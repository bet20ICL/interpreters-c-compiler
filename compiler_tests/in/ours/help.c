int f() {
    int a = 10, b = 3, c = 5;
    return a + b - c * a / b & c | a % b ^ c && a || b == c;
}