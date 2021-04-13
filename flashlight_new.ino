const int button_pin = 2;
const int led_pin = 13;

// || (alt gr + w , || or)
// && (alt gr + c , && or)

int charge = 5000; // in milli seconds (1000 milliseconds = 1 seconds)
int max_charge = charge;
bool button_state = true;
bool last_button_state = true;
unsigned long last_millis = 0;
bool millis_changed = false;
bool in_use = false;
bool lamp_on = false;
bool disabled = false;
int flicker_time = 2000; // the remaining time of int=charge when the light starts to flicker
int flicker_frequency = 2;
int random_number = 0;


void setup(){
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  //Serial.begin(115200);
}

void loop(){
  random_number = random(1, 100);
  //Serial.println(charge);
  if(charge < 0){
    charge = 0;
  }
  if(charge > 5000){
    charge = max_charge;
  }
  button_state = digitalRead(button_pin);
  if(button_state != last_button_state){
    in_use = 1;
    if(digitalRead(button_pin) == false){
      in_use = 1;
      lamp_on = 1;
    }else{
      in_use = 0;
      lamp_on = 0;
    }
  }

  if(lamp_on == true && disabled == false){
    //Serial.println("xd");
    digitalWrite(led_pin ,true);
   }else if(lamp_on == false){
    digitalWrite(led_pin ,false);
  }

  if(charge <= flicker_time && in_use == true){
    if(random_number < flicker_frequency){
      lamp_on = !lamp_on;
    }
  }

  if(in_use == true){
    if(millis_changed == true && disabled == false){
      charge --;
    }
  }
  if (in_use == false || disabled == true){
    if(millis_changed == true){
      charge ++;
    }
  }

  if(charge <= 0){
    disabled = true;
    lamp_on = false;
  }

  if(disabled == true && charge >= max_charge){
    disabled = false;
    if(digitalRead(button_pin) == false){
      lamp_on = 1;
    }
  }

  if(last_millis != millis()){
    millis_changed = true;
  }else{
    millis_changed = false;
  }

  last_millis = millis();
  last_button_state = button_state;
}
