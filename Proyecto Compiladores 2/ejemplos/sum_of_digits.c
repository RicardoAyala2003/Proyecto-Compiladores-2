// Test: Sum of digits
int n = 12345;
int suma = input();

while (n > 0) {
    suma = suma + n % 10;
    n = n / 10;
}

print(suma);  // Output: 15