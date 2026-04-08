#include <Arduino.h>

// PRÁCTICA 8: Display 7 Segmentos - Contador con Función de Error
// Programación de Interfaces y Puertos - UAT

const int SEG[] = {2, 3, 4, 5, 6, 7, 8};
const int DIG[] = {9, 10};

// Tabla de segmentos (Cátodo Común)
const byte TABLA[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b01111001  // [10] Letra 'E' (segmentos a, d, e, f, g encendidos)
};

int contador = 0;
unsigned long ultimoTick = 0;

void mostrarDigito(int num_digito, int valor) {
  digitalWrite(DIG[0], HIGH);
  digitalWrite(DIG[1], HIGH);

  byte segmentos = TABLA[valor];
  for(int s = 0; s < 7; s++) {
    digitalWrite(SEG[s], (segmentos >> s) & 1);
  }

  digitalWrite(DIG[num_digito], LOW);
  delayMicroseconds(2000); 
}

void setup() {
  for(int i = 0; i < 7; i++) pinMode(SEG[i], OUTPUT);
  for(int i = 0; i < 2; i++) {
    pinMode(DIG[i], OUTPUT);
    digitalWrite(DIG[i], HIGH);
  }
  Serial.begin(9600);
}

void loop() {
  // Si el contador es menor a 100, funciona normal
  if (contador < 100) {
    mostrarDigito(0, contador / 10); // Decenas
    mostrarDigito(1, contador % 10); // Unidades
  } 
  // Si el contador es 100 o más, muestra "E" de Error
  else {
    mostrarDigito(0, 10); // Muestra la 'E' en el primer display
    mostrarDigito(1, 10); // Muestra la 'E' en el segundo display
  }

  // Lógica de incremento de tiempo
  if (millis() - ultimoTick >= 1000) {
    ultimoTick = millis();
    contador++;
    
    // Para probar el error, puedes dejar que suba. 
    // Para que sea un contador infinito de 0-99, descomenta la línea de abajo:
    // if (contador > 99) contador = 0;

    Serial.print("Valor actual: ");
    Serial.println(contador);
  }
}