// Include Emon Library
#include "EmonLib.h"

// Crear una instancia EnergyMonitor
EnergyMonitor energyMonitor;

// Voltaje de nuestra red eléctrica
float voltajeRed = 230.0;

void setup()
{
  Serial.begin(9600);

  // Iniciamos la clase indicando
  // Número de pin: donde tenemos conectado el SCT-013
  // Valor de calibración: valor obtenido de la calibración teórica
  // Inicial calibrado 13.23
  energyMonitor.current(0, 20);
}

void loop()
{
  // Obtenemos el valor de la corriente eficaz
  // Pasamos el número de muestras que queremos tomar
  double Irms = energyMonitor.calcIrms(4000);

  // Calculamos la potencia aparente
  double potencia =  Irms * voltajeRed;

  // Mostramos la información por el monitor serie
  Serial.print("Potencia = ");
  Serial.print(potencia);
  Serial.print("    Irms = ");
  Serial.println(Irms);
}

