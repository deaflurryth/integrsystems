// Online C compiler to run C program online
#include <stdio.h>

main() {
    float a, b;
    printf("Введите два значения: \n");
    scanf("%f%f", &a, &b);
    if(a>b){
        printf("a Больше b");
    }else if(a==b){
        printf("a равно b");
    }else{
        printf("a Меньше b");
    }
    
    int age;
    scanf("%d", &age);
    if (25 <=age && age < 40){ //Альтернатива &
        
    }else{
        
    }
    
    if (25 <=age || age < 40){ // Алтернатива |
        
    }else{
        
    }
    
    char c;
    
    scanf("%c", &c);
    
    switch(c){
        case 'a': 
            printf("Антилопа\n");
            break;
        case 'b':
            printf("sddfsfg\n");
            break;
        default:
            printf("неизвестная буква");
            break;
    }
    
    switch(c){
        case 'A':
        case 'a': 
            printf("Антилопа\n");
            break;
        case 'b':
            printf("sddfsfg\n");
            break;
        default:
            printf("неизвестная буква");
            break;
    }
}