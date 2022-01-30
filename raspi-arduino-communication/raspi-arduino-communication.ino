int ledPins[4] = {2, 3, 4, 5};
int ledState[4] = {0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  for (int i=0; i<4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.println("Device is ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int ledToSwitch = Serial.read() - '0';
    ledState[ledToSwitch] = (ledState[ledToSwitch] + 1) % 2;
    digitalWrite(ledPins[ledToSwitch], ledState[ledToSwitch]);
  }
}       
