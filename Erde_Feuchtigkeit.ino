////////////////////////////// I/O
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;
const int dot = 9;
const int c1 = 10;
const int c2 = 11;
const int c3 = 12;
const int c4 = 13;

////////////////////////////// Variablen
unsigned long timer_display = 0;
int display_wo = 1;
unsigned long timer_messen = 0;
int feuchtigkeit;

////////////////////////////// Konstanten
const byte b0 = 0b00111111; //Welche Segmente für welche Zahl angeschaltet werden müssen, hier 0
const byte b1 = 0b00000110; //1
const byte b2 = 0b01011011; //...
const byte b3 = 0b01001111;
const byte b4 = 0b01100110;
const byte b5 = 0b01101101;
const byte b6 = 0b01111101;
const byte b7 = 0b00000111;
const byte b8 = 0b01111111;
const byte b9 = 0b01101111;

////////////////////////////// Funktionen
void setDigit(int com, int zahl, bool punkt); //einzelnes Digit setzen
void setDisplay(int zahl); // bis 4 stellig Zahl ausgeben



void setup() {
  Serial.begin(9600);
  
  pinMode(a,OUTPUT); //Alle benötigten Pins auf OUTPUT
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(dot,OUTPUT);
  pinMode(c1,OUTPUT);
  pinMode(c2,OUTPUT);
  pinMode(c3,OUTPUT);
  pinMode(c4,OUTPUT);

  digitalWrite(a,LOW); //Alle auf aus setzen
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
  digitalWrite(dot,LOW);
  digitalWrite(c1,HIGH);
  digitalWrite(c2,HIGH);
  digitalWrite(c3,HIGH);
  digitalWrite(c4,HIGH);

  setDisplay(8888); //Alle Segmente  an, zur prüfung
  
}

void loop()
{
  if((timer_messen + 1000) < millis()) //Jede Sekunde Wert auslesen, Seriell ausgeben und in Variable speichern
  {
    feuchtigkeit= analogRead(A0);
    Serial.print("Feuchtigkeit: ");
    Serial.print(analogRead(A0));
    Serial.print("\n");
    analogWrite(A1,(200));
    timer_messen = millis();
  }

  setDisplay(feuchtigkeit); //Feuchtigkeit ausgeben
}



void setDigit(int com, int zahl, bool punkt)
{
  byte wahl;

  if(zahl == 0) wahl = b0; //zahl zu binärwerten zuordnen
  else if(zahl == 1) wahl = b1;
  else if(zahl == 2) wahl = b2;
  else if(zahl == 3) wahl = b3;
  else if(zahl == 4) wahl = b4;
  else if(zahl == 5) wahl = b5;
  else if(zahl == 6) wahl = b6;
  else if(zahl == 7) wahl = b7;
  else if(zahl == 8) wahl = b8;
  else if(zahl == 9) wahl = b9;

  digitalWrite(c2,HIGH); //alle Digits ausschalten
  digitalWrite(c3,HIGH);
  digitalWrite(c4,HIGH);
  digitalWrite(c1,HIGH);

  digitalWrite(a,bitRead(wahl,0)); //gewählte Konfiguration schreiben
  digitalWrite(b,bitRead(wahl,1));
  digitalWrite(c,bitRead(wahl,2));
  digitalWrite(d,bitRead(wahl,3));
  digitalWrite(e,bitRead(wahl,4));
  digitalWrite(f,bitRead(wahl,5));
  digitalWrite(g,bitRead(wahl,6));
  digitalWrite(dot,punkt);
  
  if(com == c1) //Gewünschter Digit anschalten
  {
    digitalWrite(c1,LOW);
  }
  else if(com == c2)
  {
    digitalWrite(c2,LOW);
  }
  else if(com == c3)
  {
    digitalWrite(c3,LOW);
  }
  else if(com == c4)
  {
    digitalWrite(c4,LOW);
  }
}

void setDisplay(int zahl)
{
  unsigned int intervall = 1000; //Intervall, wie lange jedes Segment an sein soll
    
  int einer = zahl % 10; //Erste Stelle berechnen
  int zehner = ((zahl -einer) % 100) / 10; //Zweite Stelle berechnen
  int hunderter = ((zahl-einer-(zehner*10)) % 1000) / 100; //dritte Stelle berechnen
  int tausender = (zahl - einer - (zehner*10) - (hunderter * 100))/1000; //vierte Stelle berechnen

  if(((timer_display + intervall) < micros()) && display_wo == 1) 
  {
    setDigit(c1,tausender,0);
    display_wo = 2;
  }
  else if(((timer_display + intervall*2) < micros()) && display_wo == 2)
  {
    setDigit(c2,hunderter,0);
    display_wo = 3;
  }
  else if(((timer_display + intervall*3) < micros()) && display_wo == 3)
  {
    setDigit(c3,zehner,0);
    display_wo = 4;
  }
  else if(((timer_display + intervall*4) < micros()) && display_wo == 4)
  {
    setDigit(c4,einer,0);
    display_wo = 1;
    timer_display = micros();
  }
}
