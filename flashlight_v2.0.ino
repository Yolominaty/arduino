const int button_pin = 2;
const int led_pin = 13;

// || (alt gr + w , || or)
// && (alt gr + c , && or)

int charge = 5000; // in milli seconds (1000 milliseconds = 1 seconds)
int max_charge = charge;
bool button_state = true;
bool last_button_state = true;
unsigned long last_millis = 0;
bool in_use = false;
bool lamp_on = false;
bool disabled = false;
int flicker_time = 2000; // the remaining time of int=charge when the light starts to flicker
int flicker_frequency = 2;
int random_number = 0;
int val = 0;

#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display


Adafruit_SSD1306 display(128, 64);  // Create display

void setup(){
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  //Serial.begin(115200);

  delay(100);  // This delay is needed to let the display to initialize

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
 
  display.clearDisplay();  // Clear the buffer

  display.setTextColor(WHITE);  // Set color of the text

  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3

  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                               // To override this behavior (so text will run off the right side of the display - useful for
                               // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                               // with setTextWrap(true).

  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)
}

void loop(){
  
  random_number = random(1, 5);
  //Serial.println(button_state);
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

  val = millis() - last_millis;
  if(in_use == false || disabled == true){
    charge = charge + val;
  }
  if(in_use == true && disabled == false){
    charge = charge - val;
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

  if(disabled == false){
    if(charge >= 4000){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, WHITE);
      display.fillRect(53, 0, 22, 64, WHITE);
      display.fillRect(78, 0, 22, 64, WHITE);
      display.fillRect(103, 0, 22, 64, WHITE);
    }
    if(charge >= 3000 && charge < 3999){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, WHITE);
      display.fillRect(53, 0, 22, 64, WHITE);
      display.fillRect(78, 0, 22, 64, WHITE);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
    if(charge >= 2000 && charge < 2999){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, WHITE);
      display.fillRect(53, 0, 22, 64, WHITE);
      display.fillRect(78, 0, 22, 64, BLACK);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
    if(charge >= 1000 && charge < 1999){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, WHITE);
      display.fillRect(53, 0, 22, 64, BLACK);
      display.fillRect(78, 0, 22, 64, BLACK);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
    if(charge > 0 && charge < 999){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, BLACK);
      display.fillRect(53, 0, 22, 64, BLACK);
      display.fillRect(78, 0, 22, 64, BLACK);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
  }

  if(disabled == true){
    if(charge >= 0 && charge <= 1000){
      display.fillRect(3, 0, 22, 64, BLACK);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, BLACK);
      display.fillRect(53, 0, 22, 64, BLACK);
      display.fillRect(78, 0, 22, 64, BLACK);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
    if(charge >= 1001 && charge <= 2000){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, BLACK);
      display.fillRect(53, 0, 22, 64, BLACK);
      display.fillRect(78, 0, 22, 64, BLACK);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
    if(charge >= 2001 && charge <= 3000){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, WHITE);
      display.fillRect(53, 0, 22, 64, BLACK);
      display.fillRect(78, 0, 22, 64, BLACK);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
    if(charge >= 3001 && charge <= 4000){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, WHITE);
      display.fillRect(53, 0, 22, 64, WHITE);
      display.fillRect(78, 0, 22, 64, BLACK);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
    if(charge >= 4000){
      display.fillRect(3, 0, 22, 64, WHITE);  // Draw rectangle (x,y,width,height,color)
                                            // It draws from the location to down-right
      display.fillRect(28, 0, 22, 64, WHITE);
      display.fillRect(53, 0, 22, 64, WHITE);
      display.fillRect(78, 0, 22, 64, WHITE);
      display.fillRect(103, 0, 22, 64, BLACK);
    }
  }

  last_millis = millis();
  display.display();  // Print everything we set previously
  last_button_state = button_state;
}
