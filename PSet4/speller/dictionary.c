// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27
#define case 97

// Represents a node in a trie
typedef struct node
{
    // marker to set specific nodes as words
    bool isWord;
    // Create a node to house N children
    struct node *children[N];
}
node;

// Represents a trie
node *root = NULL;

void freeNode(node *r);

// Set counter for number of words loaded in dictionary
int numWords;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary list
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Create a universal root node to be used to traverse through the trie
    root = calloc(27, sizeof(node));
    node *pointer = root;

    // Initialize every index to NULL (must be some value to be error free)
    for (int i = 0; i < 27; i++)
    {
        pointer->children[i] = NULL;
    }

    int index;
    char c;

    // Insert words into trie
    while (1)
    {
        // Open the file and get a new char
        c = fgetc(file);

        if (feof(file))
        {
            break;
        }

        if (c == '\'')
        {
            index = N - 1;
        }
        else
        {
        index = c - case;
        }

        if (isalpha(c) || c == '\'')
        {

            if (pointer->children[index] == NULL)
            {
                // Allocate memory for new node and initialize it
                pointer->children[index] = calloc(1, sizeof(node));
                // Set the pointer equal to that new node
                pointer = pointer->children[index];
            }
            else
            {
                pointer = pointer->children[index];
            }
        }
        else
        {
            pointer->isWord = true;
            pointer = root;
            numWords++;
        }
    }
    fclose(file);

    // Indicate success
    return true;
}



// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numWords;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Set the pointer to equal the root with every new word
    node *pointer = root;

    // Create array to traverse through
    int len = strlen(word);
    int index = 0;
    char c[len];

    // Create a word array with all letters lowercase
    for (int i = 0; i < len; i++)
    {
        if (isupper(word[i]))
        {
           c[i] = tolower(word[i]);
        }
        else
        {
           c[i] = word[i];
        }
    }

    // Set a null terminator
    c[len] = '\0';


    // Loop to go through the every letter in the word
    for (int i = 0; i<=len; i++)
    {
        // Index would equal the position in the node
        index = c[i] - case;

        if (c[i] == '\'')
        {
            index = N - 1;
        }

        if (c[i] != '\0')
        {
            // Checking basics for the location if NULL then automatically not in node so false
            if (pointer->children[index] == NULL)
            {
                return false;
            }
            // Otherwise, if it's not NULL it has to be a valid entry in the node
            else
            {
                pointer = pointer->children[index];
            }
        }
        else
        {
            if (pointer->isWord == true)
            {
                return true;
            }
        }
    }
    return false;
}


bool unload(void)
{
    freeNode(root);
    return true;
}


void freeNode(node *r)
{

    if (r == NULL)
    {
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (r->children[i] != NULL)
        {
            freeNode(r->children[i]);
        }
    }
    free(r);
}
