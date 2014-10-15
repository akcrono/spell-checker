/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"
#include <string.h>

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* parsingNode=dict;
    for (int i=0; word[i]!='\0'; i++)
    {
        if (word[i]=='\'')
            parsingNode=parsingNode->children[26];
        else
        {

            parsingNode=parsingNode->children[tolower(word[i])-97];
        }
        if (parsingNode==NULL)
            return false;
            
    }

    return parsingNode->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    dSize=0;
    dict = malloc(sizeof(node));
    char currentWord[LENGTH+1];
    node* parsingNode;
    
    FILE* inptr = fopen(dictionary, "r");
    fscanf(inptr, "%s", currentWord);
    while (feof(inptr)==0)
    {
        parsingNode=dict;  
        for (int i=0; currentWord[i]!='\0'; i++)
        {
            int tryKey;
            if (currentWord[i]=='\'')
                tryKey=26;
            else
                tryKey = currentWord[i]-97;
            if (parsingNode->children[tryKey]==NULL)
            {
                node* temp = malloc(sizeof(node));
                temp->is_word=false;
                parsingNode->children[tryKey] = temp;
            }
            parsingNode=parsingNode->children[tryKey];
        }
        parsingNode->is_word = true;
        dSize++;
        fscanf(inptr, "%s", currentWord);
    }
    // printTrie(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    deleteNode(dict);
    return true;
}
void deleteNode(node* tempNode)
{
    for (int i=0; i<27; i++)
    {
        if (tempNode->children[i]!=NULL)
            deleteNode(tempNode->children[i]);
    }
    free(tempNode);
}

