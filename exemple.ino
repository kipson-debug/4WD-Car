#include <Arduino.h>

// 1. Définition de la structure de contrôle du robot
class Robot4WD {
  public:
    // Déclarer ici les broches (pins) de vos moteurs si nécessaire
    // const int pinMoteur1 = 12;

    void begin() {
      // Code à exécuter au démarrage (ex: pinMode)
      Serial.println("Robot prêt et initialisé !");
    }

    void forward() {
      Serial.println("Le robot avance...");
      // Ajoutez ici les instructions physiques (digitalWrite) pour vos moteurs
    }

    void backward() {
      Serial.println("Le robot recule...");
    }

    void turnLeft() {
      Serial.println("Le robot tourne à gauche...");
    }

    void turnRight() {
      Serial.println("Le robot tourne à droite...");
    }

    void stop() {
      Serial.println("Le robot s'arrête.");
    }
};

// 2. Création de l'objet "robot" utilisable partout dans le code
Robot4WD robot;

void setup() {
  Serial.begin(115200); // Pour voir les messages s'afficher sur le moniteur série
  
  // Initialisation du robot
  robot.begin();
}

void loop() {
  // Exemple de scénario de test :
  robot.forward();
  delay(2000); // Avance pendant 2 secondes
  
  robot.turnLeft();
  delay(1000); // Tourne pendant 1 seconde
  
  robot.stop();
  delay(5000); // Reste arrêté 5 secondes avant de recommencer
}
