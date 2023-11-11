
#include <stdio.h>

int main()
{
    printf("Enter the lenth of array!\n");
    int len;
    scanf("%d",&len);
    printf("%d\n", len);
    
    int array[len];
  
   printf("Enter the integer value to sort in array....\n");
  for(int i=0; i<len; i++)  
    {  
        scanf("%d", &array[i]);  
    }    

  printf("\nElements in array are: ");  
    for(int i=0; i<len; i++)  
    {  
        printf("%d  \n", array[i]);  
    } 
    printf("ODD Numbers = ");    
 for(int j =0; j<len; j++)
  {
      if(array[j]%2 !=0)
      printf("%d  " , array[j]);
      
  }
    return 0;
}
