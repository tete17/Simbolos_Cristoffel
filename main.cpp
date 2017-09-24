#include <iostream>
#include "FTensor.hpp"
#include "Symbolics/symbolicc++.h"

using namespace std;

int main() {

    Symbolic zero;
    Symbolic one(1);
    
    Symbolic x("x"), y("y"), z("z"), t("t");
    Symbolic g=((-one, zero, 20, zero),
                (zero, one, 20, zero),
                (zero, zero, one, zero),
                (zero, zero, zero, one));
    g = g[ t, x, y, z];

    cout << g.inverse() << endl;
    

    return zero;
}