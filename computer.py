import paho.mqtt.client as mqtt
from random import randint, randrange, uniform
import time
#from main import dict
#mqttBroker = "mqtt.eclipseprojects.io"
mqttBroker = "test.mosquitto.org"
client= mqtt.Client("COMPUTER")
client.connect(mqttBroker)

    
def comp(num):
        print(num)
        topic="MOVEMENT"
        if(num==5):
                topic="PACKAGE"
                mymess="THROW"
        elif(num==4):
                mymess="REVERSE"
        elif(num==3):
                mymess="LEFT"
        elif(num==2):
                mymess="RIGHT"
        elif(num==1):
                mymess="FORWARD"
        else:
                mymess="STOP"

        
                
        client.publish(topic,mymess)
        print("just publish  "+str(mymess)+" to "+topic)
        time.sleep(0.2)


        
