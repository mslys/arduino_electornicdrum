/*Arduino-Drum by Michal Slys*/

#include <MIDI.h> 
MIDI_CREATE_DEFAULT_INSTANCE();

//analog Arduino's inputs
const int Pad1 = A0;
const int Pad2 = A1;
const int Pad3 = A2;
const int Pad4 = A3;
const int Pad5 = A4;

//volume threshold variable, being used to determine
//if user stikes the drum pad
const int volumeThreshold = 380;

//variables for volume magnitude of each drum pad
int Drum1_val = 0;
int Drum2_val = 0;
int Drum3_val = 0;
int Drum4_val = 0;
int Drum5_val = 0;

//variables used in program logic
//variables used in proces of separation of vibrtion from
//exact force impact
int signalTest2 = 0;
int signalTest1 = 0;
int signalTest3 = 0;
int signalTest4 = 0;
int signalTest5 = 0;

//midi mapping - addictive drums mapping
byte snareDrum = 38;
byte kick = 36; 
byte hihatClosed = 53;
byte crash = 77;
byte hihatOpened = 56;

void setup()
{
  MIDI.begin(4);
  //starts serial communication between arduino na serial USB port
  Serial.begin(115200); 
}

void loop()
{ 
  /*1st pad*/
  //checks if magnitude of analoginput is higher than volumeThreshold
  if(analogRead(Pad1) >= volumeThreshold) 
  {
  signalTest1 = 1;
  }
  //if magnitude of analoginput was higher than volumeThreshold
  //program checks again if the signal is decreasing
  //if so, it means that drum pad was hit
  if(signalTest1 == 1 && analogRead(Pad1) <= (volumeThreshold-100))
  {
    //sets the velocity
    Drum1_val= analogRead(Pad1);
    int velocity = Drum1_val/3 + 78;
    if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;

    //sends midi signal over USB serial port
    MIDI.sendNoteOn(hihatOpened, velocity, 1);
    MIDI.sendNoteOff(hihatOpened, 0, 1);
    //sets signalTest again to 0
    signalTest1 = 0;
  }

  /*2nd pad*/
  if(analogRead(Pad2) >= volumeThreshold) 
  {
  signalTest2 = 1;
  } 
  Drum2_val = analogRead(Pad2);
  if(signalTest2 == 1 && analogRead(Pad2) <= (volumeThreshold-95))
  {
   Drum2_val= analogRead(Pad2);
   int velocity = Drum2_val/3 + 35;
   
   if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;  
      
    MIDI.sendNoteOn(snareDrum, velocity, 1);
    MIDI.sendNoteOff(snareDrum, 0, 1);
    signalTest2 = 0;
  }

  /*3rd pad*/
  if(analogRead(Pad3) >= volumeThreshold) 
  {
  signalTest3 = 1; 
  }
  Drum3_val = analogRead(Pad3);
  if(signalTest3 == 1 && analogRead(Pad3) <= (volumeThreshold-95))
  {
   Drum3_val= analogRead(Pad3);
   int velocity = Drum3_val/2 + 77;
   
   if(velocity >= 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;
      
    MIDI.sendNoteOn(hihatClosed, velocity, 1);
    MIDI.sendNoteOff(hihatClosed, 0, 1);
    signalTest3 = 0;
  }

  /*4th pad*/
  if(analogRead(Pad4) >= volumeThreshold) 
  {
  signalTest4 = 1; 
  }
  if(signalTest4 == 1 && analogRead(Pad4) <= (volumeThreshold-95))
  {
   Drum4_val= analogRead(Pad4);
   int velocity = Drum4_val/3 + 75;
   
   if(velocity > 120)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;  
      
    MIDI.sendNoteOn(crash, velocity, 1);
    MIDI.sendNoteOff(crash, 0, 1);
    signalTest4 = 0;
  }

  /*5th pad*/
  if(analogRead(Pad5) >= volumeThreshold) 
  {
  signalTest5 = 1; 
  Drum5_val = analogRead(Pad5);
  }
  if(signalTest5 == 1 && analogRead(Pad5) <= (volumeThreshold-95))
  {
   int velocity = Drum5_val; 
   if(velocity >= 12)
      velocity = 125;
    else if(velocity < 0)
      velocity = 0;   
       
    MIDI.sendNoteOn(kick, velocity, 1);
    MIDI.sendNoteOff(kick, 0, 1);
    signalTest5 = 0;
  }
}
