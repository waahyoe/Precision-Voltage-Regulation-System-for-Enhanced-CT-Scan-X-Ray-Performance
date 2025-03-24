/////https://www.youtube.com/watch?v=3zt60r7qpf4&t=531s&ab_channel=MAICONTROLLER
//sensor voltage zmpt101B, driver motor BTS7960, stepper motor, trimpot 96,8
#include "EmonLib.h"
#include <Stepper.h>

#define NUM_SAMPLES 10
#define inPinV A0

EnergyMonitor emon1;
int voltage_tujuan = 220;     // Target tegangan
float tolerance = 2.0;        // Toleransi ± nilai target
// Faktor kalibrasi default
float vCalibration = 457;  

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int stepCount = 0;

void setup() {
  Serial.begin(115200);
  stepCount = 0;
  myStepper.setSpeed(50);
  
  // Inisialisasi sensor ZMPT101B dengan faktor awal
  emon1.voltage(inPinV, vCalibration, 1.7);
}

void loop() {
  double sumVoltage = 0.0;
  
  // Baca tegangan menggunakan EmonLib sebanyak NUM_SAMPLES kali untuk mendapatkan rata-rata
  for (int i = 0; i < NUM_SAMPLES; i++) {
    emon1.calcVI(20, 2000);
    sumVoltage += emon1.Vrms;
  }
  double avgVoltage = sumVoltage / NUM_SAMPLES;
  
  // Update faktor kalibrasi berdasarkan nilai avgVoltage
  if (avgVoltage <= 50) {
      vCalibration = 380;  // Misalnya, untuk kondisi 25V
  } else if (avgVoltage <= 100) {
      vCalibration = 447;  // Misalnya, untuk kondisi 75V
  } else if (avgVoltage <= 150) {
      vCalibration = 457;  // Misalnya, untuk kondisi 125V
  } else if (avgVoltage <= 200) {
      vCalibration = 457;  // Misalnya, untuk kondisi 175V
  } else if (avgVoltage <= 250) {
      vCalibration = 457;  // Misalnya, untuk kondisi 225V
  } else {
      vCalibration = 457;  // Default jika tidak masuk kategori di atas
  }
  
  // Terapkan faktor kalibrasi yang telah diupdate ke sensor
  emon1.voltage(inPinV, vCalibration, 1.7);
  
  // Cetak data untuk monitoring
  Serial.print("avgVoltage: ");
  Serial.print(avgVoltage, 2);
  Serial.print(" V | Calibration Factor: ");
  Serial.println(vCalibration);
  
  // Kontrol motor berdasarkan avgVoltage
  if (avgVoltage < voltage_tujuan - tolerance) {
      myStepper.step(-10);
      Serial.print("clockwise steps:");
      Serial.println(stepCount);
      stepCount -=10;
  }
  else if (avgVoltage > voltage_tujuan + tolerance) {
      myStepper.step(10);
      Serial.print("counter clockwise steps:");
      Serial.println(stepCount);
      stepCount +=10;
  }
  else {
      Serial.print("steps:");
      Serial.println(stepCount);
      Serial.println("Motor berhenti, nilai sesuai target");
  }
  delay(10);
}
