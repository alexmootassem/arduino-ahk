/* Arduino USB Keyboard HID
 * Auto Hot Key
 */
 
#define KEY_ONE   0x1e
#define KEY_TWO	  0x1f
#define KEY_THREE 0x20
#define KEY_FOUR  0x21

uint8_t buf[8] = { 0 }; 	/* Keyboard report buffer */
 
#define PIN_TURN_ON 5
#define PIN_TURN_OFF 6

int led = 13;
int state = 1;
boolean active = false;
unsigned long last_time = 0;
 
void setup() 
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(PIN_TURN_ON, INPUT);
  digitalWrite(PIN_TURN_ON, 1);
  pinMode(PIN_TURN_OFF, INPUT);
  digitalWrite(PIN_TURN_OFF, 1);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  delay(200);
}
 
void loop() 
{
  state = digitalRead(PIN_TURN_ON);
  if (state != 1) {
    active = true;
    digitalWrite(led, HIGH);
  }
  
  state = digitalRead(PIN_TURN_OFF);
  if (state != 1) {
    active = false;
    last_time = 0;
    digitalWrite(led, LOW);
  }
  
  if (active == true) {
    unsigned long delta = millis() - last_time;
    if (delta > random(10000, 20000)) {
//      sendKey(0x15);
//      sendKey(KEY_ONE);
//      sendKey(KEY_TWO);
      sendKey(KEY_THREE);
      sendKey(KEY_FOUR);
      last_time = millis();
    }
  }
}

void sendKey(uint8_t key)
{
  buf[0] = 0;
  buf[2] = key;
  Serial.write(buf, 8);	// Send keypress
  releaseKey();
  delay(random(148, 489));  
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);	// Release key  
}
