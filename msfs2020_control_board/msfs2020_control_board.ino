typedef struct {
  String name;
  int pin;
  int ledPin;
  int previousState;
} switch_control;

typedef struct {
  String name;
  int clickPin;
  int aPin;
  int bPin;
  int previousClickState;
  int previousAState;
} dial_control;

typedef struct {
  String name;
  int pin;
  int previousState;
} button_control;

switch_control switches[9] = {
  { "SWITCH0", 22, 31 },
  { "SWITCH1", 23, 32 },
  { "SWITCH2", 24, 33 },
  { "SWITCH3", 25, 34 },
  { "SWITCH4", 26, 35 },
  { "SWITCH5", 27, 36 },
  { "SWITCH6", 28, 37 },
  { "SWITCH7", 29, 38 },
  { "SWITCH8", 30, 39 }
};

dial_control dials[4] = {
  { "DIAL0", 40, 41, 42 },
  { "DIAL1", 43, 44, 45 },
  { "DIAL2", 46, 47, 48 },
  { "DIAL3", 49, 50, 51 }
};

button_control buttons[11] = {
  { "BUTTON0", 2 },
  { "BUTTON1", 3 },
  { "BUTTON2", 4 },
  { "BUTTON3", 5 },
  { "BUTTON4", 6 },
  { "BUTTON5", 7 },
  { "BUTTON6", 8 },
  { "BUTTON7", 9 },
  { "BUTTON8", 10 },
  { "BUTTON9", 11 },
  { "BUTTON10", 12 }
};

void setup() {
  // Init Switches & LEDs
  for (int i = 0; i < 9; i++) {
    pinMode(switches[i].pin, INPUT_PULLUP);
    pinMode(switches[i].ledPin, OUTPUT);
  }

  // Init Dials
  for (int i = 0; i < 4; i++) {
    pinMode(dials[i].clickPin, INPUT_PULLUP);
    pinMode(dials[i].aPin, INPUT_PULLUP);
    pinMode(dials[i].bPin, INPUT_PULLUP);
  }

  // Init Buttons
  for (int i = 0; i < 11; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

  Serial.begin(9600);
}

void loop() {
  // Check switches
  for (int i = 0; i < 9; i++) {
    int currentState = digitalRead(switches[i].pin);
    if (currentState == HIGH && switches[i].previousState == LOW) { // Switch just went HIGH (off)
      digitalWrite(switches[i].ledPin, LOW);
      Serial.println(switches[i].name + ":off");
    }
    else if (currentState == LOW && switches[i].previousState == HIGH) { // Switch just went LOW (on)
      digitalWrite(switches[i].ledPin, HIGH);
      Serial.println(switches[i].name + ":on");
    }
    switches[i].previousState = currentState;
  }

  //Check dials
  for (int i = 0; i < 4; i++) {
    // First check the click
    int currentClickState = digitalRead(dials[i].clickPin);
    if (currentClickState == LOW && dials[i].previousClickState == HIGH) { // Click just happened
      Serial.println(dials[i].name + ":click");
    }

    // Now check the potentiometer
    int currentAState = digitalRead(dials[i].aPin);
    int currentBState = digitalRead(dials[i].bPin);
    if (currentAState != dials[i].previousAState){    
      if (currentAState != currentBState) { 
       if (dials[i].previousAState == 1) {
        Serial.println(dials[i].name + ":down");
       }
      } else {
       if (dials[i].previousAState == 0) {
        Serial.println(dials[i].name + ":up");
       }
      }
    }

    // Store states for next loop
    dials[i].previousAState = currentAState;
    dials[i].previousClickState = currentClickState;
  }

  // Check buttons
  for (int i = 0; i < 11; i++) {
    int currentState = digitalRead(buttons[i].pin);
    if (currentState == LOW && buttons[i].previousState == HIGH) { // Click just happened
      Serial.println(buttons[i].name + ":click");
    }
    buttons[i].previousState = currentState;
  }
}
