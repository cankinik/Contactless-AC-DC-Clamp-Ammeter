#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 2, 4, 5, 6, 7); 

double startTime=0;
long sum =0;
int count =0;
int maxV = 0;
int minV = 1024;
double voltage = 0;
double ampere = 0;
double voltageDifference = 0;
double RMSAmpere = 0;
int differenceAmount = 0;
boolean calibrate = false;
int calibrationVoltage = 0;

//For frequency
int maxVf = 0;
int minVf = 1024;
long time1;
long time2;
int oscillationCounter = 0;
double interval1 = 0;
double interval2 = 0;
double frequency = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(9, INPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(A4,INPUT);
}

void loop() {    
    calibrate = digitalRead(9);
    count++;
    int a =analogRead(A4);
    if (count <= 1000 )
    {      
       if (a > maxVf){maxVf = a;}
       if (a < minVf){minVf = a;}   
    }
    if ( count >= 1001 && count <= 2000 )
    {
      interval1 = maxVf - 5*(maxVf - minVf)/100;
      interval2 = maxVf - 10*(maxVf - minVf)/100;
      if ( a >= interval2 && a <= interval1 )
      {        
        if ( oscillationCounter == 0 )
        {
          time1 = millis();
        }
        if ( oscillationCounter == 4 )
        {
          time2 = millis();
        }
        delay(5);
        oscillationCounter++;
      }
    }
    if (count == 2001)
    {
      frequency = 1000/((time2 - time1)/4);
      oscillationCounter = 0;
      maxVf = 0;
      minVf = 1024;
    }

    sum += a;    
    /////calibration
    if(calibrate){
      calibrationVoltage = a;
      
    }
    /////
    if (a > maxV){maxV = a;}
    if (a < minV){minV = a;}  
    if(count == 10000)
    {              
      
      if(maxV - minV > 20 )
      {
        voltageDifference =  maxV - minV - differenceAmount;   
        RMSAmpere = ((voltageDifference)/2/92/1.414);  
        //AC
        Serial.println(maxV);
        lcd.clear();
        lcd.print("AC Ampere: ");
        lcd.print(RMSAmpere);
        lcd.setCursor(0, 2);
        lcd.print("F: ");
        lcd.print(frequency);
        lcd.print("Hz ");
        if( time1 == 0 && time2 == 0 )
        {
          lcd.print("Sq");
        }
        else
        {
          lcd.print("Sine");
        }
        time1 = 0;
        time2 = 0;
      }
      else
      {
        //DC    
        differenceAmount = maxV - minV;
        voltage = sum/10000;
        Serial.println(voltage);
        ampere = (voltage - (calibrationVoltage))/97;////////////////////
        lcd.clear();
        lcd.print("DC Ampere: ");
        lcd.print(ampere);
      }      
      maxV = 0;
      minV = 1024;
      sum = 0;
      count = 0;      
    }  
}
