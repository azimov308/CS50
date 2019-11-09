//**********************************//
// Code creates pyramids from Mario //
//**********************************//

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Declare Variables
    int height;

    //Loop to get Height
    do 
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Loop to draw half pyramid
    for (int row = height; height > 0; height--)
    {
        //Draw whitespaces
        for (int ws = 1; ws <= height - 1; ws++)
        { 
            printf(" ");
        }
        //Left pyramid
        for (int ht = height - 1; ht < row; ht++)
        {
            printf("#");
        }
        
        //Space between pyramids
        printf("  ");
        
        //Right Pyramid
        for (int ht = height - 1; ht < row; ht++)
        {
            printf("#");
        }
        
        //Next line
        printf("\n");
    }
}