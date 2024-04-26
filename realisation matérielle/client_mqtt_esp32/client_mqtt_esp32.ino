#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "music/musique.h"

// ---------------------- Screen ----------------------
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    16
#define MAX_WAIT_FOR_TIMER 4

// ----------------------- WiFi -----------------------
const char *ssid = "";
const char *password = "";

// -------------------- MQTT Broker -------------------
const char *mqtt_broker = "";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

// ----------------------- Topic ----------------------
const char *topic_led = "led_1";
const char *topic_RPR = "recv_photoresistance_1";
const char *topic_SPR = "send_photoresistance_1";
const char *topic_RBTN = "recv_button_1";
const char *topic_SBTN = "send_button_1";
const char *topic_OLED = "oled_1";
const char *topic_SPK = "speaker_1";

// ---------------------- Taches ----------------------
enum {EMPTY, FULL};

struct Led_s {
  int timer;
  unsigned long period;
  int pin;
  int etat;
  int eteint;
}Led;

struct Lum_s {
  byte pin;
}Lum;

struct Oled_s {
  Adafruit_SSD1306 display;
  char str[100];
}Oled;

struct Button_s {
  byte pin;
  int etat;
}Button;

struct Speaker_s {
  byte pin;
  int size;
  int note;
  void (*music)(int, int);
  int arret;
}Speaker;

// --------------------- Mail Box ---------------------
struct mailbox_s {
  int state;
  int val;
};
struct mailbox_s mb_led = {.state = EMPTY};
struct mailbox_s mb_lum = {.state = EMPTY};
struct mailbox_s mb_oled = {.state = EMPTY};
struct mailbox_s mb_button = {.state = EMPTY};
struct mailbox_s mb_speaker = {.state = EMPTY};

// ----------------------- Fonction de setup -----------------------
void setup() {
  Serial.begin(9600);
  setup_wifi();
  setup_broker();

  client.subscribe(topic_led);
  client.subscribe(topic_RPR);
  client.subscribe(topic_RBTN);
  client.subscribe(topic_OLED);
  client.subscribe(topic_SPK);

  // Initialize tasks
  setup_Led(&Led, 0, 1, LED_BUILTIN); // Led est exécutée toutes les 100ms 
  setup_Lum(&Lum, 36); // Broche 36 -> photorésistance
  setup_Oled(&Oled);
  setup_Button(&Button, 23); // Broche 23 -> bouton
  setup_Speaker(&Speaker, 17); // Broche 17 -> speaker
}

// ------------- Configuration du Wifi -------------
void setup_wifi() {
  // WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.println("Connecting to WiFi..");
    // Serial.println(WiFi.status());
    
  }
  Serial.println("Connected to the Wi-Fi network");
}

// Configuration du Broker
void setup_broker() {
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-1";
    client_id += "  "+String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
    if (client.connect(client_id.c_str())) {
      Serial.println("Public EMQX MQTT broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state()+" ");
      delay(2000);
    }
  }
}

// ------------- Configuration des taches -------------
void setup_Led(struct Led_s *ctx, int timer, unsigned long period, byte pin) {
  ctx->timer = timer;
  ctx->period = period;
  ctx->pin = pin;
  ctx->etat = 0;
  ctx->eteint = 1;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, ctx->etat);
}

void setup_Lum(struct Lum_s *lum, byte pin) {
  lum->pin = pin;
}

void setup_Oled(struct Oled_s *oled) {
  oled->display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  Wire.begin(4, 15); // pins SDA, SCL

  if(!(oled->display.begin(SSD1306_SWITCHCAPVCC, 0x3C))) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  oled->display.clearDisplay();
  oled->display.setTextSize(3);
  oled->display.setTextColor(WHITE);
  oled->display.setCursor(0, 0);
  oled->display.cp437(true);
  
  oled->display.display();
}

void setup_Button(struct Button_s *button, byte pin) {
  button->pin = pin;
  pinMode(button->pin, INPUT_PULLUP);
}

