void pause(){
      int time=100;
      while(time-millis()<=0){
         stop();
         time=millis();
      }
     }
Est ce que ceci est correct ?

Non, cette fonction contient plusieurs erreurs majeures de logique qui empêcheront votre code de fonctionner. Si vous l'exécutez, la fonction va soit se terminer instantanément en moins d'une microseconde, soit bloquer l'Arduino à l'infini.
Décortiquons pourquoi cela ne fonctionne pas et comment la corriger.

Les 3 problèmes de votre code :

1. Le problème du type de variable (int) :
La variable time est un int. Sur un Arduino Uno, un int est limité à un nombre maximal de 32 767. Comme la fonction millis() augmente de 1000 toutes les secondes, au bout de seulement 32 secondes de fonctionnement, le calcul mathématique va planter (overflow). Il faut obligatoirement utiliser un unsigned long.
2. Le piège de la soustraction inversée :
Dans votre condition : time - millis() <= 0.
Au démarrage de la fonction, time vaut 100. Si votre Arduino tourne depuis 5 secondes, millis() vaut 5000.
Le calcul fait : 100 - 5000 = -4900.
Puisque -4900 est bien inférieur ou égal à 0 (<= 0), la condition est vraie immédiatement. La boucle s'arrête tout de suite sans attendre.
3. La réinitialisation interne (time = millis()) :
À l'intérieur de la boucle, vous changez la valeur de time en lui donnant le temps actuel. Cela écrase votre repère de temps.

La méthode correcte pour créer votre fonction pause()

Pour créer une fonction pause(int duree) qui attend le nombre de millisecondes de votre choix (par exemple pause(2000) pour 2 secondes), vous devez suivre la structure officielle de la montre et des pâtes :
cpp
void pause(unsigned long duree) {
  // 1. On enregistre le moment exact où la pause COMMENCE
  unsigned long tempsDeDepart = millis();
  
  // 2. TANT QUE le temps écoulé est INFÉRIEUR à la durée demandée...
  while (millis() - tempsDeDepart < duree) {
    
    // ... On force le robot à rester immobile
    stop(); 
    
    // ICI : L'Arduino tourne en boucle mais reste "éveillé".
    // Vous pourriez y ajouter la lecture d'un bouton d'urgence !
  }
}
Utilisez le code avec précaution.

Pourquoi cette version fonctionne parfaitement ?

• Elle utilise la bonne soustraction : millis() - tempsDeDepart calcule le temps réel qui s'écoule depuis que vous êtes entré dans la fonction.
• Elle est réutilisable : En mettant duree entre les parenthèses, vous pouvez écrire pause(500); ou pause(3000); dans votre programme selon vos besoins.
Voulez-vous que l'on reprenne l'exercice précédent avec la LED et le bouton pour s'assurer que le fonctionnement de la soustraction millis() - variable est bien clair pour vous ?
