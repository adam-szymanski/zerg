#include "lib/tensor/Tensor.h"

#include<iostream>
using namespace std;
using namespace Zerg;

int main() {
    Tensor t({4});
    t.val(0) = 0;
    t.val(1) = 1;
    t.val(2) = 2;
    t.val(3) = 3;
    cout << "t=" << t;
    
    return 0;
}