const int TONE_PWM_CHANNEL = 0;

void setup_Speaker(struct Speaker_s *speaker, byte pin) {
  speaker->pin = pin;
  pinMode(speaker->pin, OUTPUT);
}

// ----------------------- Fonction qui boucle -----------------------
void loop() {
  client.loop();
  loop_Led(&Led);
  loop_Lum(&Lum);
  loop_Oled(&Oled);
  loop_Button(&Button);
  loop_Speaker(&Speaker);
}

// ------------- Loop des taches -------------
void loop_Led(struct Led_s *led) {
  if (led->eteint || !waitFor(led->timer, led->period)) return;
  digitalWrite(led->pin, led->etat);
  led->etat = 1 - led->etat;
  if (mb_led.state == FULL) {
    led->period = mb_led.val;
    mb_led.state = EMPTY;
  }
}

void loop_Lum(struct Lum_s *lum) {
  if (mb_lum.state == EMPTY) return;
  int r = analogRead(lum->pin);
  char str[4] = { 0 };
  itoa(100 - map(r, 0, 4095, 0, 100), str, 10);
  client.publish(topic_SPR, str);
  mb_lum.state = EMPTY;
}

void loop_Oled(struct Oled_s *oled) {
  if (mb_oled.state == EMPTY) return;

  mb_oled.state = EMPTY;
  oled->display.clearDisplay();
  oled->display.setCursor(0, 0);

  oled->display.write(oled->str);
  oled->display.display();
}

void loop_Button(struct Button_s *button) {
  if (mb_button.state == EMPTY) return;
  mb_button.state = EMPTY;
  int etat = digitalRead(button->pin);
  button->etat = 1 - etat;
  char str[2] = { 0 };
  itoa(button->etat, str, 10);
  client.publish(topic_SBTN, str);
}

void loop_Speaker(struct Speaker_s *speaker) {
  if (mb_speaker.state == EMPTY || speaker->arret) return;
  speaker->music(speaker->pin, speaker->note % speaker->size);
  speaker->note++;
}

// ----------- Renvoie si le timer est fini -----------
unsigned int waitFor(int timer, unsigned long period) {
  static unsigned long waitForTimer[MAX_WAIT_FOR_TIMER];
  unsigned long newTime = micros() / period;
  int delta = newTime - waitForTimer[timer];
  if (delta < 0)
    delta = 1 + newTime;
  if (delta)
    waitForTimer[timer] = newTime;
  return delta;
}

