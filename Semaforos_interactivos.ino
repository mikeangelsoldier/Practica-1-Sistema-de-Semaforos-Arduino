
#define pot 0
#define boton 13

#define ledSVerde 6	//Led semaforo coches Verde
#define ledSAmarillo 5	//Led semaforo coches Amarillo
#define ledSRojo 4	//Led semaforo coches Rojo

#define ledPVerde 3	//Led semaforo peatonal Verde
#define ledPRojo 2	//Led semaforo peatonal2 rojo
#define ledPVerde2 7	//Led semaforo peatonal2 Verde
#define ledPRojo2 8	//Led semaforo peatonal2 rojo

#define ledTiempoMinimo 11

int tiempoEspera = 2000;
int tiempoParpadeosRapidos = 400;
int tiempoEsperaPreventivo = 2000;
int tiempoEsperaPeaton = 6000;
int cantidadParpadeos = 4;
int tiempoEsperaMinimo = 0;

boolean botonPresionado=false;
boolean tiempoMinimoExpirado=true;

int valorPot = 0;

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
    verificarValorPotenciometro();
    
    if(botonPresionado){
      cederPasoAPeaton();
    }else{
      encendidoSemaforoCoches();
    }
    verificarPulsacion();
}

void encendidoSemaforoCoches(){
    /******************************Encendido del semaforo de coches*/
  digitalWrite(ledSVerde, HIGH);
  digitalWrite(ledPRojo, HIGH);
  digitalWrite(ledPRojo2, HIGH);
  if(!tiempoMinimoExpirado){
    digitalWrite(ledTiempoMinimo, HIGH);
    delay(tiempoEsperaMinimo);//Tiempo de espera para volver a pulsar el boton
    digitalWrite(ledTiempoMinimo, LOW);
    tiempoMinimoExpirado=true;
  }
}

void verificarPulsacion() {  
  if (digitalRead(boton) == LOW) {
    botonPresionado = true;
    tiempoMinimoExpirado=false;
  }else{
    botonPresionado = false;
  }
}

void cederPasoAPeaton(){
    parpadeoPreventivoVerdeCoches();
    luzPreventiva();
    luzPeatonal();
}

void parpadeoPreventivoVerdeCoches(){
    for (int i = 0; i < cantidadParpadeos; i++) {
      digitalWrite(ledSVerde, HIGH);
      delay(tiempoParpadeosRapidos);
      digitalWrite(ledSVerde, LOW);
      delay(tiempoParpadeosRapidos);
    }
}

void luzPreventiva(){
     digitalWrite(ledSAmarillo, HIGH);
     digitalWrite(ledPRojo, HIGH);
  digitalWrite(ledPRojo2, HIGH);
    delay(tiempoEsperaPreventivo);
    digitalWrite(ledSAmarillo, LOW);
    digitalWrite(ledPRojo, LOW);
    digitalWrite(ledPRojo2, LOW);
}

void luzPeatonal(){
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

