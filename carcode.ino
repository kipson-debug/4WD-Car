

// Tableau contenant les 4 boutons
// button[0] = AVANT
// button[1] = DROITE
// button[2] = ARRIÈRE
// button[3] = GAUCHE
int button[]={2,3,4,5};
int seuil=512;
int left=A0;
int middle=A1;
int right=A2;
int lecteurs []={left,middle,right};

// Tableau contenant les 4 LED
// led[0] = LED avant gauche
// led[1] = LED avant droite
// led[2] = LED arrière gauche
// led[3] = LED arrière droite
int led[]={10,11,13,12};


// Broches permettant de contrôler le moteur gauche
int leftpositive=8;
int leftnegative=9;


// Broches permettant de contrôler le moteur droit
int rightpositive=7;
int rightnegative=6;


// Tableau contenant les broches des moteurs
int motor[]={6,7,8,9};


// Temps de fonctionnement des moteurs
int delayTime=20;


// Temps utilisé pour les clignotants
int ledDelay=200;


void setup(){

    // Configuration des boutons, moteurs et LED
    for(int i=0;i<4;i++){

        // Les boutons sont des entrées
        pinMode(button[i],INPUT);

        // Les moteurs sont des sorties
        pinMode(motor[i],OUTPUT);

        // Les LED sont des sorties
        pinMode(led[i],OUTPUT);

    }

}


void turnright(){

    // Le moteur gauche tourne vers l'avant
    digitalWrite(leftpositive,HIGH);

    // Le moteur droit tourne vers l'arrière
    digitalWrite(rightnegative,HIGH);
    blinkright();

}

void turnleft(){

    // Le moteur gauche tourne vers l'arrière
    digitalWrite(leftnegative,HIGH);

    // Le moteur droit tourne vers l'avant
    digitalWrite(rightpositive,HIGH);
    blinkleft();

}




void forward(){

    // Le moteur gauche tourne vers l'avant
    digitalWrite(leftpositive,HIGH);

    // Le moteur droit tourne vers l'avant
    digitalWrite(rightpositive,HIGH);
    frontlight();


}


void backward(){

    // Le moteur gauche tourne vers l'arrière
    digitalWrite(leftnegative,HIGH);

    // Le moteur droit tourne vers l'arrière
    digitalWrite(rightnegative,HIGH);
    backlight();

}





void blinkleft(){

    // Parcourt les LED de gauche
    // i = 0 puis i = 3
    for(int i=0;i<4;i+=3){

        // Allume la LED
        digitalWrite(led[i],HIGH);

        // Attend
        delay(ledDelay);

        // Éteint la LED
        digitalWrite(led[i],LOW);

        // Attend avant de continuer
        delay(ledDelay);

    }

}



void blinkright(){

    // Parcourt les LED 1 et 2
    for(int i=1;i<3;i++){

        // Allume la LED
        digitalWrite(led[i],HIGH);

        // Attend
        delay(ledDelay);

        // Éteint la LED
        digitalWrite(led[i],LOW);

        // Attend
        delay(ledDelay);

    }

}




void frontlight(){

    // Allume les deux LED avant
    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],HIGH);

}




void backlight(){

    // Allume les deux LED arrière
    digitalWrite(led[2],HIGH);
    digitalWrite(led[3],HIGH);

}



void lightoff(){

    // Parcourt les 4 LED
    for(int i=0;i<4;i++){

        // Éteint chaque LED
        digitalWrite(led[i],LOW);

    }

}

void allLight() {



    // Parcourt les 4 LED
    for(int i=0;i<4;i++){

        // Éteint chaque LED
        digitalWrite(led[i],HIGH);

    }

}



void stop(){

    // Parcourt les 4 sorties moteur
    for(int i=0;i<4;i++){

        // Coupe tous les moteurs
        digitalWrite(motor[i],LOW);

    }


    // Lorsque la voiture s'arrête,
    // toutes les LED sont éteintes
    lightoff();

}

void followLine(){
// Lecture des valeurs des capteurs
/*
pour n'importe quel capteur sur la ligne noire, plus la ligne devient claire,
plus la valeur lue est grande. Ainsi, 
si le capteur de gauche est sur la ligne noire, il faudra équilibrer en allant vers la gauche
si le capteur du milieu est sur la ligne, on avance tout droit
si le capteur de droite est sur la ligne, il faudra équilibrer vers droite
durant la V2, il faudra que le robot tourne juqu'à ce que le milieu soit sur la ligne
*/
int leftValue=analogRead(left);
int middleValue=analogRead(middle);
int rightvalue=analogRead(right);
if(leftValue>seuil && middleValue>seuil && rightValue>seuil)
 {stop();};
if(leftValue<seuil && middleValue>seuil && rightValue>seuil)
 {turnleft();}
if(leftValue>seuil && middleValue>seuil && rightValue) 
 {turnright();} 
if(leftValue>seuil && middleValue>seuil && rightValue>seuil)
 {forward();}
}

void loop(){

    if(digitalRead(button[0]) == HIGH &&
       digitalRead(button[2]) == HIGH){

        
        stop();

    }

    else if(digitalRead(button[3]) == HIGH &&
            digitalRead(button[1]) == HIGH){

        
        stop();

    }




    
    else if(digitalRead(button[0]) == HIGH){

        // Faire avancer la voiture
        forward();

    }


   
    // Si le bouton DROITE est appuyé
    else if(digitalRead(button[1]) == HIGH){

        // Tourner à droite
        turnright();

    }


    // Si le bouton ARRIÈRE est appuyé
    else if(digitalRead(button[2]) == HIGH){

        // Faire reculer la voiture
        backward();

    }




    // Si le bouton GAUCHE est appuyé
    else if(digitalRead(button[3]) == HIGH){

        // Tourner à gauche
        turnleft();

    }


    
    else{

        
        allLight();          

    }

}