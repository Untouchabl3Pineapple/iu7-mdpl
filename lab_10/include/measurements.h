#ifndef __MEASUREMENTS_H__
#define __MEASUREMENTS_H__

#include "matrix.h"

#define REPEATS     1000000

void asmTime(const Matrix* l, const Matrix* r);
void cTime(const Matrix* l, const Matrix* r);

#endif  // __MEASUREMENTS_H__