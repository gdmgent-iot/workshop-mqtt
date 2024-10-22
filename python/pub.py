# imports
import paho.mqtt.client as mqtt
import time

# initialize the client
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
# broker, port, keepalive0
client.connect("mqtt.eclipseprojects.io", 1883, 60)

# publish a random message
def publish_joke():
    client.publish("jokes", "Why did the tomato turn red? Because it saw the salad dressing!")

# publish a joke every 5 seconds
try:
    while True:
        publish_joke()
        time.sleep(5)
except Exception as e:
    print("An error occurred: ", e)
finally:
    client.disconnect()
    print("Disconnected from the broker.")