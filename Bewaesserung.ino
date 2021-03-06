//Konstanten
const int FeuchtWert1 = 400;
const int FeuchtWert2 = 400;
const int FeuchtWert3 = 400;
const int Bewaesserungszeit = 1000;
const int Checktime = 2000;

//Ports
const int MSensor1 = A0;
const int MSensor2 = A1;
const int MSensor3 = A2;
const int Pumpe1 = 2;
const int Pumpe2 = 3;
const int Pumpe3 = 4;

//Variablen
int feuchtigkeit1;
int feuchtigkeit2;
int feuchtigkeit3;

bool BAn1 = 0;
bool BAn2 = 0;
bool BAn3 = 0;

//Timer
unsigned long timer1 = 0;
unsigned long timer1_1 = 0;
unsigned long timer2 = 0;
unsigned long timer2_1 = 0;
unsigned long timer3 = 0;
unsigned long timer3_1 = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(Pumpe1,OUTPUT);
  pinMode(Pumpe2,OUTPUT);
  pinMode(Pumpe3,OUTPUT);

  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW);

}

void loop()
{
  if(millis() > (timer1 + 500)) //Sensor 1
  {
  feuchtigkeit1 = analogRead(MSensor1);
    if((feuchtigkeit1 > FeuchtWert1) && (millis() > timer1_1 + Checktime) && BAn1 == 0)
    {
      digitalWrite(Pumpe1,HIGH);
      BAn1 = 1;
      timer1_1 = millis();
      Serial.print("Pumpe1 an\n");
    }
    else if(BAn1 == 1 && (millis() > timer1_1 + Bewaesserungszeit))
    {
      digitalWrite(Pumpe1,LOW);
      BAn1 = 0;
      Serial.print("Pumpe1 aus\n");
    }
    timer1 = millis();
   }


  if(millis() > (timer2 + 500)) //Sensor 2
  {
  feuchtigkeit2 = analogRead(MSensor2);
    if((feuchtigkeit2 > FeuchtWert2) && (millis() > timer2_1 + Checktime) && BAn2 == 0)
    {
      digitalWrite(Pumpe2,HIGH);
      BAn2 = 1;
      timer2_1 = millis();
      Serial.print("Pumpe2 an\n");
    }
    else if(BAn2 == 1 && (millis() > timer2_1 + Bewaesserungszeit))
    {
      digitalWrite(Pumpe2,LOW);
      BAn2 = 0;
      Serial.print("Pumpe2 aus\n");
    }
    timer2 = millis();
   }

   if(millis() > (timer3 + 500)) //Sensor 3
  {
  feuchtigkeit3 = analogRead(MSensor3);
    if((feuchtigkeit3 > FeuchtWert3) && (millis() > timer3_1 + Checktime) && BAn3 == 0)
    {
      digitalWrite(Pumpe3,HIGH);
      BAn3 = 1;
      timer3_1 = millis();
      Serial.print("Pumpe3 an\n");
    }
    else if(BAn3 == 1 && (millis() > timer3_1 + Bewaesserungszeit))
    {
      digitalWrite(Pumpe3,LOW);
      BAn3 = 0;
      Serial.print("Pumpe3 aus\n");
    }
    timer3 = millis();
   }
}
