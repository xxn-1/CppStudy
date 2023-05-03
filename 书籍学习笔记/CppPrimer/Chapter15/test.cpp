#include "BaseOver.h"
using namespace std;
int main() {
    BaseOver t;
    Base* base1 = t.clone();
    
    base1->show();
}