// Test: Sum of first N natural numbers
int n = 10;
int suma = 0;
int i = 1;

while (i <= n) {
    suma = suma + i;
    i = i + 1;
}

print(suma);  // Output: 55