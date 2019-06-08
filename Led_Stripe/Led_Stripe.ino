#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/ColorRGBA.h>

#define OFF 0
#define ON 1
#define BLUE_PIN 2
#define RED_PIN 3 
#define GREEN_PIN 4


ros::NodeHandle nh;

int blink_mode = 0;

int r = 0;
int b = 0;
int g = 0;

unsigned long last_millis = millis();
unsigned long current_millis = millis();

int led_state = 0;

void messageCb( const std_msgs::ColorRGBA& msg){
  r = (int)msg.r;
  g = (int)msg.g;
  b = (int)msg.b;
  blink_mode = (int)msg.a;
}

ros::Subscriber<std_msgs::ColorRGBA> sub_RGB("/Led_Stripe/RGB", &messageCb );

void setup()
{
  nh.initNode();
  nh.subscribe(sub_RGB);
  Serial.begin(57600);
  
  pinMode(BLUE_PIN,OUTPUT);
  pinMode(RED_PIN,OUTPUT);
  pinMode(GREEN_PIN,OUTPUT);
}
void loop()
{
  if(blink_mode > OFF){
    current_millis = millis();
    if (current_millis - last_millis > blink_mode){
      if (led_state == 1){
        analogWrite(BLUE_PIN,0);
        analogWrite(RED_PIN,0);
        analogWrite(GREEN_PIN,0);
        led_state = 0;
      }else {
        analogWrite(BLUE_PIN,b);
        analogWrite(RED_PIN,r);
        analogWrite(GREEN_PIN,g);
        led_state = 1;
      }
      last_millis = current_millis;
    }
  }
  else{
    analogWrite(BLUE_PIN,b);
    analogWrite(RED_PIN,r);
    analogWrite(GREEN_PIN,g);
    led_state = 1;
  }
  nh.spinOnce();
}
