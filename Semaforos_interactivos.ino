
#define boton 13

#define ledSVerde 6	//Led semaforo coches Verde
#define ledSAmarillo 5	//Led semaforo coches Amarillo
#define ledSRojo 4	//Led semaforo coches Rojo

#define ledPVerde 3	//Led semaforo peatonal Verde
#define ledPRojo 2	//Led semaforo peatonal2 rojo
#define ledPVerde2 7	//Led semaforo peatonal2 Verde
#define ledPRojo2 8	//Led semaforo peatonal2 rojo


int tiempoEspera = 2000;
int tiempoParpadeosRapidos = 400;
int tiempoEsperaPreventivo = 2000;
int tiempoEsperaPeaton = 6000;
int cantidadParpadeos = 4;
int tiempoEsperaMinimo = 0;

boolean botonPresionado=false;

void setup() {
  pinMode(ledSVerde, OUTPUT);
  pinMode(ledSAmarillo, OUTPUT);
  pinMode(ledSRojo, OUTPUT);
  pinMode(ledPVerde, OUTPUT);
  pinMode(ledPRojo, OUTPUT);
  pinMode(ledPVerde2, OUTPUT);
  pinMode(ledPRojo2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
    verificarPulsacion();
    if(botonPresionado){
      cederPasoAPeaton();
    }else{
      encendidoSemaforoCoches();
    }
}

void encendidoSemaforoCoches(){
    /******************************Encendido inicial del semaforo de coches y peatonal*/
  digitalWrite(ledSVerde, HIGH);
  digitalWrite(ledPRojo, HIGH);
  digitalWrite(ledPRojo2, HIGH);

}

void verificarPulsacion() {
  if (digitalRead(boton) == LOW) {
    botonPresionado = true;
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









