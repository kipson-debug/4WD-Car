#include <IRremote.h> // Bibliothèque standard obligatoire

// Broche sur laquelle est branché le signal du récepteur IR (ex: broche 11)
const int PIN_RECEPTEUR_IR = 11;

void setup() {
  // Initialisation de la communication avec l'ordinateur
  Serial.begin(9600);
  
  // Initialisation native du récepteur IR
  // ENABLE_LED_FEEDBACK fait clignoter la petite LED intégrée à l'Arduino lors d'une réception
  IrReceiver.begin(PIN_RECEPTEUR_IR, ENABLE_LED_FEEDBACK);
  
  Serial.println("--- Récepteur IR Prêt ---");
  Serial.println("Appuyez sur les touches de votre télécommande pour voir les codesIR...");
}

void loop() {
  // 1. On vérifie de manière non-bloquante si un signal a été capté et décodé
  if (IrReceiver.decode()) {
    
    // 2. On extrait le code brut à 32 bits (unsigned long)
    unsigned long codeBrut = IrReceiver.decodedIRData.decodedRawData;
    
    // 3. On affiche le résultat dans le terminal
    Serial.print("Code détecté (Décimal) : ");
    Serial.print(codeBrut); // Exemple : 4244832000
    
    Serial.print("  |  En Hexadécimal : 0x");
    Serial.println(codeBrut, HEX); // Exemple : FD02FF00
    
    // 4. OBLIGATOIRE : On libère le récepteur pour lui permettre d'écouter le prochain signal
    IrReceiver.resume(); 
  }
}
