int sensorValue = 0;
const int thresh = 450;
const int sampleWindow = 10;
const int wait = 5;
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
  Serial.print("Volume = ");
  Serial.println(volume);
  float depth = volume / 35.91; //Area of sensor in cm^2
  Serial.print("Depth = ");
  Serial.println(depth);
  float rate = (depth * 360);
  Serial.print("Rate = ");
  Serial.print(rate);
  Serial.println("cm/hr");
}


void loop() 
{
  int total = 0;

  for (int j = 1; j <= sampleWindow/5; j++)  
  {
    for (int i = 0; i < samples; i++)
    {
      data[i] = analogRead(0); 
      delay(wait);
    }
    //printData(data);
    //Serial.print(j);
    //Serial.print("-Drops: ");
    //Serial.println(countDrops(data));
    total += countDrops(data);
  }
  Serial.print("Total Drops:");
  Serial.println(total);
  dropsToIntensity(total);
}
