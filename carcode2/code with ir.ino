#include <IRRemote.h>

//Définition des constantes de modes
#define MODE_MANUAL 0
#define MODE_LINE  1
#define MODE_DANCE  2


class Robot4WD {
    private :

    //Définition des broches des moteurs
    int leftpositive = 6;
    int leftnegative = 7;
    int rightpositive = 8;
    int rightnegative = 9;
    int motors [4] = {6, 7, 8, 9};

    //Définition des broches des sensors
    int sensors [3] = {A0, A1, A2};   // 0:Gauche, 1:Milieu, 2:Droit

    int currentMode=MODE_MANUAL; //Le robot commence en mode manuel par défaut
    int limit=512; //Seuil de détection pour les capteurs de ligne
    unsigned long smart=1000; //Durée de la pause intelligente (en ms)
    public:
    void begin() {
      for (int i = 0; i < 4; i++) {
        pinMode(button[i], INPUT_PULLUP);
        pinMode(motors[i], OUTPUT);
      }
      Serial.begin(9600);
      stop();
      Serial.println("_ _ _Laboratoire initialisé  _ _ _");
      Serial.println("Récepteur initialisé")
      Serial.println("-----------------Tutoriel à suivre----------------")
    }
    void smartBreak(unsigned long duration){
      unsigned long startTime = millis();
      while(millis()-startTime < duration){
        stop();
      }
    }
    // Le fameux "Getter" pour que le loop() puisse connaître le mode
    int getMode() {
      return currentMode;
    }
    
      }
  
    void stop() {
      for (int i = 0; i < 4; i++) {
        digitalWrite(motors[i], 0);
      }
    }

    void forward(){
       stop();
      digitalWrite(leftpositive, 1);  
      digitalWrite(rightpositive, 1);
      smartBreak(smart);
       }

    void backward(){ 
      stop(); 
      digitalWrite(leftnegative, 1);  
      digitalWrite(rightnegative, 1);
      smartBreak(smart); 
      }

    void turnleft(){ 
      stop(); 
      digitalWrite(leftnegative, 1);  
      digitalWrite(rightpositive, 1);
      smartBreak(smart); 
      }
      
    void turnright(){ 
      stop(); 
      digitalWrite(leftpositive, 1);  
      digitalWrite(rightnegative, 1);
      smartBreak(smart);
      }
}

class IRReceiver {
  private:
    int irPin; // Broche sur laquelle est branché le signal du récepteur IR
    unsigned long lastIRCode; // Pour stocker le dernier code IR reçu

  public:
    IRReceiver(int pin) : irPin(pin), lastIRCode(0) {}

    void begin() {
      IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
      Serial.println("Récepteur IR initialisé");
    }
    
    unsigned long getIRCode() {
      if (IrReceiver.decode()) {
        unsigned long codeBrut = IrReceiver.decodedIRData.decodedRawData;
        IrReceiver.resume(); // Libère le récepteur pour le prochain signal
        lastIRCode = codeBrut; // Stocke le dernier code IR reçu
        return codeBrut;
      }
      return 0; // Aucun code IR reçu
    }

    unsigned long getLastIRCode(){
        return lastIRCode;
    }
};
Robot4WD robot;
IRReceiver irReceiver(11);