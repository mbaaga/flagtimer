int flagInput;
int mainTimer;
int secondTimer;
int mainTimerTarget = 10;
int secondTimerTarget = 2;
unsigned long temptTimer;
bool gameRunning = false;
bool delayStart = false;
int delayStartTimer;
int delayStartTimerTarget = 5;
bool defence = false;
int abortGameTimer;
bool abortGame = false;
int flagPin = 3;
int signalPin = 5;


void setup() {
  //start serial connection
  Serial.begin(9600);
  Serial.println("hello");
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(flagPin, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(signalPin, OUTPUT);
  pinMode(13, OUTPUT);
  flagInput = 0;
  temptTimer = 0;
  mainTimer = 0;
  secondTimer = 0;
  temptTimer = millis();
  abortGameTimer = 0;

  startGame();
  digitalWrite(signalPin, HIGH);
  digitalWrite(13, LOW);

}

void loop() {
  updateTimer();
  
  
  //read the pushbutton value into a variable
  readInput();
  //print out the value of the pushbutton
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (secondTimer > secondTimerTarget) {
    endGame();
  }

}


void readInput() {
  flagInput = digitalRead(flagPin);
}

void updateTimer() {
  if (gameRunning && (millis() - temptTimer > 1000)) {
    temptTimer = millis();
    // startSignal();


      mainTimer++;
      digitalWrite(13, !digitalRead(13));

    
    if (!flagInput && mainTimer > 0 && !defence) {
      secondTimer++;
    } else if(defence && flagInput){
      secondTimer++;
    }
    
    else {
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

    if(gameRunning){

    }
    else{
      
      gameRunning = true;
      Serial.println("Defence");
      
  }
        if (!digitalRead(flagPin)) {
        defence = true;
        Serial.println(defence);
        Serial.println("************");
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
  for (int i = 0; i < 1; i++) {
    digitalWrite(signalPin, LOW);
    Serial.println("signal");
    delay(5000);
    digitalWrite(signalPin, HIGH);
    delay(3000);
    Serial.println("stop");
  }
}
