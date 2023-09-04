// Online C compiler to run C program online
#include <stdio.h>

main() {
    int x, n;
    float d;
    x = 7;
    d = x / 4;
    printf("Результат первого выполнея: %f \n", d);
    d = x / 4.;
    printf("Результат второго выполнения: %f \n", d);
    d = (float) x/4;
    printf("Результат третьего выполнения: %f \n", d);
    n = 7. / 4.;
    printf("Результат четвертого выполнеия: %d \n", n);
    
    int mod = 10%7;
    printf("Результат пятого выполнеия: %d \n", mod);
    
    float z;
    z = (d + 5 * x) - fabs(32 - 120) * sqrt(56);
    
    int p = 0;
    p++;
    ++p;
    p--;
    --p;
    
    z = 15 * p++;
    
    x += a;
}