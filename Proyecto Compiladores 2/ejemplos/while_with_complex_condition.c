// Test: While with complex condition
int i = 0;
int sum = 0;
while (i < 5 && sum < 10) {
    sum = sum + i;
    i = i + 1;
    print(sum);
}
// Output: 0, 1, 3, 6, 10