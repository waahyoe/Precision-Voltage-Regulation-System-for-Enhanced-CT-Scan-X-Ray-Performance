# Precision Voltage Regulation System for CT Scan & X-Ray

## Project Overview
This project is a **Precision Voltage Regulation System** designed to automatically adjust a transformer's output voltage using a stepper motor. The system ensures stable voltage supply, which is crucial for electromedical devices like **CT scans and X-ray machines**, optimizing imaging performance and protecting equipment from power fluctuations.

## Setup & Usage Instructions
### 1. **Calibrate ADC Value**
- Upload and run **`adcValue.ino`** on your microcontroller.
- Adjust the **trimpot** until the **average ADC value (`avgValue`)** is **512**.
- Ensure the reference input voltage is **5V** for accurate calibration.

### 2. **Test Stepper Motor**
- Run the **stepper motor test code** to verify motor functionality.
- Ensure the stepper motor moves as expected when controlled by the system.

### 3. **Deploy Final Program**
- Once calibration and motor testing are successful, upload and run **`fixprogram.ino`**.
- The system will now automatically adjust the transformer to achieve the target voltage.

## Dependencies
- Arduino-compatible microcontroller
- Stepper motor & driver
- ADC module
- Transformer with adjustable output
- Power supply (5V reference voltage)

## Notes
- Ensure stable power input for accurate voltage regulation.
- If adjustments are needed, repeat the **ADC calibration** step before running the final program.
