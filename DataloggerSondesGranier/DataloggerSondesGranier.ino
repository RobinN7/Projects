/*
 SD card datalogger
 	
 Carte SD associée au bus SPI comme suit :
 MOSI - pin 11
 MISO - pin 12
 CLK - pin 13
 CS - pin 4
 
 16 Juillet 2014

 Robin Beilvert
*/ 	

#include <SD.h>

// Even if it's not used as the CS pin, the hardware CS pin 
// (10 on most Arduino boards,n53 on the Mega) must be left 
// as an output or the SD library functions will not work.

const int chipSelect = 10;

int analogPin = 0; 

// integer to store the read value from analogPin:
int value = 0;

// make an empty string for assembling the data to log:
String dataString = "";

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
/*  
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
*/

  Serial.print("Initialisation de la carte SD...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Carte defectueuse ou non presente");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  value = analogRead(analogPin);
  dataString = String(value);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
}









