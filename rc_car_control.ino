// foward --------------------------------------
const int Channel0_MAX = 1050; //1094=1104-10
//const int Channel0_MID = 1504;
const int Channel0_MIN = 1958; //1948+10
int Channel0_interval = 0;

// right and left -------------------------------
const int Channel1_MAX = 1950; //1940+10
//const int Channel1_MID = 1520;
const int Channel1_MIN = 1086; //1096-10
int Channel1_interval = 0;

// Speed output ---------------------------------
int RightWheel = 0;
int LeftWheel = 0;

unsigned long timer[5];
byte last_channel[2];
int input[2];
float input_percent[2];

void setup() {
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  Serial.begin(9600);
  Channel0_interval = abs(Channel0_MAX-Channel0_MIN);
  Channel1_interval = abs(Channel1_MAX-Channel1_MIN);  
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
    if (input[0]>Channel0_MIN) input[0]=Channel0_MIN;
    if (input[0]<Channel0_MAX) input[0]=Channel0_MAX;
  }
  
  // channel 2 ---------------
  if(last_channel[1] == 0 && PINB & B00000010 ) {
    last_channel[1] = 1;
    timer[2] = timer[0];
  }
  else if(last_channel[1] == 1 && !(PINB & B00000010) ) {
    last_channel[1] = 0;
    input[1] = timer[0] - timer[2];
    if (input[1]<Channel1_MIN) input[1]=Channel1_MIN;
    if (input[1]>Channel1_MAX) input[1]=Channel1_MAX;
  }
}

void print() {
  input_percent[0] = ((float)input[0]-(float)Channel0_MAX)/(float)Channel0_interval;
  input_percent[1] = ((float)input[1]-(float)Channel1_MIN)/(float)Channel1_interval;
  Serial.print(input_percent[0]);
  Serial.print(" - ");
  Serial.println(input_percent[1]);
}

void SpeedUpdate() {
  
}
