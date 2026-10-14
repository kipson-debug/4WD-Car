#include <IRremote.h>

// Définition des constantes de modes
#define MODE_MANUAL 0
#define MODE_LINE  1
#define MODE_DANCE  2
#define MODE_Wireless 3

class Robot4WD {
  private:

    int button [4] = {2, 3, 4, 5};     // 0:Avancer, 1:Droite, 2:Reculer, 3:Gauche
    int sensors [3] = {A0, A1, A2};   // 0:Gauche, 1:Milieu, 2:Droit

    int leftpositive = 6;
    int leftnegative = 7;
    int rightpositive = 8;
    int rightnegative = 9;
    int motors [4] = {6, 7, 8, 9};

    int limit = 512;
    int currentMode = MODE_MANUAL; // Le robot commence en mode manuel par défaut
    
    int irPin=10;

    unsigned long codesIR []={ };//Tableau pour stocker les codesIR ir connus

    unsigned long smart = 1000; // Durée de la pause intelligente (en ms)

    unsigned long lastIRCode = 0; // Pour stocker le dernier code IR reçu

  public:
    void begin() {
      for (int i = 0; i < 4; i++) {
        pinMode(button[i], INPUT_PULLUP);
        pinMode(motors[i], OUTPUT);
        IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
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
    int getIRCode(){
      if (IrReceiver.decode()) {
        unsigned long codeBrut = IrReceiver.decodedIRData.decodedRawData;
        IrReceiver.resume(); // Libère le récepteur pour le prochain signal
        lastIRCode = codeBrut; // Stocke le dernier code IR reçu
        return codeBrut;
      }
    int   
    int getLastIRCode(){
      return lastIRCode;
    }  
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

    // --- SÉLECTION DES MODES PAR COMBOS ---
    void Combos() {
      bool b0 = (digitalRead(button[0]) == 0);
      bool b1 = (digitalRead(button[1]) == 0);
      bool b2 = (digitalRead(button[2]) == 0);
      bool b3 = (digitalRead(button[3]) == 0);

      // COMBO : Bouton Avancer (0) + Droite (1) = Mode Suiveur de Ligne
      if (b0 && b1) {
        currentMode = MODE_LINE;
        Serial.println("Mode activé : SUIVEUR DE LIGNE");
        stop();
        delay(500); // Anti-rebond pour stabiliser le changement
      }
      // COMBO : Bouton Reculer (2) + Gauche (3) = Mode Manuel
      else if (b2 && b3) {
        currentMode = MODE_MANUAL;
        Serial.println("Mode activé : MANUEL");
        stop();
        delay(500);
      }
      // COMBO : Bouton Droite (1) + Gauche (3) = Mode Danse !
      else if (b1 && b3) {
        currentMode = MODE_DANCE;
        Serial.println("Mode activé : MODE DANSE !");
        stop();
        delay(500);
      }
    }

    // --- DEFINITION DES FONCTIONS DE CHAQUE MODE ---

    // Mode 0 : Pilotage Manuel
    void manualDrive() {
      bool fwd   = (digitalRead(button[0]) == 0);
      bool right = (digitalRead(button[1]) == 0);
      bool bwd   = (digitalRead(button[2]) == 0);
      bool left  = (digitalRead(button[3]) == 0);

      if (fwd && bwd)       { stop(); }
      else if (left && right) { stop(); }
      else if (fwd)         { forward(); }
      else if (right)       { turnright(); }
      else if (bwd)         { backward(); }
      else if (left)        { turnleft(); }
      else                  { stop(); }
    }

    // Mode 1 : Suiveur de Ligne
    void followline() {
      int leftValue = analogRead(capteurs[0]);
      int middleValue = analogRead(capteurs[1]);
      int rightValue = analogRead(capteurs[2]);

      if (leftValue > limit && middleValue > limit && rightValue > limit) { stop(); }
      if (leftValue < limit && middleValue > limit && rightValue > limit) { turnleft(); }
      if (leftValue > limit && middleValue > limit && rightValue < limit) { turnright(); } 
      if (leftValue > limit && middleValue < limit && rightValue > limit) { forward(); }
    }

    // Mode 2 : Mode Danse (Démonstration automatique)
    void letsDance() {
      // Le robot fait une petite chorégraphie cyclique
      turnleft();
      delay(200);
      turnright();
      delay(200);
    }
};

Robot4WD robot;

void setup() {
    robot.begin();
}

void loop() {
    // 1. On écoute en permanence si l'utilisateur fait un combo de touches
    robot.Combos();

    // 2. On aiguille le comportement du robot selon le mode actif
    switch (robot.getMode()) {
        case MODE_MANUAL:
            robot.manualDrive();
            break;
            
        case MODE_LINE:
            robot.followline();
            break;
            
        case MODE_DANCE:
            robot.letsDance();
            break;

        case MODE_Wireless:
            // Ici, vous pouvez ajouter le code pour le mode sans fil si nécessaire
            robot.wireless();
            break;    
            
        default:
            robot.stop();
            break;
    }
}
