#include "sin_cmp.h"
#include "32bit.h"
#include "64bit.h"
#include "80bit.h"

int main(void) {
    print32BitResults();
    print64BitResults();
    print80BitResults();

    sinPiCmp();
    sinPiDel2Cmp();

    return 0;
}
