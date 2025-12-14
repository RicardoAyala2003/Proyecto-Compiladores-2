// Test: Prime number checker
int n = 17;
int esPrimo = 1;
int i = 2;

if (n <= 1) {
    esPrimo = 0;
} else {
    while (i * i <= n) {
        if (n % i == 0) {
            esPrimo = 0;
        }
        i = i + 1;
    }
}

print(esPrimo);  // Output: 1 (17 is prime)