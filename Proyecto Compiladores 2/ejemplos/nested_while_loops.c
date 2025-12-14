// Test: Nested while loops
int i = 0;
while (i < 3) {
    int j = 0;
    while (j < 2) {
        print(i * 10 + j);
        j = j + 1;
    }
    i = i + 1;
}
// Output: 0, 1, 10, 11, 20, 21