/*
 SD card datalogger
 	
 Carte SD associée au bus SPI comme suit :
 MOSI - pin 11
 MISO - pin 12
 CLK - pin 13
 CS - pin 10
 
 16 Juillet 2014

 Robin Beilvert
*/ 	

#include <SD.h>

// Even if it's not used as the CS pin, the hardware CS pin 
// (10 on most Arduino boards,n53 on the Mega) must be left 
// as an output or the SD library functions will not work.

const int chipSelect = 10;

int analogPin = 0; 

// Nombre d'échantillons à moyenner:
int nEch = 10;
// Période d'échantillonage en millisecondes:
int periode = 300;
// PERIODE D'ECHANTILLONAGE FINALE = nEch*periode.


// Tableau pour ranger les données des 6 entrées analogiques:
unsigned long sensorValue[4] = {0};

// Chaîne de caractères pour écrire les valeurs:
String dataString = "";


// SETUP : Cette fonction ne s'exécute qu'une fois au 
// démarrage de la carte ou quand on appuie sur le bouton de reset: 
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  /*  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  */

  Serial.print("Initialisation de la carte SD... ");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // Vérifie la présence et l'initialisabilité de la carte SD:
  if (!SD.begin(chipSelect)) {
    Serial.println("Carte defectueuse ou non presente");
    // don't do anything more:
    return;
  }
  Serial.println("Carte initialisée.");
  
  // Ouverture du fichier. Un seul fichier peut être ouvert à la fois,
  // il faut fermer celui-ci avant d'en ouvrir un autre.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // Écrire dans le fichier si il est disponible:
  if (dataFile) {
    dataString="Temps,Sonde 1,Sonde 2,Sonde 3,Sonde 4";
    dataFile.println(dataString);
    dataFile.close();
    
    // Écrire aussi sur le port série:
    Serial.println(dataString);
  }  
  // Si le fichier n'est pas ouvert, afficher une erreur:
  else {
    Serial.println("error opening datalog.txt");
  } 
}

void loop()
{
  // Rénitialisation de la chaîne de caractères:
  dataString = "" ;
  // Rénitialisation du tableau de valeurs:
  for(int i=0; i<4; i++) {
     sensorValue[i] = 0;
  }
  
  // Moyenne sur nEch échantillons:
  for (int i=0; i<nEch; i++) {
    
    // Lire 4 entrées et les ajouter dans le tableau sensorValue:
    for (int analogPin = 0; analogPin < 4; analogPin++) {
      sensorValue[analogPin] += analogRead(analogPin);
      
      // Si on a atteint la dernière boucle, faire les moyennes et 
      // les écrire dans dataString:    
      if (i == nEch-1){
        // Ecrire depuis combien de temps le programme tourne:
        if (analogPin == 0) {
          dataString += String(millis()/1000);
          dataString += ",";
        }
        sensorValue[analogPin] /= nEch;
        dataString += String(sensorValue[analogPin]);
        if (analogPin<3) {
          dataString +=",";
        }
      }          
    }
    delay(periode);
  }
  

  
  // Ouverture du fichier.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // Écrire dans le fichier si il est disponible:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    
    // Écrire aussi sur le port série:
    Serial.println(dataString);
  }  
  // Si le fichier n'est pas ouvert, afficher une erreur:
  else {
    Serial.println("error opening datalog.txt");
  } 
}









