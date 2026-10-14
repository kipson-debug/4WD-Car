#include <IRRemote.h>

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

IRReceiver irReceiver(11); // Crée une instance de IRReceiver sur la broche 11

void setup() {
  Serial.begin(9600);
  irReceiver.begin();
}
void loop() {
  unsigned long code = irReceiver.getIRCode();
  if (code != 0) {
    Serial.print("Code IR reçu : ");
    Serial.println(code);
  }
}