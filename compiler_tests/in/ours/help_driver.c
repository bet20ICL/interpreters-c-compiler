int f();

int main()
{
    int a = 10, b = 3, c = 5;
    return !(f()==(a + b - c * a / b & c | a % b ^ c && a || b == c));
}
