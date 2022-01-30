int ledPins[4] = {10, 11, 12, 13};
int buttonPins[4] = {2, 3, 4, 5};
int values[4] = {0, 0, 0, 0};
unsigned long lightOn;
int gameOver = 0;
unsigned long gameOverTime;
unsigned long flashes [] = {500, 1000, 1500, 2000, 2500, 3000};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for (int i=0; i<4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  lightOn = millis() + random(500,3000);
}

void animation() {
  unsigned long currentTime = millis();
  int index = -1;
  unsigned long timePassed = currentTime - gameOverTime;
  for(int i = 0; i < (sizeof(flashes)/sizeof(flashes[0])); i++) {
    if(flashes[i] > timePassed) {
      index = i;
      break;
    }
  }
  if(index >= 0) { 
    if(index % 2 == 1) {
      for(int i=0; i < 4; i++) {
        digitalWrite(ledPins[i], LOW);
      }
    } else {
      for(int i=0; i < 4; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
    }
  } else {
    gameOver = 0;
    for(int i=0; i<4; i++) {
      values[i] = 0;
    }
  }
}

void checkForGameOver() {
  for(int i=0; i<4; i++) {
    if (values[i] == 0) {
      return;
    }
  }
  gameOver = 1;
  gameOverTime = millis();
}

void checkButton(int buttonPin, int ledPin, int index) {
  int val = digitalRead(buttonPin);
  if (val == LOW) {
    digitalWrite(ledPin, LOW);
    values[index] = 0;
  }
}

void loop() {  
  if (!gameOver) {
    checkForGameOver();

    for(int i=0; i<4; i++) {
      checkButton(buttonPins[i], ledPins[i], i);
    }
    if (millis() > lightOn) {
      int pin = random(4);
      values[pin] = 1;
      digitalWrite(ledPins[pin], HIGH);
      lightOn = lightOn + random(100,1000);
    }
  } else {
    Serial.println("Game Over!");
    animation();
  }
}
