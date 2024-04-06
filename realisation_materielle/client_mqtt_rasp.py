import paho.mqtt.client as mqtt
import database as db

# Paramètres du broker MQTT
broker_address = "localhost"
broker_port = 1883

# Topics
topic_led_1 = "led_1"
topic_led_2 = "led_2"
topic_RPR_1 = "recv_photoresistance_1"
topic_RPR_2 = "recv_photoresistance_2"
topic_SPR_1 = "send_photoresistance_1"
topic_SPR_2 = "send_photoresistance_2"
topic_RBTN_1 = "recv_button_1"
topic_RBTN_2 = "recv_button_2"
topic_SBTN_1 = "send_button_1"
topic_SBTN_2 = "send_button_2"
topic_OLED_1 = "oled_1"
topic_OLED_2 = "oled_2"
topic_SPK = "speaker"

# Fonction de connexion au broker
# Souscrire au topic une fois connecté
def on_connect(client, userdata, flags, rc):
    print("Connecté")
    client.subscribe(topic_SPR_1)
    client.subscribe(topic_SPR_2)
    client.subscribe(topic_SBTN_1)
    client.subscribe(topic_SBTN_2)

# Fonction de réception des messages
def on_message(client, userdata, message):
    print("Message reçu on topic " + message.topic)
    db.insert_data(message.topic, message.payload.decode("utf-8"))

# Il faut gerer le cas ou on doit envoyé un message a l'esp32

def main():
    client = mqtt.Client() 
    client.connect(broker_address, broker_port)
    client.on_connect = on_connect
    client.on_message = on_message
    db.open_data()
    client.loop_start()

if __name__ == "__main__":
    main()