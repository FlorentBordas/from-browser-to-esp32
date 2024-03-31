import paho.mqtt.client as mqtt

# Paramètres du broker MQTT
broker_address = "localhost"
broker_port = 1883
topic = "compteur"

# Fonction de connexion au broker
# Souscrire au topic une fois connecté
def on_connect(client, userdata, flags, rc):
    print("Connecté")
    client.subscribe(topic)

# Fonction de réception des messages
def on_message(client, userdata, message):
    print("Message reçu : " + message.payload.decode())

def main():
    client = mqtt.Client() 
    client.connect(broker_address, broker_port)
    client.on_connect = on_connect
    client.on_message = on_message
    client.loop_forever()

if __name__ == "__main__":
    main()