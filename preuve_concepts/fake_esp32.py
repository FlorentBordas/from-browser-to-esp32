import paho.mqtt.client as mqtt
import time

# Paramètres du broker MQTT
broker_address = "localhost"
broker_port = 1883
topic = "compteur"

# Fonction de connexion au broker
def on_connect(client, userdata, flags, rc):
    print("Connecté")

def main():
    client = mqtt.Client() 
    client.connect(broker_address, broker_port)
    client.loop_start()
    client.on_connect = on_connect

    # Envoie toute les seconde un compteur
    counter = 0
    while True:
        counter += 1
        client.publish(topic, str(counter))
        print("Compteur publié : " + str(counter))
        time.sleep(1)

if __name__ == "__main__":
    main()