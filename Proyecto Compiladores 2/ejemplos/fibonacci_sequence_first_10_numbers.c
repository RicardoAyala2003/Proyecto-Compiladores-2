// Test: Fibonacci sequence (first 10 numbers)
int n = 10;
int a = 0;
int b = 1;
int i = 0;

while (i < n) {
    print(a);
    int temp = a + b;
    a = b;
    b = temp;
    i = i + 1;
}
// Output: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34