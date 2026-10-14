#include <Arduino.h>

// 1. Définition des modes possibles sous forme de nombres simples
#define MODE_NORMAL 0
#define MODE_SPECIAL 1

class Robot4WD {
  private:
    int modeActuel = MODE_NORMAL; // Le robot commence toujours en mode normal

  public:
    void begin() {
      Serial.println("Robot prêt ! Mode actuel : NORMAL");
    }

    // Fonction pour lire le mode depuis le loop()
    int getMode() {
      return modeActuel;
    }

    // ACTION A : Active le mode spécial
    void verifierDeclenchement(bool conditionSpecifique) {
      if (conditionSpecifique && modeActuel == MODE_NORMAL) {
        modeActuel = MODE_SPECIAL;
        Serial.println(">>> ALERTE : Mode Spécial ACTIVÉ ! <<<");
      }
    }

    // ACTION B : Désactive le mode spécial
    void verifierDesactivation(bool conditionFin) {
      if (conditionFin && modeActuel == MODE_SPECIAL) {
        modeActuel = MODE_NORMAL;
        Serial.println(">>> Fin de l'alerte : Retour au Mode NORMAL <<<");
      }
    }

    // Comportement du robot en mode Normal
    void executerModeNormal() {
      Serial.println("Robot en patrouille (Mode Normal)...");
      // Vos commandes moteurs pour le comportement de base ici
    }

    // Comportement du robot en mode Spécial
    void executerModeSpecial() {
      Serial.println("Robot en fuite / action d'urgence (Mode Spécial) !!!");
      // Vos commandes moteurs pour le comportement spécial ici
    }
};

Robot4WD robot;

void setup() {
  Serial.begin(115200);
  robot.begin();
}

void loop() {
  // --- ÉTAPE 1 : Simulation des actions spécifiques ---
  // Remplacez ces 'false' par vos vrais capteurs (ex: digitalRead(PIN_BOUTON))
  bool actionDeclenchement = false; 
  bool actionDesactivation = false;

  // À des fins de test dans votre moniteur série :
  // Si vous tapez 'A' dans le terminal, on simule l'action spécifique
  // Si vous tapez 'B', on simule l'action de fin
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'A' || c == 'a') actionDeclenchement = true;
    if (c == 'B' || c == 'b') actionDesactivation = true;
  }


  // --- ÉTAPE 2 : Gestion de l'état du robot ---
  // On passe les actions à notre robot pour qu'il décide s'il doit changer de mode
  robot.verifierDeclenchement(actionDeclenchement);
  robot.verifierDesactivation(actionDesactivation);


  // --- ÉTAPE 3 : Exécution du comportement selon le mode verrouillé ---
  if (robot.getMode() == MODE_SPECIAL) {
    robot.executerModeSpecial();
  } else {
    robot.executerModeNormal();
  }

  delay(500); // Petite pause pour la lisibilité du moniteur série
}
