


#define ledSVerde 6	//Led semaforo coches Verde
#define ledSAmarillo 5	//Led semaforo coches Amarillo
#define ledSRojo 4	//Led semaforo coches Rojo

#define ledPVerde 3	//Led semaforo peatonal Verde
#define ledPRojo 2	//Led semaforo peatonal2 rojo
#define ledPVerde2 7	//Led semaforo peatonal2 Verde
#define ledPRojo2 8	//Led semaforo peatonal2 rojo


int tiempoEspera = 2000;
int tiempoEsperaRapido = 400;
int tiempoEsperaPreventivo = 2000;
int tiempoEsperaPeaton = 6000;
int cantidadParpadeos = 3;
int tiempoEsperaSemaforoVehicular = 0;
void setup() {
  pinMode(boton1, INPUT_PULLUP);

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
  


}


