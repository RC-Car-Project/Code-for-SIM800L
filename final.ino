String ip = "23.32.23.23" ; //Définition des l'adresse du serveur socket
unsigned int port = 23 ;  //Définition du port du serveur socket
String apn= "sl2sfr";  //Définition de l'APN (dépend de l'opérateur de la SIM)
int pincapteur1=1  ;  //Définition des capteurs de réception
int pincapteur2=2  ;
int pincapteur3=3  ;
int pincapteur4=4  ;


void setup() 
{ 
  Serial.begin(9600);  //Définition de l'interface Serial connecté à l'ordinateur (debug) USB
  Serial1.begin(9600); //Définition de l'interface Serial1 connecté à la SIM800L
  InitialisationUDP(ip,port,apn);  //Lancement de la fonction d'initialisation de la connexion UDP
  
} 
void loop(){ 
Envoie();//Lancement de la fonction d'envoie UDP

}

void InitialisationUDP(String ip, unsigned int port, String apn){
    ///Initialisation de la connection
  delay(5000);
  Serial1.println("AT+CSTT=\"" + apn + "\"\r");  //Initialisation de la SIM
  Serial.println(Serial1.readString());
  if (Serial1.readString()=="ERROR"){ //Retour d'erreur, on recommence
      InitialisationUDP(ip,port,apn);          Serial.println(Serial1.readString()); 
} 
  else{  
          Serial1.println("AT+CIICR"); //Activation des fonctionnalites sans file
          Serial.println(Serial1.readString()); 
          Serial1.println("AT+CIFSR"); //Obtention de l'adresse IP.
          Serial.println(Serial1.readString()); 

          if (Serial1.readString()=="ERROR"){  //    
              InitialisationUDP(ip,port,apn);  Serial.println(Serial1.readString()); } 
          else {          
              Serial1.println("AT+CIPSTART=\"UDP\",\""+ip+"\",\""+port+"\""); //Initialisation de UDP
              Serial.println(Serial1.readString()); 
              if (Serial1.readString()=="ERROR")
                {    InitialisationUDP(ip,port,apn);  Serial.println(Serial1.readString()); } 
             else{}
                }

         }

  }

void Envoie(){ //Fonction d'envoie.Delais doit être supérieur à 4000ms.
  Serial1.println("AT+CIPSEND"); //Ouverture de l'entrée des données
  Serial.println(Serial1.readString()); 
  Serial1.println(message(pincapteur1,pincapteur2,pincapteur3,pincapteur4)); //Entrée du message
  Serial.println(Serial1.readString()); 
  Serial1.println((char)26); //Fin du message (Ctrl+C)/Envoie
  Serial.println(Serial1.readString()); 
  
  }
// EXEMPLE DE MESSAGE A ENVOYER
String message(int pincapteur1, int pincapteur2,int pincapteur3, int pincapteur4){
  int capteur1= analogRead(pincapteur1);
  int capteur2= analogRead(pincapteur2);
  int capteur3= analogRead(pincapteur3);
  int capteur4= analogRead(pincapteur4);

  return String(capteur1)+",1,"+String(capteur1)+",2,"+String(capteur3)+",3,"+String(capteur4)+",4," ;
  } 
