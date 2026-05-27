// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Number of buckets
const unsigned int N = 26;

// Node structure
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash table
node *table[N];

// Word counter
int word_count = 0;

// Check whether word is in dictionary
bool check(const char *word)
{
    // Hash word
    int index = hash(word);

    // Traverse linked list
    node *cursor = table[index];

    while (cursor != NULL)
    {
        // Compare words (case-insensitive)
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Convert first letter to uppercase
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // Read words from file
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create new node
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // Copy word into node
        strcpy(n->word, word);

        // Hash word
        int index = hash(word);

        // Insert node into hash table
        n->next = table[index];
        table[index] = n;

        // Increase word count
        word_count++;
    }

    // Close dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory
bool unload(void)
{
    // Traverse every bucket
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Free linked list
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
