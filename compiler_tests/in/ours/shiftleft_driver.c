
int f(int x, int y);

int main()
{
    if( (f(0x0F,0x10)!= 0x0F << 0x10) ) return 1;
    if( (f(0x00,0x10)!= 0x00 << 0x10) ) return 1;
    if( (f(0x0F,0x00)!= 0x0F << 0x00) ) return 1;
    if( (f(0x00,0x00)!= 0x00 << 0x00) ) return 1;
    return 0;
}