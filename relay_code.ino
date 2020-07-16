// Run mix.py from powershell [admin]

char serialData;
int receivedChar;
boolean newData = false;

void setup() {
  // initialize digital pins as an outputs.
  pinMode(9, OUTPUT);   // IN1
  pinMode(10, OUTPUT);  // IN2
  pinMode(11, OUTPUT);  // IN3
  pinMode(12, OUTPUT);  // IN4
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  delay(150);

  recvOneChar();                 // This fuction reads the data coming from Python
  showNewData();                 // This function is std and starts the motion function
}

void recvOneChar() {
  if (Serial.available() > 0) {
    serialData = Serial.read();
    //receivedChar = receivedChar-'0';
    newData = true;
  }
}
void showNewData() {
  if (newData == true)  { //&& (newData == 1)
    Serial.print("This just in ... ");
    Serial.println(serialData);
    startCode();
    newData = false;
  }
}


void startCode() {                //Change all values of LOW to HIGH

  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);          //supply power to the LED [Remove when connecting the car]


  //Relay stuff
  if (serialData > 0) {
    while (serialData == '1') {
      digitalWrite(9, HIGH);
      delay(100);
      serialData = 0;

      digitalWrite(9, LOW);
    }

    while (serialData == '2') {        // RVS Motion
      digitalWrite(10, HIGH);
      delay(100);
      serialData = 0;

      digitalWrite(10, LOW);
    }

    while (serialData == '3') {        // FWD + Right Motion
      digitalWrite(11, HIGH);       // Wheels turn Right [11]
      delay(100);
      digitalWrite(9, HIGH);        // FWD Motion is activated [10]
      delay(100);
      digitalWrite(9, LOW);         // Stops FWD Motion
      digitalWrite(11, LOW);        // Wheels return to original position
      serialData = 0;               // Reset value
    }


    while (serialData == '4') {        // FWD + Left Motion
      digitalWrite(12, HIGH);
      delay(100);
      digitalWrite(9, HIGH);        // FWD Motion is activated [10]
      delay(100);
      serialData = 0;               // Reset value
      digitalWrite(9, LOW);
      digitalWrite(12, LOW);
    }

    while (serialData == '5') {        // RVS + Left Motion
      digitalWrite(12, HIGH);
      delay(100);
      digitalWrite(10, HIGH);       // FWD Motion is activated [10]
      delay(100);
      serialData = 0;               // Reset value
      digitalWrite(10, LOW);
      digitalWrite(12, LOW);
    }

    while (serialData == '6') {        // RVS + Left Motion
      digitalWrite(12, HIGH);
      delay(100);
      digitalWrite(10, HIGH);       // FWD Motion is activated [10]
      delay(100);
      serialData = 0;               // Reset value
      digitalWrite(10, LOW);
      digitalWrite(12, LOW);
    }
  }
}
