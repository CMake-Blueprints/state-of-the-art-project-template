#pragma once

#include "MyProject/lib1/lib1.h"

namespace MyProject::lib1 {

class InterfaceImpl {
public:
    int calculateAnswer() {
        return 42;
    }
};

} // namespace MyProject::lib1
