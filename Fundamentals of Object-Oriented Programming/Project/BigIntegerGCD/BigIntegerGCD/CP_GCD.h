#ifndef CP_GCD_H
#define CP_GCD_H
#include "C_Integer.h"

extern long long gcd(long long x, long long y);
extern C_Integer gcd_half(C_Integer x, C_Integer y);     // 更相减损法求最大公约数
extern C_Integer gcd_division(C_Integer x, C_Integer y); // 辗转相除法求最大公约数

#endif // !CP_GCD_H
