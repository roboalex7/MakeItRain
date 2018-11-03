int sensorValue = 0;
int groundState = 256;
int maxVal = 512;
int minVal = 0;
int sampleWindow = 100;



void setup() 
{
  Serial.begin(9600);
}



int findMaxAmplitude(int period)
{
  unsigned long startTime = millis();
  int maxReading = 0;
  int minReading = 1023;
  
  while (millis() - startTime < period)
  {
    int rawInput = analogRead(0);
    
    if (rawInput > maxReading)
      maxReading = rawInput;
    if (rawInput < minReading)
      minReading = rawInput;
  }
  
  int amplitude = maxReading - minReading;
  return amplitude;
}



void printData(int value1, int value2)
{
  //Print the desired value(s)
  Serial.print(value1); 
  Serial.print(",");
  Serial.print(value2);
  Serial.print(",");
  //Print the ground state
  Serial.print(groundState); 
  Serial.print(",");
  //Force upper and lower bounds to prevent autoscaling
  Serial.print(maxVal);
  Serial.print(",");
  Serial.println(minVal);
}



void loop() 
{
  sensorValue = analogRead(0);
  int soundLevel = findMaxAmplitude(sampleWindow)/2;
  
  printData(sensorValue, soundLevel + groundState);
}
