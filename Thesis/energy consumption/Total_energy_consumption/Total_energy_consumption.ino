const int sensorIn = A0;      // pin where the OUT pin from sensor is connected on Arduino
int mVperAmp = 66;           // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
int Watt = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
double Wh =0 ;
unsigned long last_time = 0;
unsigned long current_time = 0;
 
 
void setup() {
  Serial.begin (115200); 
  Serial.println ("ACS712 current sensor"); 
     
}
 
void loop() {
 
  Serial.println ("");
  
  Voltage = getVPP();
  VRMS = (Voltage/2.0) *0.707;   //root 2 is 0.707
  Serial.print("Vrms: ");
  Serial.print(VRMS);
  Serial.print(" volts --->");
  AmpsRMS = (VRMS * 1000)/mVperAmp;
 
  Serial.print(" Irms: ");
  Serial.print(AmpsRMS);
  Serial.print(" A --->");
  Watt = (AmpsRMS*240/1.3);
  Serial.print(" Power: ");      // 1.3 is an empirical calibration factor
  Serial.print(Watt);
  Serial.print(" W --->");
  last_time = current_time;
  current_time = millis();
  Wh = Wh + Watt *((current_time - last_time)/3600000.0);
  Serial.print("watt_hour: ");
  Serial.print(Wh);
  Serial.println(" Wh --->");
  Serial.println("Energy consumption Per day ");
  double Unit = Wh/1000;
  Serial.print("units: ");
  Serial.println(Unit);
}
 
 
float getVPP()
{
  float result;
  int readValue;                // value read from the sensor
  int maxValue = 0;             // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 3000) //sample for 1 Sec
   {
    readValue = analogRead(sensorIn);
    // see if you have a new maxValue
    if (readValue > maxValue) 
    {
      /*record the maximum sensor value*/
      maxValue = readValue;
    }
    if (readValue < minValue) 
    {
      /*record the minimum sensor value*/
      minValue = readValue;
    }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
   Serial.print("\nVp-p:  ");
   Serial.println(String(result, 3));   
   return result;
 }