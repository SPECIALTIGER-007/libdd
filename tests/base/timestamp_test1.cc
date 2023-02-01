//
// Created by tiger on 2/1/23.
//

#include <iostream>

#include "Timestamp.h"

int main() {
    libdd::Timestamp time;
    std::cout << libdd::Timestamp::now().toFormattedString() << std::endl;
    std::cout << libdd::Timestamp::now().toFormattedString(true) << std::endl;
    return 0;
}