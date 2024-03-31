import paho.mqtt.client as mqtt
import logging

def on_connect(client, userdata, flags, rc):
    print(f"Client {client} connected")

def on_message(client, userdata, msg):
    print(f"Received message '{msg.payload}' on topic '{msg.topic}' from client '{client}'")

def on_subscribe(client, userdata, mid, granted_qos):
    print(f"Client {client} subscribed to topic with message id {mid} and qos {granted_qos}")

def on_unsubscribe(client, userdata, mid):
    print(f"Client {client} unsubscribed from topic with message id {mid}")

def on_disconnect(client, userdata, rc):
    print(f"Client {client} disconnected")

# Paramètres du broker MQTT
broker_address = "localhost"
broker_port = 1883
topic = "compteur"

logging.basicConfig(level=logging.DEBUG)

broker = mqtt.Client()
broker.enable_logger()

broker.connect(broker_address, broker_port)
broker.on_connect = on_connect
broker.on_message = on_message
broker.loop_forever()