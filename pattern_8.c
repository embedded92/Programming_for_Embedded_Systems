/*
 * pattern_8.c
 *
 *  Created on: Dec 15, 2019
 *      Author: ramneet
 */
#include <stdio.h>
int main()
{
    int x = 0,y = 0;
    unsigned int size = 0;
    printf("Enter the size = ");
    scanf("%u",&size);
    for(x=1; x<(size*2); ++x)
    {
        for(y=1; y<=size; ++y)
        {
            // Condition for corner and center intersection space
            if(((x==1) && (y==1 || y==size)) ||
                    ((x==size) && ((y==1) || (y==size))) ||
                    (x==size*2-1 && (y==1 || y==size)))
            {
                printf(" ");
            }
            else if((x==1) || (x==size) || (x==(size*2)-1) || (y==1) || (y==size))
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
