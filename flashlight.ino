const int buttonPin = 2;  

int buttonState = 0;
int lastButtonState = 0;
unsigned long startPressed = 0;
int held_down_time = 0;
int on = 0;
int disable_time = 5000;
int disabled = 0;
int was_disabled = 0;
int disabled_time_passed = 0;
int start_Disabled = 0;
int recharge_time = 2000;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  //Serial.begin(115200);
}

void loop() {
  //Serial.println(held_down_time);
  buttonState = digitalRead(buttonPin); 
  if(buttonState == LOW){
    held_down_time = millis() - startPressed;
  }
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      startPressed = millis();
      on = 1;
    }else{
      held_down_time = 0;
      on = 0;
    }
  }

  if(on == 1 and disabled == 0){
    digitalWrite(13, HIGH);
  }else if(on == 0 or disabled == 1){
    digitalWrite(13, LOW);
  }

  if(held_down_time > disable_time){
    disabled = 1;
  }

  if(disabled == 1){
    if(disabled != was_disabled){
      start_Disabled = millis();
      was_disabled = disabled;
    }
    disabled_time_passed = millis() - start_Disabled;
    if(disabled_time_passed > recharge_time){
      disabled_time_passed = 0;
      startPressed = millis();
      on = 0;
      disabled = 0;
    }
  }

  lastButtonState = buttonState;
  was_disabled = disabled;
}
