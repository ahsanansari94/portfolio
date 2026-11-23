
//const int Sensor_Pin = A0;
float Vpp = 0; // peak-peak voltage 
float Vrms = 0; // rms voltage
float Irms = 0; // rms current
float Supply_Voltage = 233.0;           // reading from DMM
float Vcc = 5.0;         // ADC reference voltage // voltage at 5V pin 
float power = 0;         // power in watt              
float Wh =0 ;
unsigned int Sensitivity = 66;   // 185mV/A for 5A, 100 mV/A for 20A and 66mV/A for 30A Module
unsigned long last_time = 0;
unsigned long current_time = 0;
//unsigned int calibration = 100;  // V2 slider calibrates this
//unsigned int pF = 85;

void setup(){
  Serial.begin(9600);
  Serial.println("Energy Consumption");
}

void loop()
{
  Vpp = getVPP();
  Vrms = (Vpp/2.0) * 0.707;
  //Vrms = Vrms - (calibration /10000.0);
  Serial.print("Vrms: ");
  Serial.print(Vrms);
  Serial.println(" volts");
  Irms = (Vrms *1000)/Sensitivity;
  if((Irms > -0.015) && (Irms < 0.008)){
    Irms = 0.0;
  } 
  Serial.print("Irms: ");
  Serial.print(Irms);
  Serial.println(" A");
  power = (Supply_Voltage * Irms) *(pF/100);
  Serial.print("Power: ");
  Serial.print(power);
  Serial.println(" watt");  
  last_time = current_time;
  current_time = millis();
  Wh = Wh + power *((current_time - last_time)/3600000.0);
  Serial.print("watt hour: ");
  Serial.print(Wh);
  Serial.println(" Wh");
  Serial.println("Energy consumption Per day ");
  float Unit = Wh/1000;
  Serial.print("units: ");
  Serial.println(Unit);
  Serial.println();
}

float getVPP(){
  float result;
  int adc;
  int maxvalue =0;
  int minvalue =1024;
   uint32_t start_time = millis();
  while ((millis() - start_time) < 3000) //sample for 1 Sec
  {
    adc = analogRead(A0);
    //Serial.print("ADC_VALUE: ");
    //Serial.println(adc);
    if(adc > maxvalue)
    {
      maxvalue = adc;
    }
    if (adc < minvalue)
    {
      minvalue= adc;
    }
  }
    // Subtract min from max
  result = ((maxvalue - minvalue) * 5.0) / 1024.0;
  //Serial.print("ADC_VALUE: ");
  //Serial.println(result);
  return result;
}