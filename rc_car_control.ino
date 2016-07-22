unsigned long timer[5];
byte last_channel[2];
int input[2];

void setup() {
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  Serial.begin(9600);
}

void loop() {
  print();
}

ISR(PCINT0_vect) {
  timer[0] = micros();
  // channel 1 ---------------
  if(last_channel[0] == 0 && PINB & B00000001 ) {
    last_channel[0] = 1;
    timer[1] = timer[0];
  }
  else if(last_channel[0] == 1 && !(PINB & B00000001) ) {
    last_channel[0] = 0;
    input[0] = timer[0] - timer[1];
  }
  
  // channel 2 ---------------
  if(last_channel[1] == 0 && PINB & B00000010 ) {
    last_channel[1] = 1;
    timer[2] = timer[0];
  }
  else if(last_channel[1] == 1 && !(PINB & B00000010) ) {
    last_channel[1] = 0;
    input[1] = timer[0] - timer[2];
  }
}

void print() {
  Serial.print(input[0]);
  Serial.print(" - ");
  Serial.println(input[1]);
}

