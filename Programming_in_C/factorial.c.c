#include <stdio.h>

int find_fact(int x)
{
    if(x==0)
    return 1;
    
   return(x*find_fact(x-1));
}

int main()
{
     int num =0;
     int factorial =0;
     int i=0;
     printf("Enter the number to calculte factorial!\n");
     scanf("%d", &num);
     factorial = find_fact(num);
      printf("Factorial = %d\n", factorial);
}
