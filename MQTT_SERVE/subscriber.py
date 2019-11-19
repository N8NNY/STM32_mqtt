import paho.mqtt.client as mqtt
import settings
host = settings.HOST
port = settings.PORT


def on_connect(client, userdata, flags, rc):
    print("MQTT Connected.")
    print("Connected with result code " + str(rc))
    client.subscribe("Test")


def on_message(client, userdata, msg):
    print(msg.payload.decode("utf-8", "strict"))


client = mqtt.Client()
client.username_pw_set(settings.USER, settings.PASSWORD)
client.on_connect = on_connect
client.on_message = on_message
client.connect(host, port)
client.loop_forever()
