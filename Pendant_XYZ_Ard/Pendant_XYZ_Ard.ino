/*
  Pendant XYZ
  code for reading the rotatry encoder and selector
  and converting those to a GRBL jog command
*/
#define Channel_A 2
#define Channel_B 3
#define Axe_X 4
#define Axe_Y 5
#define Axe_Z 6
#define Axe_4 7
#define X1 8
#define X10 9
#define X100 10

volatile int jogValue=0;
volatile int jogValueX=0;
volatile int jogValueY=0;
volatile int jogValueZ=0;
volatile int jogValue4=0;
char startJogCommand[100] = "$J=G91 G20";
char completeJogCommand[100];


// 
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Channel_A,INPUT_PULLUP);
  pinMode(Channel_B,INPUT_PULLUP);
  pinMode(X1,INPUT_PULLUP);  // Multiplier Active on LOW
  pinMode(X10,INPUT_PULLUP);
  pinMode(X100,INPUT_PULLUP);
  pinMode(Axe_X,INPUT_PULLUP); // Axe are Active on a Low
  pinMode(Axe_Y,INPUT_PULLUP);
  pinMode(Axe_Z,INPUT_PULLUP);
  pinMode(Axe_4,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Channel_A), encoderCall, RISING);
  interrupts();
}

// 
void loop() {
  delay (100);
  // if the selector is not in the off position
  // and if one of the jog value is greater than zero 
  // send the jog value
  if ((!digitalRead(X1) || !digitalRead(X10) || !digitalRead(X100)) && ( !digitalRead(Axe_X) || !digitalRead(Axe_Y) || !digitalRead(Axe_Z) || !digitalRead(Axe_4)) ){
      digitalWrite(LED_BUILTIN, HIGH);   // 
      if (jogValueX != 0 || jogValueY != 0 || jogValueZ != 0 ){
        Serial.println(startJogCommand + String(" X") + String(jogValueX) + String(" Y") + String(jogValueY) + String(" Z") + String(jogValueZ));
        jogValueX=0;
        jogValueY=0;
        jogValueZ=0;
        
      }
  }
  else{
      digitalWrite(LED_BUILTIN, LOW);   
      Serial.println(String(char(0x85))); // Send tge Jog cancel Command
  }
}

void encoderCall()
  {
    if (!digitalRead(Channel_B)){
      if (!digitalRead(X1)){
        if (!digitalRead(Axe_X)){
          jogValueX++;
        }else if(!digitalRead(Axe_Y)) {
          jogValueY++;
        }else if(!digitalRead(Axe_Z)) {
          jogValueZ++;
        }else if(!digitalRead(Axe_4)) {
          jogValue4++;
        }
      }else if (!digitalRead(X10)){
        if (!digitalRead(Axe_X)){
          jogValueX = jogValueX + 10;
        }else if(!digitalRead(Axe_Y)) {
          jogValueY = jogValueY + 10;
        }else if(!digitalRead(Axe_Z)) {
          jogValueZ = jogValueZ + 10;
        }else if(!digitalRead(Axe_4)) {
          jogValue4 = jogValue4 + 10;
        }
      } else if ( !digitalRead(X100)) {
        if (!digitalRead(Axe_X)){
          jogValueX = jogValueX + 100;
        }else if(!digitalRead(Axe_Y)) {
          jogValueY = jogValueY + 100;
        }else if(!digitalRead(Axe_Z)) {
          jogValueZ = jogValueZ + 100;
        }else if(!digitalRead(Axe_4)) {
          jogValue4 = jogValue4 + 100;
        }
      }
    }
    else {
      if (!digitalRead(X1)){
        if (!digitalRead(Axe_X)){
          jogValueX--;
        }else if(!digitalRead(Axe_Y)) {
          jogValueY--;
        }else if(!digitalRead(Axe_Z)) {
          jogValueZ--;
        }else if(!digitalRead(Axe_Z)) {
          jogValue4--;
        }
      }else if (!digitalRead(X10)){
        if (!digitalRead(Axe_X)){
          jogValueX = jogValueX - 10;
        }else if(!digitalRead(Axe_Y)) {
          jogValueY = jogValueY - 10;
        }else if(!digitalRead(Axe_Z)) {
          jogValueZ = jogValueZ - 10;
        }else if(!digitalRead(Axe_4)) {
          jogValue4 = jogValue4 - 10;
        }
      } else if ( !digitalRead(X100)) {
        if (!digitalRead(Axe_X)){
          jogValueX = jogValueX - 100;
        }else if(!digitalRead(Axe_Y)) {
          jogValueY = jogValueY - 100;
        }else if(!digitalRead(Axe_Z)) {
          jogValueZ = jogValueZ - 100;
        }else if(!digitalRead(Axe_4)) {
          jogValue4 = jogValue4 - 100;
        }
      }
    }
  }

