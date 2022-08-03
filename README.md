### İoT Car
# İot Car Bulid With Raspberrypi and NodeMcu
**İot Car Application**
*The general principle of our application was to design a comprehensive project on the Internet of Things.
Thanks to our project, all sensors, motors and electronic devices used in the prototype can communicate with each other.
In my project, "mosquitto" was used to implement the concepts of the Internet of Things, and our mosquito distribution and server point became our raspberrypi card.
In order to fully meet the IoT concepts and fulfill the requirements, "IoT Stack" was installed on our raspberry pi card, and this installation includes add-ons such as grafana, influxdb, nodered. 
After the IoT stack installation, we can now use our Raspberry pi card as a broker, but our nodemcu model in our prototype can also be deployed. 
It needs to communicate with our raspberry pi card, which is a broker, for this, by integrating the "pubsubclient" library into our nodemcu card, 
an example program about this library is opened from "arduino.ino" and then the necessary configurations (ip addresses) for the necessary encodings and connections are added to this project page.
being written.After doing all these processes successfully, we download our application called "mqtt dash" optionally to our phone before uploading our program to nodemcu in order to test it. 
Later, while installing the program to esp, on the other hand, we feed our raspberry pi card with an adapter and provide power flow. 
Now, all electronic devices are ready for testing, as soon as the message that the mqtt connection is successfully established, we send data to our vehicle from the mqtt dash application and observe the movement of the vehicle with the data it receives.
Now send to the esp module, the data sent comes to both our phone, our personal computer and our broker raspberry pi card.
Optionally, you can perform a design with the "grafana" interface to visualize this data.
You can create a database on Raspberry ("influxdb") and keep the flowing data on this database. 
In other words, you can add variety to your project with various plug-ins after the test phase of the work is completed successfully.*
