/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
 
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;
int prevButton1 = 1;
int prevButton2 = 1;

int notes[7] = {220, 246, 261, 293, 329, 349, 391};
int note_iter = 2;
float conversion = 0.46;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT);
  
  pinMode(13, OUTPUT);  
  pinMode(12, OUTPUT);  
  pinMode(11, OUTPUT);  
  pinMode(10, OUTPUT);  
  pinMode(9, OUTPUT);  
  pinMode(8, OUTPUT);  
  pinMode(7, OUTPUT);  
  pinMode(6, OUTPUT);  
  
  // timer1
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 240;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 64 prescaler
  TCCR1B |= (1 << CS11) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();
}


void writeByte(int x) {
  int pin;
  
  //PORTD: 0 - 7
  //PORTB: 8 - 13
  PORTD = ~(x << 6);
  PORTB = ~(x >> 2);
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;

ISR(TIMER1_COMPA_vect){
  counter += stride;
  if (counter > high) {
    counter = low;
  }

  // write to the digital pins  
  writeByte(counter);
}

void loop() {
  int button1 = digitalRead(buttonPin1);
  int button2 = digitalRead(buttonPin2);
  int i = note_iter - button1 + button2 + 1; 
  OCR1A = (int) (conversion * notes[i]);
}
