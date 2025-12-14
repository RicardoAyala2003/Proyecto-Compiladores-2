// Test: Greatest Common Divisor
int a = 48;
int b = 18;

while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
}

print(a);  // Output: 6