int sensorValue = 0;

const int thresh = 450;
const int sampleWindow = 10;
const int samples = 1000;

int data[samples];



void setup() 
{
  Serial.begin(9600);
}



void printData(int input[])
{
  for (int i = 0; i < samples; i++)
  {
    Serial.print(input[i]);
    Serial.print(", ");
  }
   Serial.println(' ');
}



int countDrops(int input[])
{
  int drops = 0;
  for (int i = 3; i < samples; i++)
  {
    bool duplicate = false;
    if (input[i] > thresh || input[i] < (512 - thresh))
    {
      for (int j = 1; j <= 3; j++)
      {
        if (input[i - j] > thresh || input[i-j] < (512 - thresh))
        {
          //Serial.println("Duplicate Point Detected");
          duplicate = true;
        }
        
      }
      
      if (!duplicate)
        drops++;
    }
  }
  return drops;
}



float dropsToIntensity(int drops)
{
  float volume = drops / 28.5;
  float depth = volume / 35.91; //Area of sensor in cm^2
  float rate = (depth * 360);
  
  Serial.print("Rate = ");
  Serial.print(rate);
  Serial.println("cm/hr");
  
  return rate;
}



void relativeIntensity(float intensity)
{
  if (intensity == 0)
    Serial.println("No rain detected");
  else if (intensity < 0.25)
    Serial.println("Light rain detected");
  else if (intensity >= 0.25 && intensity <= 0.76)
    Serial.println("Moderate rain detected");
  else if (intensity > 0.76)
    Serial.println("Heavy rain detected");
  else return;
}



void loop() 
{
  int total = 0;

  for (int j = 1; j <= sampleWindow/5; j++)  
  {
    for (int i = 0; i < samples; i++)
    {
      data[i] = analogRead(0); 
      delay(5);
    }
    
    total += countDrops(data);
  }
  
  Serial.print("Total Drops:");
  Serial.println(total);
  
  float intensity = dropsToIntensity(total);
  relativeIntensity(intensity);
  
  Serial.println(' ');
}