// -------- Lors de la reception d'un message ---------
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message received on topic ");
  Serial.println(topic);

  // Led
  if (strcmp(topic, topic_led) == 0) {
    // Eteint la led
    if (length == 1 && *payload == (byte)'0') {
      Led.etat = 0;
      Led.eteint = 1;
      return;
    }
    // Fais clignoter les leds
    Led.eteint = 0;
    mb_led.state = FULL;
    mb_led.val = 0;
    for (unsigned int i = 0; i < length; i++) {
      mb_led.val *= 10;
      mb_led.val += payload[i] - '0';
    }
    mb_led.val *= 100;
  }

  // Photoresistance
  else if (strcmp(topic, topic_RPR) == 0) {
  // Renvoie la valeur de la photo resistance
    mb_lum.state = FULL;
  }

  // Button
  else if (strcmp(topic, topic_RBTN) == 0) {
    // Renvoie la valeur du bouton
    mb_button.state = FULL;
  }

  // OLED
  else if (strcmp(topic, topic_OLED) == 0) {
    // Affiche un message sur l'ecran
    for (unsigned int i = 0; i < length; i++) {
      Oled.str[i] = payload[i];
    }
    Oled.str[length] = '\0';
    mb_oled.state = FULL;
  }

  // Speaker
  else if (strcmp(topic, topic_SPK) == 0) {
    // Joue du son
    mb_speaker.state = FULL;
    mb_speaker.val = 0;
    for (unsigned int i = 0; i < length; i++) {
      mb_speaker.val *= 10;
      mb_speaker.val += payload[i] - '0';
    }
    Serial.println(mb_speaker.val);
    if (mb_speaker.val == 0) {
      Speaker.arret = 1;
      return;
    } else if (mb_speaker.val == 1) {
      Speaker.size = sizeof(chevelle_the_red_durations);
      Speaker.music = play_chevelle_the_red;
    } else if (mb_speaker.val == 2) {
      Speaker.size = sizeof(doom_durations);
      Speaker.music = play_doom;
    } else if (mb_speaker.val == 3) {
      Speaker.size = sizeof(game_of_thrones_durations);
      Speaker.music = play_game_of_thrones;
    } else if (mb_speaker.val == 4) {
      Speaker.size = sizeof(happy_birthday_durations);
      Speaker.music = play_happy_birthday;
    } else if (mb_speaker.val == 5) {
      Speaker.size = sizeof(harry_potter_durations);
      Speaker.music = play_harry_potter;
    } else if (mb_speaker.val == 6) {
      Speaker.size = sizeof(home_alone_durations);
      Speaker.music = play_home_alone;
    } else if (mb_speaker.val == 7) {
      Speaker.size = sizeof(imagine_dragons_enemy_durations);
      Speaker.music = play_imagine_dragons_enemy;
    } else if (mb_speaker.val == 8) {
      Speaker.size = sizeof(its_a_small_world_durations);
      Speaker.music = play_its_a_small_world;
    } else if (mb_speaker.val == 9) {
      Speaker.size = sizeof(kaleo_way_down_we_go_durations);
      Speaker.music = play_kaleo_way_down_we_go;
    } else if (mb_speaker.val == 10) {
      Speaker.size = sizeof(mario_bros_durations);
      Speaker.music = play_mario_bros;
    } else if (mb_speaker.val == 11) {
      Speaker.size = sizeof(maroon5_memories_durations);
      Speaker.music = play_maroon5_memories;
    } else if (mb_speaker.val == 12) {
      Speaker.size = sizeof(nokia_durations);
      Speaker.music = play_nokia;
    } else if (mb_speaker.val == 13) {
      Speaker.size = sizeof(pacman_durations);
      Speaker.music = play_pacman;
    } else if (mb_speaker.val == 14) {
      Speaker.size = sizeof(pink_panther_durations);
      Speaker.music = play_pink_panther;
    } else if (mb_speaker.val == 15) {
      Speaker.size = sizeof(pirates_of_the_caribbean_durations);
      Speaker.music = play_pirates_of_the_caribbean;
    } else if (mb_speaker.val == 16) {
      Speaker.size = sizeof(shape_of_you_durations);
      Speaker.music = play_shape_of_you;
    } else if (mb_speaker.val == 17) {
      Speaker.size = sizeof(star_wars_durations);
      Speaker.music = play_star_wars;
    } else if (mb_speaker.val == 18) {
      Speaker.size = sizeof(tetris_durations);
      Speaker.music = play_tetris;
    } else if (mb_speaker.val == 19) {
      Speaker.size = sizeof(the_godfather_durations);
      Speaker.music = play_the_godfather;
    } else if (mb_speaker.val == 20) {
      Speaker.size = sizeof(the_lion_sleeps_tonight_durations);
      Speaker.music = play_the_lion_sleeps_tonight;
    } else if (mb_speaker.val == 21) {
      Speaker.size = sizeof(the_nightmare_before_christmas_durations);
      Speaker.music = play_the_nightmare_before_christmas;
    } else if (mb_speaker.val == 22) {
      Speaker.size = sizeof(the_simpsons_durations);
      Speaker.music = play_the_simpsons;
    } else if (mb_speaker.val == 23) {
      Speaker.size = sizeof(drift_durations);
      Speaker.music = play_drift;
    } else if (mb_speaker.val == 24) {
      Speaker.size = sizeof(xmas_durations);
      Speaker.music = play_xmas;
    }
    Speaker.size /= sizeof(int);
    Speaker.note = 0;
    Speaker.arret = 0;
  }
}
