const int button1Pin=1;
const int button2Pin=2;
const int potPin=A0;


void setup()
{
  pinMode(potPin,INPUT);
  pinMode(button1Pin,INPUT);
  pinMode(button2Pin,INPUT);
}

void loop()
{
  while (digitalRead(button1Pin)==1 && digitalRead(button2Pin)==0)
  {
    tone(13,analogRead(potPin)/3);             //Fréquence fondamentale
  }
  while (digitalRead(button2Pin)==1 && digitalRead(button1Pin)==0)
  {
    tone(13,1.122462*analogRead(potPin)/3);    //On monte de 1 ton en multipliant par (2^(-12))^2 (2 fois un demi ton)
  }
  while (digitalRead(button1Pin)==1 && digitalRead(button2Pin)==1)
  {
    tone(13,1.259921*analogRead(potPin)/3);    //On monte de 2 tons en multipliant par (2^(-12))^4 (4 fois un demi ton)
  }
  delay(10);
  noTone(13);
}

