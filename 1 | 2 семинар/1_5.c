// Online C compiler to run C program online
#include <stdio.h>

main() {
    for (int i=0; i < 15; i++){
        printf("%d \n" , i);
    }
    int i;
    float x;
    for(i=0, x =.2; i <15; i++, x+=0.1){
        printf("%d %f \n", i, x);
    }
    
    int N;
    int counter = 0;
    do{
        scanf("%d", &N);
    } while( N<=0);
    
    while(N>0){
        N/=10;
        counter++;
    }
    printf("%d", counter);
    
    int A, B;
    while(1){
        printf("\nВведите делимое и делитель");
        scanf("%d%d", &A, &B);
        if (A == 0 && B == 0){
            break;
        }
        if(B==0){
            printf("Деление на ноль");
            continue;
        }
        printf("%d, %d", A/B, A%B);
    }
}