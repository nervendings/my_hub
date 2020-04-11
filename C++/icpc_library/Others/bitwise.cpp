#pragma GCC target ("popcnt")
__builtin_parity(n);//@1的个数的奇偶性@
__builtin_popcount(n);//@1个数@
__builtin_ctz(n);//@末尾0个数,n!=0@
__builtin_clz(n);//@前导0的个数,n!=0@
__builtin_ffs(n);//@最后1的位置,从1开始@
__builtin_parity(n)//@x中1的奇偶性@
uint32_t __builtin_bswap32(uint32_t x)//@按字节翻转@
