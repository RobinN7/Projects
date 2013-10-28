//Project created by Proux Alexandre and Beilvert Robin
//The aim of this project is to control a robot arm manually or automatically.

////////////////////////////////////////////////////////
/////// PINS USED AS PWM : (3) 5 6 9 10 11 (13) ////////
////////////////////////////////////////////////////////


//////////////////// USER INTERACTIONS ///////////////////////

int tu=0; // Select Translate Up
int td=1; // Select Translate Down
int tl=2; // Select Translate Left
int tr=3; // Select Translate Right
int tb=4; // Select Translate Backward
int tf=7; // Select Translate Forward

int thu=8; // Select Turn Hand Up
int thd=12; // Select Turn Hand Down

//////////////////// OUTPUT ACTIONS /////////////////////////

int uodr=5; // Up Or Down Rotation -> Turn UP if 1, Down if 0

int br=6; // Base Rotation
int sr=9; // Shoulder Rotation
int er=10; // Elbow Rotation
int hr=11; // Hand Rotation

int ledPin=13; // Indicates the curring mode : Manual (Yellow LED) if 1, Automatic (Green LED) if 0

////////////////////// ENSLAVEMENT /////////////////////////

int motorChoice(void); // Declaration de la fonction qui determine quelle moteur doit etre actionné

//////////////////// PIN DECLARATION ///////////////////////

void setup()
{
  pinMode (uodr,OUTPUT); // Up Or Down Rotation -> Turn UP if 1, Down if 0
  
  pinMode (br,OUTPUT); // Base Rotation
  pinMode (sr,OUTPUT); // Shoulder Rotation
  pinMode (er,OUTPUT); // Elbow Rotation
  pinMode (hr,OUTPUT); // Hand Rotation
  
  pinMode (tu,INPUT); // Select Translate Up
  pinMode (td,INPUT); // Select Translate Down
  pinMode (tl,INPUT); // Select Translate Left
  pinMode (tr,INPUT); // Select Translate Right
  pinMode (tb,INPUT); // Select Translate Backward
  pinMode (tf,INPUT); // Select Translate Forward
}

////////////////////// MAIN PROGRAM ////////////////////////

void loop()
{
  buttonG=digitalRead (0);
  buttonD=digitalRead (6);
  choixmoteur();
  
//////////////////////////DEBUT WHILE///////////////////////////////

 while(buttonG==1 || buttonD==1)        //Une ROTATION est demandée
  {
  
    if (buttonG==1 && buttonD==0)       //On demande ROTATION GAUCHE
    {
       digitalWrite (7,1); //On tourne à gauche
   
       switch (choixmoteur())
       {
         case 1 : digitalWrite (1,1);
         break;
         case 2 : digitalWrite (2,1);
         break;
         case 3 : digitalWrite (3,1);
         break;
         case 4 : digitalWrite (4,1);
         break;
         case 5 : digitalWrite (5,1);
         break;

       }
     }
     else                               //On demande ROTATION DROITE
     {
       digitalWrite (7,1); //On tourne à droite
 
       switch (choixmoteur())
       {
         case 1 : digitalWrite (1,1);
         break;
         case 2 : digitalWrite (2,1);
         break;
         case 3 : digitalWrite (3,1);
         break;
         case 4 : digitalWrite (4,1);
         break;
         case 5 : digitalWrite (5,1);
         break;
       }
   }
   
digitalWrite (1,0);        //
digitalWrite (2,0);        //
digitalWrite (3,0);        // Aucune ROTATION n'est demandée, on éteint tout 
digitalWrite (4,0);        // (à remplacer par asservissement par la suite)
digitalWrite (5,0);        //

}

//////////////////////////FIN WHILE///////////////////////////////
  
delay(30);
  
  
}



int choixmoteur(void)
{ 
  
int inter=0;

  button1=digitalRead (1);
  button2=digitalRead (2);
  button3=digitalRead (3);
  button4=digitalRead (4);
  button5=digitalRead (5);
  
  if (button1==1 && button2==0 && button3==0 && button3==0 && button5==0)
  {
    inter=1;
  }
  else if (button2==1 && button1==0 && button3==0 && button5==0 && button4==0)
  {
    inter=2;  
  }
    else if (button3==1 && button1==0 && button2==0 && button5==0 && button4==0)
  {
    inter=3;
  }
    else if (button4==1&& button1==0 && button2==0 && button5==0 && button3==0)
  {
    inter=4;
  }
  else if (button5==1 && button4==0 && button1==0 && button2==0 && button5==0 && button3==0)
  {
    inter=5;
  }
  
  else
  {
    inter=0;
  }
 
 return inter;  
  
}

