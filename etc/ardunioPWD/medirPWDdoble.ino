// Include Emon Library
#include "EmonLib.h"

// Crear una instancia EnergyMonitor
EnergyMonitor energyMonitor;
EnergyMonitor energyMonitor2;

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
  energyMonitor2.current(1, 20);
}

void loop()
{
  // Obtenemos el valor de la corriente eficaz
  // Pasamos el número de muestras que queremos tomar
  double Irms = energyMonitor.calcIrms(1484);
  double Irms2 = energyMonitor2.calcIrms(1484);

  // Calculamos la potencia aparente
  double potencia =  Irms * voltajeRed;
  double potencia2 =  Irms2 * voltajeRed;

  // Mostramos la información por el monitor serie
  Serial.print("Potencia = ");
  Serial.print(potencia);
  Serial.print("    Irms = ");
  Serial.print(Irms);
    // Mostramos la información por el monitor serie
  Serial.print("Potencia2 = ");
  Serial.print(potencia2);
  Serial.print("    Irms2 = ");
  Serial.println(Irms2);
}
