// Test: Short-circuit AND (should not divide by zero)
int x = 0;
int y = 10;
if (x != 0 && y / x > 5)
    print(1);
else
    print(0);
// Output: 0 (no division by zero error)