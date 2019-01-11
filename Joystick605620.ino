/* output and input pins */
int LED_FORWARD         = 11;
int LED_BACKWARD        = 10;
int LED_LEFT            = 9;
int LED_RIGHT           = 8;
int LED_WIPE_LEFT       = 7;
int LED_WIPE_RIGHT      = 6;
int LED_PUSH            = 5;

int PUSH_PIN            = 4;
int JOYX_PIN            = A0;
int JOYY_PIN            = A1;
int JOYZ_PIN            = A2;

/* variable declaration that holds data value */
int X_val               = 0;
int Y_val               = 0;
int Z_val               = 0;
int pushState           = 0;

char cmd[4];                        // array that holds command or a combination of two or more commands
int middlePoint         = 1023 / 2; // 1023 is the default max value of analog
int wiperMiddlePoint    = 512 / 2;  // result will be the middle point of wiper, which added/subtracted by the wiper threshold
int wiperThreshold      = 180;      // it helps reading sensitivity of the Z-axis/Wiper
int axisThreshold       = 80;       // it helps reading sensitivity X & Y axis

void setup() {
  Serial.begin(9600);
  pinMode(JOYX_PIN, INPUT);
  pinMode(JOYY_PIN, INPUT);
  pinMode(JOYZ_PIN, INPUT);
  pinMode(PUSH_PIN, INPUT);

  pinMode(LED_FORWARD, OUTPUT);
  pinMode(LED_BACKWARD, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_WIPE_LEFT, OUTPUT);
  pinMode(LED_WIPE_RIGHT, OUTPUT);
  pinMode(LED_PUSH, OUTPUT);
}
void loop() {
  turn_off();

  X_val = analogRead(JOYX_PIN);
  Y_val = analogRead(JOYY_PIN);
  Z_val = analogRead(JOYZ_PIN);
  pushState = digitalRead(PUSH_PIN);

  if (Y_val > (middlePoint + axisThreshold) || Y_val < (middlePoint - axisThreshold)) {
    cmd[0] = (Y_val > (middlePoint + axisThreshold))  ? 'F' : 'B';
  } else {
    cmd[0] = 0;
  }
  if (X_val > (middlePoint + axisThreshold) || X_val < (middlePoint - axisThreshold)) {
    cmd[1] = (X_val > (middlePoint + axisThreshold)) ? 'L' : 'R';
  } else {
    cmd[1] = 0;
  }
  command();
}
void command() {
  String cmds;
  for (int i = 0; i < 2; i++) {
    char c = cmd[i];
    if (c != NULL && c != '\0') {
      cmds += c;
    }
  }
  // check if commands is not empty
  if (cmds != NULL && cmds != '\0') {
    Serial.println(cmds);
    if (cmds == "F") {
      turn_on(LED_FORWARD);
    } else if (cmds == "B") {
      turn_on(LED_BACKWARD);
    } else if (cmds == "L") {
      turn_on(LED_LEFT);
    } else if (cmds == "R") {
      turn_on(LED_RIGHT);
    } else if (cmds == "FR") {
      turn_on(LED_FORWARD);
      turn_on(LED_RIGHT);
    } else if (cmds == "FL") {
      turn_on(LED_FORWARD);
      turn_on(LED_LEFT);
    } else if (cmds == "BL") {
      turn_on(LED_BACKWARD);
      turn_on(LED_LEFT);
    } else if (cmds == "BR") {
      turn_on(LED_BACKWARD);
      turn_on(LED_RIGHT);
    } else {
      turn_off();
    }
  } else {
    /* if no direction command to transmit then let's check the wiper command*/
    if (Z_val > (wiperMiddlePoint + wiperThreshold) || Z_val < (wiperMiddlePoint - wiperThreshold)) {
      if (Z_val > (wiperMiddlePoint + wiperThreshold)) {
        turn_on(LED_WIPE_RIGHT);
        Serial.println("WR");
      } else if (Z_val < (wiperMiddlePoint - wiperThreshold)) {
        turn_on(LED_WIPE_LEFT);
        Serial.println("WL");
      } else {
        turn_off();
      }
    } else {
      /* if no wiper command to transmit then let's check the push button state */
      if (pushState == HIGH) {
        turn_on(LED_PUSH);
        Serial.println("ON");
      } else {
        turn_off();
      }
    }
  }
}

void turn_on(int pinNo) {
  digitalWrite(pinNo, HIGH);
}

void turn_off() {
  digitalWrite(LED_FORWARD, LOW);
  digitalWrite(LED_BACKWARD, LOW);
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);
  digitalWrite(LED_WIPE_LEFT, LOW);
  digitalWrite(LED_WIPE_RIGHT, LOW);
  digitalWrite(LED_PUSH, LOW);
}

