const int BUTTON_IN = 2;
const int LED_OUT = 3;

const int FAST_TIMING = 250;
const int SLOW_TIMING = 1000;

const int DELAY_TIME = 5;

bool led_status = false;
int timer;

enum BlinkState:char{BlinkOff='0', BlinkConst='1', BinkFast='2', BlinkSlow='3'};
char inputChar;

BlinkState blinkState = BlinkOff;

void checkButtonPosition(){
  if(digitalRead(BUTTON_IN) == LOW){
    Serial.print('C');
  }
}

void changeLEDStatus(){
  timer = 0;
    
  if(led_status){
    digitalWrite(LED_OUT, LOW);
  }
  else {
    digitalWrite(LED_OUT, HIGH);
  }

  led_status = !led_status;
}

void setup() {
  timer = 0;
  // put your setup code here, to run once:
  pinMode(BUTTON_IN, INPUT_PULLUP);
  pinMode(LED_OUT, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkButtonPosition();
  
  timer += DELAY_TIME;

  if (Serial.available() > 0) {
    blinkState = Serial.read();
  }

  switch(blinkState){
    case BlinkOff: 
      digitalWrite(LED_OUT, LOW);
      break;
    case BlinkConst:
      digitalWrite(LED_OUT, HIGH);
      break;
    case BinkFast:
      if(timer >= FAST_TIMING){
        changeLEDStatus();
      }
      break;
    case BlinkSlow:
      if(timer >= SLOW_TIMING){
        changeLEDStatus();
      }
      break;
  }

  delay(DELAY_TIME);
}
