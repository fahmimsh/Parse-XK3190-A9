#ifndef WEIGHINGSCALE_H
#define WEIGHINGSCALE_H

#include <Arduino.h>
#include <Stream.h>

class WeighingScale {
  public:
    WeighingScale(Stream& s, uint32_t baud);
    void begin();
    float getWeight(bool enableSerial);

  private:
    Stream* _stream;
    uint32_t _baud;
    String _data;
    bool _startCapture;
    float _weight;

    float process_data(String data);
};
#endif
