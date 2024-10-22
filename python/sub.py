import paho.mqtt.client as mqtt

# initialize the client
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)

def show_joke(client, userdata, message):
    print(f"Received message: {message.payload.decode()} on topic {message.topic}")


# show the joke when a message is received
client.on_message = show_joke


# connect to the broker
client.connect("mqtt.eclipseprojects.io", 1883, 60)
client.subscribe("jokes")


try:
    client.loop_forever()
except Exception as e:
    print("An error occurred: ", e)
finally:
    client.disconnect()
    print("Disconnected from the broker.")