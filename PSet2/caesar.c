//**********************************************//
// Encrypts a message using a number as the key //
//**********************************************//

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void checkArgs(int argc);
void isNumeric(int argLen, string firstArg);
void encMess(int k, string plaintext);

int main(int argc, string argv[])
{
    //Check if there are enough arguments
    checkArgs(argc);
    
    //Variables
    string firstArg = argv[1];
    int k = atoi(argv[1]) % 26;
    
    //Check if argument is numeric
    int argLen = strlen(firstArg);
    isNumeric(argLen, firstArg);
    
    //Ask user for message to be encrypted
    string plaintext = get_string("plaintext: ");
    
    //Encrypt Message
    printf("ciphertext: ");
    encMess(k, plaintext);
    printf("\n");
}

//Check if there are enough arguments
void checkArgs(int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        exit(1);
    }
}

//Check if argument is numeric
void isNumeric(int argLen, string firstArg)
{
    for (int i = 0; i < argLen; i++)
    {
        if (isdigit(firstArg[i]))
        {
            continue;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            exit(1);
        }
    }
}

void encMess(int k, string plaintext)
{
    int inpLen = strlen(plaintext);
    for (int i = 0; i < inpLen; i++)
    {
        int charNum = 0;
        //Lowercase
        if (islower(plaintext[i]))
        {
            charNum = ((((int)plaintext[i] - 97 + k) % 26) + 97);
            printf("%c", (char) charNum);
        }
        //Uppercase
        else if (isupper(plaintext[i]))
        {
            charNum = ((((int)plaintext[i] - 65 + k) % 26) + 65);
            printf("%c", (char) charNum);
        }
        //If not upper or lowercase
        else
        {
            charNum = plaintext[i];
            printf("%c", charNum);
        }
    }
}