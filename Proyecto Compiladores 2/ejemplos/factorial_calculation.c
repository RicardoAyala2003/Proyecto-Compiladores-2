// Test: Factorial calculation
int n = 5;
int factorial = 1;
int i = 1;

while (i <= n) {
    factorial = factorial * i;
    i = i + 1;
}

print(factorial);  // Output: 120