#ifndef QuadratureEncoder_h
#define QuadratureEncoder_h

#include <Arduino.h>

#ifndef PULSES_PER_REV
#define PULSES_PER_REV 12
#endif

#ifndef GEAR_RATIO
#define GEAR_RATIO     50
#endif

#ifndef FWD
#define FWD 0
#endif

#ifndef REV
#define REV 1
#endif

class QuadratureEncoder
{
protected:
    int            state     = 0;
    unsigned long  millis    = 0;
    int            clicks    = 0;
    bool           direction = 0;
    
public:
    QuadratureEncoder();
    void update(int newState);
};

#endif