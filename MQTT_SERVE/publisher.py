import paho.mqtt.client as mqtt
import settings
host = settings.HOST
port = settings.PORT
client = mqtt.Client()
client.username_pw_set(settings.USER, settings.PASSWORD)
client.connect(host, port)
client.publish("Test", "shout mqtt")
