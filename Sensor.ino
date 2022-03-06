#include <dht.h>

#include <ezBuzzer.h>
#define Datapin A8
#define LED_Pin 22
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define Buzzer_PIN 13
dht DHT;

float Temperature = 0.0;
float Human = 0.0;

int PSD_Sensor = 0;
int PSD_Distance = 0;
int melodySize = 3;
int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4};
int noteDurations[] = {1,1,1};

int PSD_Read(int analogPin)
{
  int PSD_Value;
  PSD_Value = analogRead(analogPin);
  return PSD_Value;
}
int Calculate_Distance(int PSD_Value)
{
  int X;
  X = (6762 / (PSD_Value - 9)) - 4;
  return X;
}
void Temperature_Sensor_Readings()
{
  DHT.read11(Datapin);
  Temperature = DHT.temperature;
  Human = DHT.humidity;
}
void playBuzzer(int Freq, int PlayTime)
{
  tone(Buzzer_PIN, Freq, PlayTime);
}
void stopBuzzer()
{
  noTone(Buzzer_PIN);
}

void setup() {
  pinMode (LED_Pin, OUTPUT);
  Serial.begin(9600);
  for(int thisNote = 0; thisNote < melodySize; thisNote++)
  {
    int noteDuration = 10 / noteDurations[thisNote];
    playBuzzer(melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    stopBuzzer();
  }
}

void loop() {
  Temperature_Sensor_Readings();
  Serial.print("Temperature = ");
  Serial.println(Temperature);

  PSD_Sensor = PSD_Read(A2);
  PSD_Distance = Calculate_Distance (PSD_Sensor);
  //printf( PSD_Distance );
 Serial.print("Distance = " );
  Serial.println( PSD_Distance );
 //if()
  if (Temperature >= 30)
  {
    printf("High Temperature Reading \n");
    
    digitalWrite(LED_Pin,HIGH);
    playBuzzer(25, 100);
    stopBuzzer();
   
  }
  else 
  {
    printf("Normal Temperature Reading");
  }
  delay(2500);
}
