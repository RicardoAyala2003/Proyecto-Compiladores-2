// Test: Short-circuit OR
int x = 1;
int y = 0;
if (x == 1 || y / 0 > 5)
    print(1);
else
    print(0);
// Output: 1 (no division by zero error due to short-circuit)