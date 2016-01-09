#include <QuadratureEncoder.h>

void QuadratureEncoder::update(int newState) {

    // direction
    if (bitRead(newState, 0) == 0 && bitRead(this->state, 0) == 1) { // zero transition on first bit

        this->direction = bitRead(newState, 1);
    }

    // speed
    if (direction == FWD) {

        this->clicks++;

    } else {

        this->clicks--;
    }

    this->state = newState;
}
