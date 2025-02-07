#define RED_LED 13
#define YELLOW_LED 12
#define GREEN_LED 8
#define BUTTON 2
#define TRIG_PIN 9
#define ECHO_PIN 10

const int thresholdDistance = 20; // Distance threshold in cm
const long vehicleWaitTime = 30000; // 30 seconds in milliseconds

bool pedestrianRequest = false;
unsigned long lastVehicleTime = 0;

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON), pedestrianPressed, FALLING);
    Serial.begin(9600);
    stayRed(); // Start with Red light ON
}

void loop() {
    int distance = getDistance();
    
    if (distance < thresholdDistance) {
        lastVehicleTime = millis();  // Reset timer when a vehicle is detected
        normalTrafficCycle();
    } else if (millis() - lastVehicleTime > vehicleWaitTime) {
        stayRed(); // Keep the red light on indefinitely
        
        if (pedestrianRequest) {
            pedestrianRequest = false;
            pedestrianCrossing();
        }
    }
}

void normalTrafficCycle() {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(5000);
    
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    delay(2000);
    
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    delay(5000);
    
    if (pedestrianRequest) {
        pedestrianRequest = false;
        pedestrianCrossing();
    }
}

void pedestrianPressed() {
    pedestrianRequest = true;
}

void pedestrianCrossing() {
    Serial.println("Pedestrian crossing activated");
    delay(2000);
    for (int i = 0; i < 5; i++) {
        digitalWrite(YELLOW_LED, HIGH);
        delay(500);
        digitalWrite(YELLOW_LED, LOW);
        delay(500);
    }
    delay(3000);
}

void stayRed() {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
}

int getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = duration * 0.034 / 2;
    
    Serial.print("Distance: ");
    Serial.println(distance);
    
    return distance;
}
