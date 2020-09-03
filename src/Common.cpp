#include "../include/Common.h"

using namespace std;

void printVal(Value v) {
  switch(v.v) {
    case V_INT:
    cout << v.ival << endl;
    break;
    case V_STRING:
    cout << v.cval << endl;
    break;
  }
}