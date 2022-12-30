int f() {
    int b = 3, a, c = 5;
    a = (b += c) + (--c + 2);
    return a;
}