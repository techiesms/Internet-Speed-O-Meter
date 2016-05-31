/*
  Internet Speed-O-Meter
  code by:- Sachin Soni(techiesms)

 */
#define DEBUG true
#define Red 8
#define Yellow 9
#define Green 10

String Host_name="SSID name";
String Password="Password";


String ANS="";
int i=0;


void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  Serial1.begin(115200); // Serial 1 of Mega
  pinMode(Red,OUTPUT);
  pinMode(Yellow,OUTPUT);
  pinMode(Green,OUTPUT);
  
   char inv='"';
   String add="AT+CWJAP";
        add+="=";
        add+=inv;
        add+=Host_name;
        add+=inv;
        add+=",";
        add+=inv;
        add+=Password;
        add+=inv;
        add+="\r\n";
 ANS=sendData(add,5000,0);
     
}

void loop() {
  delay(2000);
int i=0;
  char inv='"';
   String add="AT+PING"; 
        add+="=";
        add+=inv;
        add+="www.google.com";
        add+=inv;
        add+="\r\n";
 ANS=sendData(add,2000,0);  // AT+PING="www.google.com"

Serial.println(ANS);

while(ANS.charAt(i)!='+')
i++;
i++;
ANS=ANS.substring(i);
i=0;
 while(ANS.charAt(i)!='+')
i++;
i++;
ANS=ANS.substring(i,i+5);
 
int speedo= ANS.toInt();  // Conversion from String to Int

if(speedo==0)
{
Serial.println("No Connection");
digitalWrite(Red,HIGH);
digitalWrite(Yellow,LOW);
digitalWrite(Green,LOW);
}
if(speedo>0 && speedo<=500)
{
Serial.println("High Speed");
digitalWrite(Red,LOW);
digitalWrite(Yellow,LOW);
digitalWrite(Green,HIGH);
}
if(speedo>500 && speedo<=1000)
{
Serial.println("Slow Speed");
digitalWrite(Red,LOW);
digitalWrite(Yellow,HIGH);
digitalWrite(Green,LOW);
}
     
    
     
   
   
   
  
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial1.print(command); // send the read character to the Serial1
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial1.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = Serial1.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

 

 

