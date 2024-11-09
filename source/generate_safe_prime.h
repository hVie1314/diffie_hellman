#ifndef _GENERATE_SAFE_PRIME_
#define	_GENERATE_SAFE_PRIME_

#include "modular_exponentiation.h"

string generateRandomBigIntegerWithinRange(const string& range);

BigInteger randomBigInteger(const BigInteger& a, const BigInteger& b);

BigInteger generateBigInteger(int bitSize);

bool millerRabinTest(BigInteger d, BigInteger n);

bool isPrime(BigInteger n, int k);

BigInteger generateRandomPrime(int bitSize);

BigInteger generateSafePrime(int bitSize);

#endif // !_GENERATE_SAFE_PRIME_

