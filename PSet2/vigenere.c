//**********************************************//
// Encrypts a message using a string as the key //
//**********************************************//

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void shift(int ptLen, int keyLen, string plaintext, string keyword);
void alphaArg(int keyLen, string keyword);
void checkArgs(int argc);

int main(int argc, string argv[])
{
    //Checks num of arg's
    checkArgs(argc);
    
    //Get length of key
    int keyLen = strlen(argv[1]);
    //Create a keyword string
    string keyword = argv[1];

    //Checks if argument is alphabetic
    alphaArg(keyLen, keyword);

    //Gets plaintext string
    string plaintext = get_string("plaintext: ");
    //Gets length of plaintext
    int ptLen = strlen(plaintext);
    printf("ciphertext: ");
    
    //Shifts value
    shift(ptLen, keyLen, plaintext, keyword);
}

void shift(int ptLen, int keyLen, string plaintext, string keyword)
{
    for (int i = 0, j = 0, c = 0, k = 0; i < ptLen; i++, j++)
    {
        if (j == keyLen)
        {
            j = 0;
        }
        //Check's if lowercase
        if (islower(plaintext[i]))
        {
            k = (((int) keyword[j]) - 97);
            c = ((((((int) plaintext[i]) - 97) + k) % 26) + 97);
            printf("%c", c);
        } 
        //Check's if uppercase
        else if (isupper(plaintext[i]))
        {
            k = (((int) keyword[j]) - 65);
            c = ((((((int) plaintext[i]) - 65) + k) % 26) + 65) - 6;
            printf("%c", (char)c);
        }
        //Otherwise skip and replace with current
        else
        {
            printf("%c", (char)plaintext[i]);
            j -= 1;
        }
    }
    printf("\n");
}

void alphaArg(int keyLen, string keyword)
{
    for (int i = 0; i < keyLen; i++)
    {
        if (isalpha(keyword[i]))
        {
            //add if upper or lower and make it all lower
            if (isupper(keyword[i]))
            {
                keyword[i] = (keyword[i] % 65) + 97;
            }
            else
            {
                continue;
            }
        }
        else
        {
            printf("Usage: ./vigenere keyword\n");
            exit(1);
        }
    }
}

void checkArgs(int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        exit(1);
    }
}