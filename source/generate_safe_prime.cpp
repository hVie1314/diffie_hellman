#include <string>
#include <random>
#include <chrono>
#include "modular_exponentiation.cpp"

using namespace std;

string generateRandomBigIntegerWithinRange(const string& range) 
{
	string result = "";
	random_device rd;
	mt19937 gen(rd());

	// Loops through each digit in the range
	for (char digit : range) 
    {
        // Generate a random number from 0 to the current digit
		uniform_int_distribution<int> dist(0, digit - '0'); 
		result.push_back('0' + dist(gen));
	}

	// Remove leading zeros
	result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));

	return result.empty() ? "0" : result;
}

BigInteger randomBigInteger(const BigInteger& a, const BigInteger& b) 
{
	if (a >= b) throw invalid_argument("Invalid range: a must be less than b.");

    // Calculate the range of the random number
	BigInteger range = b - a; 

	string randInRangeStr = generateRandomBigIntegerWithinRange(range.getValue());
	BigInteger randInRange(randInRangeStr);

	return a + randInRange; 
}

BigInteger generateBigInteger(int bitSize) 
{
    // Calculate the number of digits needed to represent the random number
    // Each digit can represent approximately: log2(10) ≈ 3.32 bits
    int numDigits = ceil(bitSize / 3.32); 
    string result = "";
    
    // Use current time for a better seed 
    auto now = chrono::steady_clock::now();
    unsigned seed = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    
    // Seed the random number generator
    mt19937 gen(seed);  
    uniform_int_distribution<int> dist(0, 9);

    // Generate the first digit from 1 to 9
    result.push_back('1' + dist(gen) % 9);

    // Generate the rest of the digits from 0 to 9
    for (int i = 1; i < numDigits; ++i) {
        result.push_back('0' + dist(gen));
    }

    return BigInteger(result);
}

bool millerRabinTest(BigInteger d, BigInteger n)
{
    // Pick a random number in [2..n-2]
    // Sure that n > 4
    BigInteger a = randomBigInteger(BigInteger("2"), n - BigInteger("2"));

    // x = a^d % n
    BigInteger x = modular_exponentiation(a, d, n);

    if (x == BigInteger("1") || x == n - BigInteger("1"))
        return true;

    // Keep squaring x until:
    // d does not reach n-1 or
    // (x^2) % n is not 1 or
    // (x^2) % n is not n-1
    while (d != n - BigInteger("1"))
    {
        x = (x * x) % n;
        d = d * BigInteger("2");

        if (x == BigInteger("1"))
            return false;
        if (x == n - BigInteger("1"))
            return true;
    }

    return false;
}

bool isPrime(BigInteger n, int k = 5)
{
    if (n <= BigInteger("1") || n == BigInteger("4"))
        return false;
    if (n <= BigInteger("3")) // 2 and 3 
        return true;

    // n = d * 2^r + 1, r >= 1
    BigInteger d = n - BigInteger("1");
    while (d % BigInteger("2") == BigInteger("0"))
        d = d / 2;

    // Check Miller-Rabin test k times
    for (int i = 0; i < k; ++i)
    {
        if (!millerRabinTest(d, n))
            return false;
    }

    // Pass Miller-Rabin test
    // Comsider n is a prime number
    return true;
}

BigInteger generateRandomPrime(int bitSize) 
{
	BigInteger candidate = generateBigInteger(bitSize);
	while (!isPrime(candidate)) {
		candidate = generateBigInteger(bitSize);
	}
	return candidate;
}

BigInteger generateSafePrime(int bitSize) {
	while (true) {
		BigInteger p = generateRandomPrime(bitSize - 1); 

        // safe prime = 2p + 1, p is a prime number
		BigInteger safePrimeCandidate = p * BigInteger("2") + BigInteger("1"); 
		if (!isPrime(safePrimeCandidate)) {
			return safePrimeCandidate;
		}
	}
}


int main() {

    BigInteger safePrime = generateSafePrime(512);
    cout << "Safe prime: " << safePrime << endl;

    return 0;
}
