int sensorValue = 0;
const int thresh = 450;
const int sampleWindow = 30;
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
  for (int i = 0; i < samples; i++)
  {
    if (input[i] > thresh || input[i] < 512 - thresh)
      drops++; 
  }
  return drops;
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
    Serial.print(j);
    Serial.print("-Drops: ");
    Serial.println(countDrops(data));
    total += countDrops(data);
  }
  Serial.print("Total Drops:");
  Serial.println(total);
}
