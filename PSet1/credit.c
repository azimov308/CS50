//********************************************************//
// Code checks if CC# is fake and what type of card it is //
//********************************************************//

#include <stdio.h>
#include <cs50.h>

int getLength(long int i);
bool checkSumAndValidity(int length, int arr[], long int n);
int cardType(int arr[], int length);

int main(void)
{
    long int n;
    n = get_long("Number: ");
    int length = getLength(n);
    int arr[length];
    checkSumAndValidity(length, arr, n);
    
    for (int i = 0; i < length; i++)
    {
        arr[i] = n % 10;
        n /= 10;
    }
    
    int num = cardType(arr, length);
    //printf("%i", num);
    
    if (length == 15 && num == 1)
    {
        printf("AMEX\n");
    } 
    else if (length == 16 && num == 2)
    {
        printf("MASTERCARD\n");
    }
    else if (length == 13 || length == 16)
    {
        printf("VISA\n");
    }
}

//Gets the length of input
int getLength(long int i) 
{
    int count = 0;
    while (i != 0)
    {
        i /= 10;
        count++;
    }
    return count;
}

//Checks with Luhn's Algo if valid/not
bool checkSumAndValidity(int length, int arr[], long int n)
{
    int sum = 0;
    
    //Used to reverse
    for (int i = 0; i < length; i++)
    {
        arr[i] = n % 10;
        n /= 10;
    }
    
    //Card must be 13, 15, or 16 numbers long
    if (length != 13 && length != 15 && length != 16) 
    {
        printf("INVALID\n");
        exit(0);
    }
    
    //Gets sum
    for (int i = 0; i < length; i++)
    {
        if (i % 2 == 1)
        {
            arr[i] *= 2;
            if (arr[i] > 9)
            {
                int rem = 0;
                rem = arr[i] % 10;
                rem += 1;
                sum += rem;
            } 
            else 
            {
                sum += arr[i];
            }
        } 
        else 
        {
            sum += arr[i];
        }
    }
    //Checks if last digit in sum is 0
    if (sum % 10 == 0)
    {
        //printf("VALID");
        return true;
    } 
    else
    {
        printf("INVALID\n");
        exit(0);
    }
}

//Returns the type of card
int cardType(int arr[], int length)
{
    int temp; 
    int start = 0;
    int end = length - 1;
    
    //Reverses the array for second part of Luhn's method
    while (start < end) 
    { 
        temp = arr[start];    
        arr[start] = arr[end]; 
        arr[end] = temp; 
        start++; 
        end--; 
    }
    
    int num = 0;
    int check = 0;
    
    //American Express = 1
    if (arr[0] == 3)
    {
        if (arr[1] == 4 || arr[1] == 7)
        {
            num = 1;
            check = 1;
        }
    }
    //Mastercard = 2
    if (arr[0] == 5)
    {
        if (arr[1] >= 1 && arr[1] <= 5)
        {
            num = 2;
            check = 1;
        }
    }
    //Visa = 3
    if (arr[0] == 4)
    {
        num = 3;
        check = 1;
    }
    
    if (check != 1) 
    {
        printf("INVALID\n");
        exit(0);
    }
    
    return num;
}