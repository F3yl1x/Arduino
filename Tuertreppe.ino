#include <IRremote.h>
#include <Bounce2.h>

int IR_RECEIVE_PIN = 7;
bool m_zustand = 0;
bool m_an = 0;
unsigned long timer1;
unsigned long timer2 = 0;
bool m_empfangen = 0;
int Knopf = 4;
int Motor1 = 2;
int Motor2 = 3;
Bounce bounce = Bounce();

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, HIGH);
  bounce.attach(Knopf,INPUT);
  bounce.interval(100);
}

void loop() {
    if (IrReceiver.decode()) {

        if(IrReceiver.decodedIRData.command == 64 and millis()-timer2 > 2000)
        {
          m_empfangen =1;
          Serial.println(IrReceiver.decodedIRData.command);
          timer2= millis();
        }
        IrReceiver.resume();
    }

    bounce.update();
    if(bounce.changed())
    {
      int debouncedInput = bounce.fell();
      if( debouncedInput == LOW)
      {
        m_empfangen=1;
      }
    }
    

        if((m_zustand==0) and (m_empfangen == 1) and (m_an == 1))
        {
          digitalWrite(Motor1, LOW);
          m_zustand = 1;
          m_an= 0;
          m_empfangen = 0;
          Serial.println("Stoppt 1");
        }

        if((m_zustand==1) and (m_empfangen == 1) and (m_an == 1))
        {
          digitalWrite(Motor2, HIGH);
          Serial.println(m_zustand);
          m_zustand = 0;
          m_an= 0;
          m_empfangen = 0;
          Serial.println("Stoppt");
          Serial.println(m_zustand);
        }


        
        if((m_zustand==0) and (m_empfangen == 1) and (m_an == 0))
          {
            digitalWrite(Motor1, HIGH);
            timer1= millis();
            m_empfangen= 0;
            m_an = 1;
            Serial.println("Fährt hoch");
          }

          if((m_an == 1) and (m_zustand==0) and ((millis()-timer1)>40000))
          {
            digitalWrite(Motor1,LOW);
            m_zustand=1;
            m_an= 0;
            Serial.println("Ist oben");
          }


          if((m_zustand==1) and (m_empfangen == 1) and (m_an == 0))
          {
            digitalWrite(Motor2, LOW);
            timer1= millis();
            m_empfangen= 0;
            m_an = 1;
            Serial.println("runter");
          }

          if((m_an == 1) and (m_zustand==1) and ((millis()-timer1)>40000))
          {
            digitalWrite(Motor2,HIGH);
            m_zustand=0;
            m_an= 0;
            Serial.println("Ist unten");
          }
        

    
}
