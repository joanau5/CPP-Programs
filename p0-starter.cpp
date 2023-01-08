#include <iostream>
using std::cout;
using std::endl;

typedef char BLAH;

#define XYZ 1 << 1 << 1 << 1 << 1

BLAH blah[XYZ]{0x54,
               104,
               0x65,
               1 << ((1 << (1 << 1)) | 1),
               97,
               110,
               0x73,
               119,
               0x65,

               0x72,
               1 << ((1 << (1 << 1)) | 1),

               105,
               0x73,

               1 << ((1 << (1 << 1)) | 1),
               50};

int main() {
  cout << blah << endl;

  return 0;
}