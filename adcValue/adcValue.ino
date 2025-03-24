#define inPinV A0  // Pin input tegangan AC
#define NUM_SAMPLES 10  // Jumlah sampel untuk moving average

int minADC = 1023;
int maxADC = 0;
int avgADC = 0;
int adcSamples[NUM_SAMPLES];  // Buffer penyimpanan
int sampleIndex = 0;  
float sumSamples = 0;  

void setup() {
  Serial.begin(115200);

  // Inisialisasi buffer dengan pembacaan awal
  for (int i = 0; i < NUM_SAMPLES; i++) {
    adcSamples[i] = analogRead(inPinV);
    sumSamples += adcSamples[i];
  }
}

void loop() {
  int adcValue = analogRead(inPinV);

  // Update moving average
  sumSamples -= adcSamples[sampleIndex];  // Kurangi nilai lama
  sumSamples += adcValue;                 // Tambahkan nilai baru
  adcSamples[sampleIndex] = adcValue;     // Simpan nilai baru
  sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;  // Update indeks
  
  int filteredADC = sumSamples / NUM_SAMPLES;  // Hitung rata-rata

  // Update nilai minimum & maksimum
  if (filteredADC < minADC) {
    minADC = filteredADC;
  }
  if (filteredADC > maxADC) {
    maxADC = filteredADC;
  }
  avgADC = (maxADC + minADC) / 2;

  // Tampilkan hasil
  Serial.print("ADC (Filtered): "); Serial.print(filteredADC);
  Serial.print(" | Min: "); Serial.print(minADC);
  Serial.print(" | avgADC: "); Serial.print(avgADC);
  Serial.print(" | Max: "); Serial.println(maxADC);

  delay(10);  // Hindari pembacaan terlalu cepat
}
