int ledPin          = 13;                 //
int joyPinButton    = 4;                  // push button
int joyPinX         = A0;                 // slider variable connecetd to analog pin 0
int joyPinY         = A1;                 // slider variable connecetd to analog pin 1
int joyPinZ         = A2;                 // slider variable connecetd to analog pin 2
int X_val           = 0;                  // variable to read the value from the analog pin 0
int Y_val           = 0;                  // variable to read the value from the analog pin 1
int Z_val           = 0;                  // variable to read the value from the analog pin 2

int leftPWM = 5;
int rightPWM = 6;
int forwPWM = 9;
int backPWM = 10;

boolean forward = false;
boolean left = false;

boolean enableForward = false;
boolean enableLeft = false;

int middlePoint = 1023 / 2;
int threshold = 60; // it helps reading sensitivity

void setup() {
  Serial.begin(9600);

  pinMode(joyPinButton, INPUT);
  pinMode(joyPinX, INPUT);
  pinMode(joyPinY, INPUT);
  pinMode(joyPinZ, INPUT);

  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  pinMode(forwPWM, OUTPUT);
  pinMode(backPWM, OUTPUT);
}

int treatValue(int data) {
  return (data * 9 / 1024) + 48;
}

void loop() {
  // reads the value of the potentiometer
  int state = digitalRead(joyPinButton);
  X_val = analogRead(joyPinX);
  Y_val = analogRead(joyPinY);
  Z_val = analogRead(joyPinZ);
  /*
    Serial.print(state); Serial.print('\t');
    Serial.print(Z_val); Serial.print('\t');
    if (X_val > (middlePoint + threshold) || X_val < (middlePoint - threshold)) {
      if (X_val > (middlePoint + threshold)) {
        digitalWrite(leftPWM, HIGH);
        Serial.print("LEFT: ");
        Serial.print(X_val); Serial.print("\t");
        Serial.print((middlePoint + threshold));
      } else {
        digitalWrite(rightPWM, HIGH);
        Serial.print("RIGHT: ");
        Serial.print(X_val); Serial.print("\t");
        Serial.print((middlePoint - threshold));
      }
    } else {
      digitalWrite(leftPWM, LOW);
      digitalWrite(rightPWM, LOW);
    }
    if (Y_val > (middlePoint + threshold) || Y_val < (middlePoint - threshold)) {
      if (Y_val > (middlePoint + threshold)) {
        digitalWrite(forwPWM, HIGH);
        Serial.print("FORWARD: ");
        Serial.print(Y_val); Serial.print("\t");
        Serial.print((middlePoint + threshold));
      } else {
        digitalWrite(backPWM, HIGH);
        Serial.print("BACKWARD: ");
        Serial.print(Y_val); Serial.print("\t");
        Serial.print((middlePoint - threshold));
      }
    } else {
      digitalWrite(forwPWM, LOW);
      digitalWrite(backPWM, LOW);
    }
    Serial.println();
  */
  if (X_val > (middlePoint + threshold) || X_val < (middlePoint - threshold)) {
    if (X_val > (middlePoint + threshold)) {
      Serial.print("L"); Serial.print('\t');
    } else {
      Serial.print("R"); Serial.print('\t');
    }
  } else {

  }
  if (Y_val > (middlePoint + threshold) || Y_val < (middlePoint - threshold)) {
    if (Y_val > (middlePoint + threshold)) {
      Serial.print("F"); Serial.print('\t');
    } else {
      Serial.print("B"); Serial.print('\t');
    }
  } else {

  }
  //Serial.print(X_val); Serial.print('\t');
  //Serial.print(Y_val); Serial.print('\t');
  Serial.print(Z_val); Serial.print('\t');
  Serial.print(state); Serial.print('\t');
  Serial.println();

  delay(100);
}
