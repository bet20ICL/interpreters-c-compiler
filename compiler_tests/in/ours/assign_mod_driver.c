
int f(int x, int y);

int main()
{
    int a = 12; 
    a %= 4;
    return !(f(12,4)==a);
}
