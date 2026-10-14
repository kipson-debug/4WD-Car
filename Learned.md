Oui, c'est totalement natif ! C'est l'une des fonctionnalités de base les plus puissantes du langage C++ et de l'univers Arduino. On appelle cela le passage de paramètres (ou d'arguments) dans une fonction.
Voici votre cours dédié, structuré pour comprendre ce super-pouvoir du code.

Cours : Les Fonctions à Paramètres ou l'Art de rendre le Code Intelligent

Jusqu'à présent, vous écriviez des fonctions "fixes" comme robot.forward();. Elles font toujours exactement la même chose. Avec les paramètres, vous allez pouvoir donner des ordres précis et variables à votre robot.

1. Qu'est-ce qu'un paramètre natif ?

Un paramètre, c'est une variable locale temporaire que l'on glisse entre les parenthèses de la fonction lors de sa création. Elle sert de "moule" ou de "boîte vide" qui attend de recevoir une valeur.

La syntaxe de création :

cpp
void nomDeLaFonction(typeDuParametre nomDeLaVariable) {
    // Le code qui utilise cette variable
}
Utilisez le code avec précaution.

2. Exemple 1 : La fonction pause(duree) décortiquée

Regardons comment l'Arduino traite ce code nativement :
cpp
void pause(unsigned long duree) {
  unsigned long tempsDeDepart = millis();
  
  // L'Arduino remplace "duree" par le nombre que vous lui avez envoyé
  while (millis() - tempsDeDepart < duree) {
    stop(); 
  }
}
Utilisez le code avec précaution.
Quand vous écrivez pause(1500); dans votre programme :
1. L'Arduino crée instantanément une variable temporaire appelée duree.
2. Il met le nombre 1500 à l'intérieur.
3. Il exécute la boucle while en remplaçant mathématiquement le mot duree par 1500.
4. Une fois la fonction terminée, la variable duree est détruite pour libérer la mémoire de la carte.

3. Exemple 2 : Donner de la puissance à votre robot

Vous pouvez mettre plusieurs paramètres dans une même fonction en les séparant par une virgule. C'est idéal pour contrôler la vitesse des moteurs de votre robot !
Imaginez cette fonction intégrée à votre robot :
cpp
// Cette fonction attend DEUX informations : la vitesse (0 à 255) et le temps
void avancerAjuste(int vitesse, unsigned long temps) {
  
  // On applique la vitesse choisie sur les pins des moteurs
  analogWrite(leftpositive, vitesse);
  analogWrite(rightpositive, vitesse);
  
  // On maintient cette action pendant le temps choisi
  unsigned long depart = millis();
  while (millis() - depart < temps) {
    // Le robot avance à la vitesse demandée
  }
  
  stop(); // On arrête après la durée écoulée
}
Utilisez le code avec précaution.

Comment vous l'utilisez dans votre loop() :

• Pour avancer très vite pendant 1 seconde :
avancerAjuste(255, 1000);
• Pour avancer doucement (mode patrouille) pendant 5 secondes :
avancerAjuste(100, 5000);

4. Pourquoi c'est une révolution pour votre code ?

1. Gain de place énorme : Sans cela, vous auriez dû écrire une fonction pause1Seconde(), une fonction pause2Secondes(), une fonction avancerVite(), avancerDoucement(), etc. Votre code aurait fait des centaines de lignes pour rien.
2. Lisibilité : Votre loop() ressemble à du français ou de l'anglais. Vous lisez exactement ce que fait le robot et pendant combien de temps.
Maintenant que vous avez ce super-pouvoir en main, que préférez-vous faire ?
• Option A : On écrit le code complet pour intégrer ces fonctions de mouvements intelligents avec paramètres (pause et vitesse) directement à l'intérieur de votre classe Robot4WD ?
• Option B : On retourne résoudre l'exercice à trous de la LED et de millis() pour valider cette logique de temps ?
