int f(int x, int y) {
    int b = 3, a = 10, c = 5, d;
    y = x = b++;
    a = --y;
    d = ((x == 3) && (y == 2) && (a == 2));
    return d;
}