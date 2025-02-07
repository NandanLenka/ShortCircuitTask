# ShortCircuitTask
Traffic Light Control System
Task1 link: https://www.tinkercad.com/things/epf0hiPM1kg-task1?sharecode=rfIz1d874PIDgrGfeVLa7R__Q1zZCmpvEM-RyvnvFnE
Task2 link: https://www.tinkercad.com/things/3Tkp9bWxwMs-task2?sharecode=W0zU0xEovy62BLRrsbQ9I1l2jGQ5kUcc-ELZHWKEDtE
A smart traffic light system using Arduino, detecting vehicles via an ultrasonic sensor and managing signals accordingly. Includes a pedestrian button for crossing requests when no vehicles are detected for 30 seconds.

Features:

Vehicle Detection: Ultrasonic sensor detects approaching vehicles. When the distance is less than a threshold value (here 20) the traffic light control system activates.

Traffic Light Control: Automated light cycle(Green, Yellow, Red) based on traffic. Green for 5sec, Yellow for 2sec, Red for 5sec.

Pedestrian Crossing: Button-activated safe crossing. If no vehicle is detected for 30 seconds, the light stays Red unless the button is pressed for pedestrian crossing.

Auto-Red Mode: Keeps red light on if no vehicle is detected for 30s.
