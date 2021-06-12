#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define TEXT_LEN 10000 // Maximum number of text allowed
#define BUFFER_SIZE 100 // Buffer size for each line in the text
#define MAX_WORDS 500 // maximum number of different words
#define WORD_LEN 15 // maximum word length

int main() {
    char text[TEXT_LEN + 1]; // The text entered
    char buffer[BUFFER_SIZE];
    char endStr[] = "*\n"; // end of text signifier
    const char space = ' ';
    const char quote = '\'';

    char words[MAX_WORDS][WORD_LEN + 1]; // words in the text array
    int nWord[MAX_WORDS]; // number of words occurrences {}
    char word[WORD_LEN + 1]; // current word been handled
    int wordLen= 0; // length of the current word been handled
    int wordCount = 0; // number of words stored

    printf("\nEnter text in an arbitrary number of lines");
    printf("\nEnter a line containing just an asterisk to end input:\n");
    while (true) {
        // read each line into buffer till *\n is encountered
        if (!strcmp(fgets(buffer, BUFFER_SIZE, stdin), endStr)){
            break;
        }

        // If we have already reached the maximum number of text allowed
        if ((strlen(text)+strlen(buffer)+1) > TEXT_LEN) {
            printf("Maximum capacity for text exceeded. Terminating program");
            return 1;
        }

        // add line buffer to text
        strcat(text, buffer);
    }

    // convert all quotes in the text to space
    for (int i = 0; i < strlen(text); i++) {
        if(text[i] == quote || isalnum(text[i])) {
            continue;
        }
        text[i] = space;
    }


    int index = 0;
    while(true)
    {
        while(text[index] == space)
            ++index;
        if (text[index] == '\0')
            break;

        wordLen = 0; // reset word length
        while(text[index] == quote || isalpha(text[index]))
        {
            if (wordLen ==  WORD_LEN) {
                printf("Maximum number of word reached \n");
                return 1;
            }
            // read the current word into and array of character in lowercase form
            word[wordLen++] = tolower(text[index++]);
        }
        // add a terminating character to the current word
        word[wordLen] = '\0';
        bool isNew = true;
        for (int i = 0; i < wordCount; i++)
        {
            if (strcmp(word, words[i]) == 0)
            {
                ++nWord[i];
                isNew = false;
                break;
            }
        }

        if (isNew)
        {
            if (wordCount >= MAX_WORDS)
            {
                printf("\n Maximum number of words reached");
                return 1;
            }

            strcpy(words[wordCount], word);
            nWord[wordCount++] = 1;
        }

    }
    for(int i = 0 ; i<wordCount ; i++)
    {
        if( !(i%3) )
            printf("\n");
        printf(" %-15s%5d", words[i], nWord[i]);
    }


//    printf("All done");
    return 0;
}
