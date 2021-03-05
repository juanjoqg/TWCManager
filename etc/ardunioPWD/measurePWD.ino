// Include Emon Library
#include "EmonLib.h"

// Crear una instancia EnergyMonitor
EnergyMonitor energyMonitor0;
EnergyMonitor energyMonitor1;
EnergyMonitor energyMonitor2;
EnergyMonitor energyMonitor3;
EnergyMonitor energyMonitor4;
EnergyMonitor energyMonitor5;

void setup()
{
  Serial.begin(9600);

  // Calibration factor, it depends on the load resistor connected to the SCT-013
  energyMonitor0.current(0, 20);
  energyMonitor1.current(1, 20);
  energyMonitor2.current(2, 20);
  energyMonitor3.current(3, 20);
  energyMonitor4.current(4, 20);
  energyMonitor5.current(5, 20);
}

void loop()
{
  double IrmsA0 = energyMonitor0.calcIrms(1484);
  double IrmsA1 = energyMonitor1.calcIrms(1484);
  double IrmsA2 = energyMonitor2.calcIrms(1484);
  double IrmsA3 = energyMonitor3.calcIrms(1484);
  double IrmsA4 = energyMonitor4.calcIrms(1484);
  double IrmsA5 = energyMonitor5.calcIrms(1484);


  // Send the information through the serial port
  Serial.print("IrmsA0 = ");
  Serial.print(IrmsA0);
  Serial.print(" EndA0");
  Serial.print("  IrmsA1 = ");
  Serial.print(IrmsA1);
  Serial.print(" EndA1");
  Serial.print("  IrmsA2 = ");
  Serial.print(IrmsA2);
  Serial.print(" EndA2");
  Serial.print("  IrmsA3 = ");
  Serial.print(IrmsA3);
  Serial.print(" EndA3");
  Serial.print("  IrmsA4 = ");
  Serial.print(IrmsA4);
  Serial.print(" EndA4");
  Serial.print("  IrmsA5 = ");
  Serial.print(IrmsA5);
  Serial.println(" EndA5");

}
