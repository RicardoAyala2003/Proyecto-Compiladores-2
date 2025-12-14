// Test: Count digits in a number
int n = 12345;
int count = 0;

if (n == 0) {
    count = 1;
} else {
    if (n < 0)
        n = -n;
    while (n > 0) {
        count = count + 1;
        n = n / 10;
    }
}

print(count);  // Output: 5