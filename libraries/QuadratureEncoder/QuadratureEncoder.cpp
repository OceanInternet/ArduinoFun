#include <QuadratureEncoder.h>

void QuadratureEncoder::update(int newState) {
    
    // direction
    
    int newFirstBit  = bitRead(newState,    0);
    int newSecondBit = bitRead(newState,    1);
    int prevFirstBit = bitRead(this->state, 0);
    
    if (newFirstBit == 0 && prevFirstBit == 1) { // zero transition on first bit
        
        this->direction = newSecondBit;
    }
    
    if(direction == FWD) {
        
        this->clicks++;
        
    } else {
        
        this->clicks--;
    }
    
    this->state  = newState;
}