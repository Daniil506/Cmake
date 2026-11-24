// Copyright 2024 Marina Usova

#include "lib_stack_on_mass/StackOnMass.h"

#include <stdexcept>

float division(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Input Error: can't divide by zero!");
    }
    return static_cast<float>(a) / b;
}
