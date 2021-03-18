int flagInput;
int mainTimer;
int secondTimer;
int mainTimerTarget = 900;
int secondTimerTarget = 60;
unsigned long temptTimer;
bool gameRunning = false;
bool delayStart = false;
int delayStartTimer;
int delayStartTimerTarget = 5;
bool defence = false;
int abortGameTimer;
bool abortGame = false;


void setup() {
  //start serial connection
  Serial.begin(9600);
  Serial.println("hello");
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  flagInput = 0;
  temptTimer = 0;
  mainTimer = 0;
  secondTimer = 0;
  temptTimer = millis();
  abortGameTimer = 0;

}

void loop() {
  updateTimer();
  startGame();
  //read the pushbutton value into a variable
  readInput();
  //print out the value of the pushbutton
  if (!flagInput) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (mainTimer > mainTimerTarget || secondTimer > secondTimerTarget) {
    endGame();
  }

}


void readInput() {
  flagInput = digitalRead(2);
  delayStart = digitalRead(5);
}

void updateTimer() {
  if (gameRunning && (millis() - temptTimer > 1000)) {
    temptTimer = millis();
    startSignal();
    if ((delayStartTimerTarget < delayStartTimer) || !delayStart) {
      if (flagInput && mainTimer == 0) {
        defence = true;
      }
      mainTimer++;

    } else {
      delayStartTimer++;
    }
    if (flagInput && mainTimer > 0 && !defence ) {
      secondTimer++;
    } else if (!flagInput && mainTimer && defence > 0) {
      secondTimer++;
    } else {
      secondTimer = 0;
    }
    Serial.println(mainTimer);
    Serial.println(delayStart);
    Serial.println(flagInput);
    Serial.println(abortGameTimer);
    Serial.println(abortGame);
    Serial.println("************");
  }

}
void startGame() {
  if (!digitalRead(3)) {
    if(gameRunning && mainTimer > 0){
      if(!abortGame){
      abortGameTimer = mainTimer;
      abortGame = true;
      }
      if(abortGame && mainTimer - abortGameTimer > 2){
      Serial.println("stop her");
      endGame();
      }
    }
    else{
      
      gameRunning = true;
  }
  }
  else{
    abortGame = false;
  }
}

void endGame() {
  endSignal();

  digitalWrite(13, HIGH);
  Serial.println("done");
  mainTimer = 0;
  secondTimer = 0;
  delayStartTimer = 0;
  gameRunning = false;
  defence = false;

}

void startSignal() {
  if (mainTimer > 0 && mainTimer < 6) {
    digitalWrite(8, HIGH);
  }
  else {
    digitalWrite(8, LOW);
  }

}
void endSignal() {
  Serial.println("derp");
  for (int i = 0; i < 3; i++) {
    digitalWrite(8, HIGH);
    delay(5000);
    digitalWrite(8, LOW);
    delay(3000);
    Serial.println("stop");
  }
}
