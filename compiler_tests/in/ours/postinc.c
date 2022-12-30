int f(int x, int y)
{
    int a = 8, b = 12;
    b = a++;
    return (b == 8) && (a == 9);
}
