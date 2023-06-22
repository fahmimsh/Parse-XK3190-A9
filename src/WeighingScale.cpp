#include "WeighingScale.h"

WeighingScale::WeighingScale(Stream& s, uint32_t baud) {
  _stream = &s;
  _baud = baud;
}

void WeighingScale::begin() {
  static_cast<HardwareSerial*>(_stream)->begin(_baud);
}

float WeighingScale::getWeight(bool enableSerial) {
  if (_stream->available()) {
    char c = _stream->read();
    if (_startCapture)  _data += c;
    if (c == 2 && !_startCapture)  _startCapture = true;
    else if (c == 3 && _startCapture) {
      _startCapture = false;
      _data.remove(_data.length() - 1);
      _weight = process_data(_data);
      _data = "";
      if(enableSerial) Serial.println(_weight);
    }
  }
  return _weight;
}

float WeighingScale::process_data(String data) {
  char WeightData[8] = {0};
  data.toCharArray(WeightData, 8);
  uint8_t DecimalPosition = 7 - (data.charAt(7) - '0');
  char WeightDataComma[9] = {0};
  WeightDataComma[DecimalPosition] = '.';
  uint8_t lengthCopy = (WeightDataComma + DecimalPosition) - WeightDataComma;
  memcpy(WeightDataComma, WeightData, lengthCopy);
  memcpy(WeightDataComma + DecimalPosition + 1, WeightData + lengthCopy, 7 - lengthCopy);
  return strtod(WeightDataComma, NULL);
}
