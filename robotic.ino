//ΧΡΗΣΗ ΒΙΒΛΙΟΘΗΚΩΝ
#include "VirtuinoEsp8266_WebServer.h"
#include <VarSpeedServo.h>

//ΟΡΙΣΜΟΣ ΜΕΤΑΒΛΗΤΩΝ
VarSpeedServo myservo_base;  
VarSpeedServo myservo_armlow;
VarSpeedServo myservo_armhigh;
VarSpeedServo myservo_gripbase;
VarSpeedServo myservo_grip;
int oldPosBase=30;
int oldPosArmlow=90;
int oldPosArmhigh=90;
int oldPosGripbase=10;
int oldPosGrip=0;
boolean StopDemo=false; 
VirtuinoEsp8266_WebServer virtuino(Serial); 

  
void setup(){

//ΑΠΕΝΕΡΓΟΠΟΙΟΥΜΕ ΤΟ DEBUG ΓΙΑΤΙ ΣΤΕΛΝΕΙ ΔΕΔΟΜΕΝΑ ΣΤΗΝ USART ΚΑΙ ΜΠΕΡΔΕΥΕΙ ΤΟ ESP8266
  virtuino.DEBUG=false;                                            
//ΕΝΑΡΞΗ ΣΕΙΡΙΑΚΗΕ ΕΠΙΚΟΙΝΩΝΙΑΣ ΜΕ ΤΟ ESP8266  
  Serial.begin(115200);
   delay(2000);
//ΑΡΧΙΚΟΠΟΙΗΣΗ ΤΟΥ WEB SERVER ΠΟΥ ΤΡΕΧΕΙ ΣΤΟ ESP8266 ΜΕ ΧΡΗΣΗ ΕΝΤΟΛΩΝ AT
  Serial.println("AT\r\n");  
  Serial.println("AT+GMR");
  delay(500);
  Serial.println("AT+CWMODE=2");  // ΟΡΙΣΜΟΣ ESP8266 ΩΣ WIFI SPOT
  delay(500);
  Serial.println("AT+CIFSR");
  delay(500);
  Serial.print("AT+CWSAP=\"");  //ΟΡΙΣΜΟΣ WIFI SSID ΚΑΙ PASSWORD
  Serial.print("RoboticArm");
  Serial.print("\",\"");
  Serial.print("alekos123");
  Serial.println("\",2,3");
  delay(500);
  Serial.println("AT+CIPMUX=1");         
  delay(500);
  Serial.print("AT+CIPSERVER=1,80");
  delay(500);


  //ΑΡΧΙΚΟΠΟΙΗΣΗ ΕΙΚΟΝΙΚΩΝ ΜΕΤΑΒΛΗΤΩΝ ΤΟΥ VIRTUINO.
  //ΑΥΤΕΣ ΑΝΤΙΣΤΟΙΧΟΥΝ ΣΕ ΕΙΚΟΝΙΚΑ PINS                       
  virtuino.vMemoryWrite(0, oldPosBase); 
  virtuino.vMemoryWrite(1, oldPosArmlow);  
  virtuino.vMemoryWrite(2, oldPosArmhigh);  
  virtuino.vMemoryWrite(3, oldPosGripbase);  
  virtuino.vMemoryWrite(4, oldPosGrip); 
  virtuino.vMemoryWrite(5, 0);   
  //ΜΕΤΑΚΙΝΗΣΗ ΤΩΝ ΣΕΡΒΟΚΙΝΗΤΗΡΩΝ ΣΤΙΣ ΑΡΧΙΚΕΣ ΤΟΥΣ ΘΕΣΕΙΣ
  myservo_base.attach(5); 
  myservo_base.write(42); 
  delay(500);
  myservo_armlow.attach(6);  
  myservo_armlow.write(100); 
  delay(500);
  myservo_armhigh.attach(9);  
  myservo_armhigh.write(90); 
  delay(500);
  myservo_gripbase.attach(10);  
  myservo_gripbase.write(35); 
  delay(500);
  myservo_grip.attach(11);  
  myservo_grip.write(0); 
  delay(500);               
  
} 

