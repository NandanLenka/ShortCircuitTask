const int redLED = 13;
const int yellowLED = 12;
const int greenLED = 8;
const int pushBUTTON = 2;

volatile bool overrideActive = false;
volatile unsigned long lastInterruptTime = 0;

unsigned long previousMillis = 0;
unsigned long interval = 5000;  

int currentState = 0;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(pushBUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pushBUTTON), activateOverride, FALLING);

  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  if (overrideActive) {
    handleOverride();
    return;
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (currentState == 0) {  
      currentState = 1;
      digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED, LOW);
      interval = 1000;
    } else if (currentState == 1) {  
      currentState = 2;
      digitalWrite(redLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, HIGH);
      interval = 9000;
    } else if (currentState == 2) {  
      currentState = 0;
      digitalWrite(redLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED, LOW);
      interval = 5000;
    }
  }
}

void activateOverride() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200) { 
    overrideActive = true;
  }
  lastInterruptTime = interruptTime;
}

void handleOverride() {
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  unsigned long startMillis = millis();
  while (millis() - startMillis < 5000);  

  overrideActive = false;

  currentState = 0;
  previousMillis = millis();
  interval = 5000;
}
