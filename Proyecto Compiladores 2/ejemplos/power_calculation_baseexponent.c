// Test: Power calculation (base^exponent)
int base = 2;
int exponente = 10;
int resultado = 1;
int i = 0;

while (i < exponente) {
    resultado = resultado * base;
    i = i + 1;
}

print(resultado);  // Output: 1024