void loop(){
     //ΕΚΚΙΝΗΣΗ ΤΟΥ VIRTUINO SERVER
     virtuino.run();           
     // Ο ΠΑΡΑΚΑΤΩ ΚΩΔΙΚΑΣ ΕΛΕΧΓΕΙ ΕΑΝ ΕΧΕΙ ΑΛΛΑΞΕΙ ΚΑΠΟΙΑ ΤΙΜΗ ΑΠΟ ΤΙΣ ΓΩΝΙΕΣ ΤΩΝ ΣΕΡΒΟΚΙΝΗΤΗΡΩΝ ΑΠΟ ΤΗΝ ΕΦΑΡΜΟΓΗ WEB
     // ΚΑΙ ΜΕΤΑΚΙΝΕΙ ΤΟΝ ΣΕΡΒΟ ΣΤΗΝ ΘΕΣΗ ΑΥΤΗ
     int pos=virtuino.vMemoryRead(0);         // ΒΑΣΗ ΒΡΑΧΙΟΝΑ
     if (pos!=oldPosBase) {
      myservo_base.write(pos,20);  
     
     }
     oldPosBase=pos;

     pos=virtuino.vMemoryRead(1);         // ΚΛΕΙΔΩΣΗ ΣΤΗΝ ΒΑΣΗ
     if (pos!=oldPosArmlow) {
      myservo_armlow.write(pos);  
     
     }
     oldPosArmlow=pos;
  

     pos=virtuino.vMemoryRead(2);         // ΑΝΩ ΚΛΕΙΔΩΣΗ
     if (pos!=oldPosArmhigh) {
      myservo_armhigh.write(pos);  
    
     }
     oldPosArmhigh=pos;
     

     pos=virtuino.vMemoryRead(3);         // ΒΑΣΗ ΔΑΓΚΑΝΑΣ
     if (pos!=oldPosGripbase) {
      myservo_gripbase.write(pos);  
     
     }
     oldPosGripbase=pos;

      pos=virtuino.vMemoryRead(4);         // ΑΝΟΙΓΜΑ ΚΛΕΙΣΙΜΟ ΔΑΓΚΑΝΑΣ
     if (pos!=oldPosGrip) {
      myservo_grip.write(pos);  
    
     }
     oldPosGrip=pos;

     // ΕΔΩ ΑΚΟΛΟΥΘΕΙ Ο ΕΛΕΓΧΟΣ ΤΗΣ VIRTUAL ΜΕΤΑΒΛΗΤΗΣ 5 ΓΙΑ ΤΟ ΕΑΝ ΠΡΕΠΕΙ ΝΑ ΞΕΚΙΝΗΣΕΙ Η ΕΠΙΔΕΙΞΗ TOY BRAXIONA
     // AYTΗ Η ΕΠΙΔΕΙΞΗ ΚΑΝΕΙ ΤΟΝ ΒΡΑΧΙΟΝΑ ΝΑ ΣΗΚΩΝΕΙ ΔΙΑΦΟΡΑ ΑΝΤΙΚΕΙΜΕΝΑ ΑΠΟ ΠΡΟΚΑΘΟΡΙΣΜΕΝΕΣ ΘΕΣΕΙΣ ΚΑΙ ΝΑ ΤΑ ΜΕΤΑΚΙΝΕΙ.
     boolean demo=boolean(virtuino.vMemoryRead(5));
     if (demo!=false) {StartDemo();}
 }

void StartDemo(){
  //!!ΤΟ DEMO ΜΠΟΡΕΙ ΝΑ ΑΛΛΑΞΕΙ ΜΕΧΡΙ ΤΗΝ ΠΑΡΟΥΣΙΑΣΗ ΤΗΣ ΕΡΓΑΣΙΑΣ!! - ΕΝΔΕΙΚΤΙΚΟΣ ΚΩΔΙΚΑΣ
  //Ανοιξε την δαγκανα
  myservo_grip.write(30,30,true);
  //ΠΙΑΣΕ ΤΟ ΑΝΤΙΚΕΙΜΕΝΟ ΑΠΟ ΤΗΝ ΘΕΣΗ 1
  myservo_base.write(79,50,true);
  myservo_armlow.write(75,5,true);  
  myservo_armhigh.write(99,5,true);
  myservo_gripbase.write(51,30,true);
  myservo_grip.write(0,30,true);
  //Ανυψωση του βραχιονα
  delay(500);
    myservo_armlow.write(72,100,true);  
  myservo_armhigh.write(64,100,true);
  myservo_base.write(59,50,true);
  //Τελος του Demo - Μηδενισμος
  virtuino.vMemoryWrite(5, 0);
  delay(1000);
    //ΒΑΛΕ ΤΟ ΑΝΤΙΚΕΙΜΕΝΟ ΣΤΗΝ ΘΕΣΗ 3
  myservo_base.write(50,50,true);
  myservo_armlow.write(75,5,true);  
  myservo_armhigh.write(99,5,true);
  myservo_gripbase.write(51,30,true);
  myservo_grip.write(30,30,true);
  //Ανυψωση του βραχιονα
  delay(500);
  myservo_armlow.write(72,100,true);  
  myservo_armhigh.write(64,100,true);
  myservo_base.write(59,50,true);
}



