#include "PMS5003.h"
void PMS5003::processDataOn(HardwareSerial &serial) {
  unsigned long timeout = millis();
  int count = 0;
  byte incomeByte[NUM_INCOME_BYTE];
  boolean startcount = false;
  byte data;
  while (1){
    if ((millis() - timeout) > 3000){
      //ptrSerial.println("SENSOR-ERROR-TIMEOUT");
      break;
    }
    if (serial.available()){
      data = serial.read();
      if (data == CHAR_PRELIM && !startcount) {
        startcount = true;
        count++;
        incomeByte[0] = data;
      }
      else if (startcount) {
        count++;
        incomeByte[count - 1] = data;
        if (count >= NUM_INCOME_BYTE){
          break;
        }
      }
    }
  }
  unsigned int calcsum = 0;
  unsigned int exptsum;
  for (int i = 0; i < NUM_DATA_BYTE; i++) {
    calcsum += (unsigned int)incomeByte[i];
  }
  exptsum = ((unsigned int)incomeByte[CHECK_BYTE] << 8) + (unsigned int)incomeByte[CHECK_BYTE + 1];
  if (calcsum == exptsum) {
    pm1 = ((unsigned int)incomeByte[PM1_BYTE] << 8) + (unsigned int)incomeByte[PM1_BYTE + 1];
    pm25 = ((unsigned int)incomeByte[PM25_BYTE] << 8) + (unsigned int)incomeByte[PM25_BYTE + 1];
    pm10 = ((unsigned int)incomeByte[PM10_BYTE] << 8) + (unsigned int)incomeByte[PM10_BYTE + 1];
  } else {
    //ptrSerial.println("#[exception] PM2.5 Sensor CHECKSUM ERROR!");
    pm1 = -1;
    pm25 = -1;
    pm10 = -1;
  }
  return;
}

int PMS5003::getPM1() {
  return pm1;
}

int PMS5003::getPM25() {
  return pm25;
}
int PMS5003::getPM10() {
  return pm10;
}
// void PMS5003::processData(int *PM1 = 0, int *PM25 = 0, int *PM10 = 0) {

//   unsigned long timeout = millis();
//   int count = 0;
//   byte incomeByte[NUM_INCOME_BYTE];
//   boolean startcount = false;
//   byte data;
//   while (1)
//   {
//   	if ((millis() - timeout) > 3000)
//     {
//       Serial.println("[SENSOR-ERROR-TIMEOUT]");
//       break;
//     }
//     if (Serial1.available())
//     {
//       data = Serial1.read();
//       if (data == CHAR_PRELIM && !startcount)
//       {
//         startcount = true;
//         count++;
//         incomeByte[0] = data;
//       }
//       else if (startcount)
//       {
//         count++;
//         incomeByte[count - 1] = data;
//         if (count >= NUM_INCOME_BYTE)
//         {
//           break;
//         }
//       }
//     }
//   }
//   unsigned int calcsum = 0; // BM
//   unsigned int exptsum;
//   for (int i = 0; i < NUM_DATA_BYTE; i++) {
//     calcsum += (unsigned int)incomeByte[i];
//   }

//   exptsum = ((unsigned int)incomeByte[CHECK_BYTE] << 8) + (unsigned int)incomeByte[CHECK_BYTE + 1];
//   if (calcsum == exptsum) {
//     *PM1 = ((unsigned int)incomeByte[PM1_BYTE] << 8) + (unsigned int)incomeByte[PM1_BYTE + 1];
//     *PM25 = ((unsigned int)incomeByte[PM25_BYTE] << 8) + (unsigned int)incomeByte[PM25_BYTE + 1];
//     *PM10 = ((unsigned int)incomeByte[PM10_BYTE] << 8) + (unsigned int)incomeByte[PM10_BYTE + 1];
//   } else {
//     Serial.println("#[exception] PM2.5 Sensor CHECKSUM ERROR!");
//     *PM1 = -1;
//     *PM25 = -1;
//     *PM10 = -1;
//   }
//   return;
// }