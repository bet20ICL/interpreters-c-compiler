int f() {
    int b = 3, a, c = 5;
    a = b + c ? ++b : ++c ;
    return b;
}