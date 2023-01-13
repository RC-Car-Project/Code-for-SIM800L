String ip = "23.32.23.23" ;
unsigned int port = 23 ;
String apn= "sl2sfr";
int pincapteur1=1  ;
int pincapteur2=2  ;
int pincapteur3=3  ;
int pincapteur4=4  ;


void setup() 
{ 
  Serial.begin(9600);  //USB
  Serial1.begin(9600); //SIM800L
  InitialisationUDP(ip,port,apn);
  
} 
void loop(){ 
Envoie(4000);

}

void InitialisationUDP(String ip, unsigned int port, String apn){
    ///Initialisation de la connection
  delay(5000);
  Serial1.println("AT+CSTT=\"" + apn + "\"\r");
  Serial.println(Serial1.readString());
  if (Serial1.readString()=="ERROR"){
      InitialisationUDP(ip,port,apn);          Serial.println(Serial1.readString()); 
} 
  else{  
          Serial1.println("AT+CIICR");
          Serial.println(Serial1.readString()); 
          Serial1.println("AT+CIFSR"); 
          Serial.println(Serial1.readString()); 

          if (Serial1.readString()=="ERROR"){    
              InitialisationUDP(ip,port,apn);  Serial.println(Serial1.readString()); } 
          else {          
              Serial1.println("AT+CIPSTART=\"UDP\",\""+ip+"\",\""+port+"\"");
              Serial.println(Serial1.readString()); 
              if (Serial1.readString()=="ERROR")
                {    InitialisationUDP(ip,port,apn);  Serial.println(Serial1.readString()); } 
             else{}
                }

         }

  }

void Envoie(int delais){ //Fonction d'envoie.Delais doit être supérieur à 4000ms.
  Serial1.println("AT+CIPSEND"); //Ouverture de l'entrée des données
  Serial.println(Serial1.readString()); 
  Serial1.println(message(pincapteur1,pincapteur2,pincapteur3,pincapteur4));
  Serial.println(Serial1.readString()); 
  Serial1.println((char)26); //Fin du message
  Serial.println(Serial1.readString()); 
  
  }

String message(int pincapteur1, int pincapteur2,int pincapteur3, int pincapteur4){
  int capteur1= analogRead(pincapteur1);
  int capteur2= analogRead(pincapteur2);
  int capteur3= analogRead(pincapteur3);
  int capteur4= analogRead(pincapteur4);

  return String(capteur1)+",1,"+String(capteur1)+",2,"+String(capteur3)+",3,"+String(capteur4)+",4," ;
  } 
