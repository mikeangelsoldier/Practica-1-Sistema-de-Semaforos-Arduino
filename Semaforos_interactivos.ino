/*

Autor: Miguel Ángel Ramírez Lira
Descripción del programa:
        Realizar un sistema que simule un Semáforo Interactivo usando Arduino. Este debe mostrar un conjunto de semáforos que cambiarán de verde a ámbar a rojo, 
        y viceversa, luego de un período de tiempo establecido, utilizando el sistema de cuatro estados de los semáforos en México. Este se extiende para incluir 
        un conjunto de luces y un botón peatonal para solicitar cruzar la calle.
        Cuando llega el peatón y se dispone a cruzar pulsa el botón que encuentra en la parte baja del semáforo, este reconoce la orden y cierra el paso de los 
        vehículos para que el viandante pueda cruzar con seguridad hasta el otro lado de la calle. Una vez que se acaba el tiempo estipulado para que el peatón cruce, 
        ese semáforo permanecerá abierto para mejorar la movilidad de los vehículos. 
        El sistema deberá de contener una perilla para controlar el tiempo mínimo en que el semáforo vehicular va a durar en verde.

*/

/***************************************Variables y constantes*/
#define pot 0
#define boton 13

#define ledSVerde 6	    //Led semaforo coches Verde
#define ledSAmarillo 5	//Led semaforo coches Amarillo
#define ledSRojo 4	    //Led semaforo coches Rojo

#define ledPVerde 3	    //Led semaforo peatonal Verde
#define ledPRojo 2	    //Led semaforo peatonal rojo
#define ledPVerde2 7	  //Led semaforo peatonal2 Verde
#define ledPRojo2 8	    //Led semaforo peatonal2 rojo
#define ledTiempoMinimo 11  //LED Que se enciende y se apaga hasta que se termina el tiempo minimo de espera

int tiempoEspera = 2000;            //tiempo en que permanecen encendidos los leds
int tiempoParpadeosRapidos = 400;   //tiempo rapido para parpadeos antes de que se encienda otro LED
int tiempoEsperaPreventivo = 2000;  //tiempo en que permanecen encendidos el LED ámbar
int tiempoEsperaPeaton = 6000;      //tiempo en que permanecen encendido el LED despues de presionar el bóton peatonal
int cantidadParpadeos = 4;          //cantidad de parpadeos antes de que cambie de color
int valorPot = 0;                   //La variable usada para guardar el valor obtenido de la resistencia del potenciometro
int tiempoEsperaMinimo = 0;         //La variable usada para guardar el equivalente del valor guardado en valorPot

boolean botonPresionado = false;    //variable para indicar cuando se a presionado o no el boton peatonal
boolean tiempoMinimoExpirado = true;//variable para indicar cuando se haya acabado el tiempo de espera minimo para volver a presionar el botón



void setup() {
  pinMode(ledSVerde, OUTPUT);
  pinMode(ledSAmarillo, OUTPUT);
  pinMode(ledSRojo, OUTPUT);
  pinMode(ledPVerde, OUTPUT);
  pinMode(ledPRojo, OUTPUT);
  pinMode(ledPVerde2, OUTPUT);
  pinMode(ledPRojo2, OUTPUT);
  pinMode(ledTiempoMinimo, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  verificarValorPotenciometro();  //metodo que guarda valores obtenidos del potenciometro

  if (botonPresionado) {      //validacion para saber si se presiono o no el botón
    cederPasoAPeaton();
  } else {
    encendidoSemaforoCoches();
  }
  verificarPulsacion();
}

void encendidoSemaforoCoches() {
  /*-----------------------------Encendido del semaforo de coches*/
  digitalWrite(ledSVerde, HIGH);
  digitalWrite(ledPRojo, HIGH);
  digitalWrite(ledPRojo2, HIGH);
  
  if (!tiempoMinimoExpirado) {
    digitalWrite(ledTiempoMinimo, HIGH);
    delay(tiempoEsperaMinimo);          //Tiempo de espera para volver a pulsar el boton
    digitalWrite(ledTiempoMinimo, LOW);
    tiempoMinimoExpirado = true;
  }
}

void verificarPulsacion() {
  if (digitalRead(boton) == LOW) {
    botonPresionado = true;
    tiempoMinimoExpirado = false;
  } else {
    botonPresionado = false;
  }
}


void cederPasoAPeaton() {
  parpadeoPreventivoVerdeCoches();
  luzPreventiva();      //metodo encargado de encender el LED ámbar
  luzPeatonal();
}


void parpadeoPreventivoVerdeCoches() {
  for (int i = 0; i < cantidadParpadeos; i++) {
    digitalWrite(ledSVerde, HIGH);
    delay(tiempoParpadeosRapidos);
    digitalWrite(ledSVerde, LOW);
    delay(tiempoParpadeosRapidos);
  }
}


void luzPreventiva() {
  digitalWrite(ledSAmarillo, HIGH);
  digitalWrite(ledPRojo, HIGH);
  digitalWrite(ledPRojo2, HIGH);
  delay(tiempoEsperaPreventivo);
  digitalWrite(ledSAmarillo, LOW);
  digitalWrite(ledPRojo, LOW);
  digitalWrite(ledPRojo2, LOW);
}


void luzPeatonal() {
  digitalWrite(ledSRojo, HIGH);
  digitalWrite(ledPVerde, HIGH);
  digitalWrite(ledPVerde2, HIGH);
  delay(tiempoEsperaPeaton);

  for (int i = 0; i < 3; i++) {
    digitalWrite(ledSRojo, HIGH);
    digitalWrite(ledPVerde2, HIGH);
    digitalWrite(ledPVerde, HIGH);
    delay(tiempoParpadeosRapidos);
    digitalWrite(ledSRojo, LOW);
    digitalWrite(ledPVerde2, LOW);
    digitalWrite(ledPVerde, LOW);
    delay(tiempoParpadeosRapidos);
  }
  luzPreventiva();
}


void verificarValorPotenciometro() {
  valorPot = analogRead(pot);
  delay(100);
  Serial.print("valor del potenciometro=     ");
  Serial.println(valorPot);
  tiempoEsperaMinimo = map(valorPot, 0, 1020, 500, 30000);
  Serial.print("tiempo de espera=              ");
  Serial.println(tiempoEsperaMinimo);
}

