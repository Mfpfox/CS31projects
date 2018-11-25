// Project 5 -- Word stuffer

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

// stuff function return values

const int STUFF_OK = 0;
const int STUFF_WORD_PORTION_BROKEN = 1;
const int STUFF_SHORT_LINE_LENGTH = 2;

// arbitrary values from problem spec

const int MAX_INPUT_LINE_LEN = 140;

// paragraph break indicator

const char PARAGRAPH_BREAK[4] = "#P#";

// function prototypes

bool getNextWord(istream& inf, char word[], int wordLimit);
bool emitWord(ostream& outf, char word[], int lineLen, int& nPrecedingSpaces,
              int& pos);
void writeText(ostream& outf, const char word[], int startPos, int len,
               int nPrecedingSpaces, int& pos);
void writeChar(ostream& outf, char ch, int& pos);

// stuff function

int stuff(int lineLen, istream& inf, ostream& outf)
{
    if (lineLen < 1)
        return STUFF_SHORT_LINE_LENGTH;
    
    char word[MAX_INPUT_LINE_LEN+1];
    
    // The first word is special, in that no output must appear before it
    
    // Get first word
    
    word[0] = '\0';
    while (getNextWord(inf, word, sizeof(word))  &&
           strcmp(word, PARAGRAPH_BREAK) == 0)
        ;
    if (word[0] == '\0')
        return STUFF_OK;  // No words in input, so no output at all
    
    int returnValue = STUFF_OK;
    bool precededByBreak = false;
    int nPrecedingSpaces = 0;
    int pos = 0;  // position of next character to be written on output line
    
    // Write first word
    
    if ( ! emitWord(outf, word, lineLen, nPrecedingSpaces, pos))
        returnValue = STUFF_WORD_PORTION_BROKEN;
    
    // Process each subsequent input word until end of file
    
    while (getNextWord(inf, word, sizeof(word)))
    {
        if (strcmp(word, PARAGRAPH_BREAK) == 0)
            precededByBreak = true;
        else // it's an input word
        {
            // Handle end/start of paragraph
            
            if (precededByBreak)
            {
                writeChar(outf, '\n', pos);  // end current line
                writeChar(outf, '\n', pos);  // empty line between paragraphs
                nPrecedingSpaces = 0;
            }
            
            // Write word along with any preceding spaces
            
            if ( ! emitWord(outf, word, lineLen, nPrecedingSpaces, pos))
                returnValue = STUFF_WORD_PORTION_BROKEN;
        }
    }
    
    writeChar(outf, '\n', pos);  // end last line
    
    return returnValue;
}

// getNextWord function
//   If there is no next word (end of file encountered), return false.
//   Otherwise, put the next word in the word array (a word that is too
//   long is silently truncated) and return true.

bool getNextWord(istream& inf, char word[], int wordLimit)
{
    // skip whitespace
    
    char ch;
    do
    {
        if ( ! inf.get(ch))
            return false;
    } while (isspace(ch));
    
    // accumulate nonwhitespace characters into word
    
    int pos = 0;
    do
    {
        // store the character if there's room for it and the eventual '\0'
        
        if (pos < wordLimit-1)
        {
            word[pos] = ch;
            pos++;
        }
        if ( ! inf.get(ch))
            break;
    } while( ! isspace(ch));
    if (wordLimit > 0)
        word[pos] = '\0';
    
    return true;
}

// emitWord function
//   write a word along with any preceding space.  Split the word if
//   necessary.  Update the current output line position.

bool emitWord(ostream& outf, char word[], int lineLen, int& nPrecedingSpaces,
              int& pos)
{
    bool returnValue = true;  // will set to false if long word was split
    
    // At all times, the remaining part of the word to write will start
    // at position wordStart of the word array, and extend for wordLen
    // characters.
    
    int wordStart = 0;
    int wordLen = strlen(word);
    
    // Repeat as long as the remaining part of the word won't fit
    
    while (pos + nPrecedingSpaces + wordLen > lineLen)
    {
        // See if there's a hyphen in the part that fits
        
        int firstPartLen;
        for (firstPartLen = lineLen - (pos + nPrecedingSpaces);
             firstPartLen > 0  &&  word[wordStart + firstPartLen-1] != '-';
             firstPartLen--)
            ;
        int segmentLen = 0;  // length of part of word to be written
        if (firstPartLen > 0)
            segmentLen = firstPartLen;
        else if (pos + nPrecedingSpaces == 0)  // portion too long
        {
            segmentLen = lineLen;  // will write as much as fits
            returnValue = false;
        }
        
        // Write segment of word and determine remaining part of word
        
        if (segmentLen > 0)
        {
            writeText(outf, word, wordStart, segmentLen, nPrecedingSpaces, pos);
            wordStart += segmentLen;
            wordLen -= segmentLen;
        }
        
        // Write newline; remaining part of word will start on next line
        
        writeChar(outf, '\n', pos);
        nPrecedingSpaces = 0;
    }
    
    // Remaining part of word fits, so write it
    
    writeText(outf, word, wordStart, wordLen, nPrecedingSpaces, pos);
    
    // Set nPrecedingSpaces for next word to be emitted
    
    char lastChar = word[wordStart + wordLen-1];
    if (lastChar == '.'  ||  lastChar == '?')
        nPrecedingSpaces = 2;
    else
        nPrecedingSpaces = 1;
    
    return returnValue;
}

// writeText function
//   write text from a word, preceded by spaces.  Update output line position.

void writeText(ostream& outf, const char word[], int startPos, int len,
               int nPrecedingSpaces, int& pos)
{
    for ( ; nPrecedingSpaces > 0; nPrecedingSpaces--)
        writeChar(outf, ' ', pos);
    for (int k = startPos; k < startPos + len; k++)
        writeChar(outf, word[k], pos);
}

// writeChar function
//   write one character.  Update output line position.

void writeChar(ostream& outf, char ch, int& pos)
{
    outf << ch;
    if (ch == '\n')
        pos = 0;
    else
        pos++;
}

// test driver for stuff function

int main()
{
    for (;;)
    {
        cout << "Enter an input filename (or empty line to quit): ";
        char inputFilename[500];
        cin.getline(inputFilename, sizeof(inputFilename));
        if (inputFilename[0] == '\0')
            break;
        ifstream inf(inputFilename);
        if ( ! inf)
        {
            cerr << "Cannot open " << inputFilename << endl;
            continue;
        }
        
        cout << "Enter a line length: ";
        int lineLen;
        cin >> lineLen;
        cin.ignore(10000, '\n');
        
        cout << "Enter an output filename (or empty line for the screen): ";
        char outputFilename[500];
        cin.getline(outputFilename, sizeof(outputFilename));
        int returnValue;
        if (outputFilename[0] == '\0')
            returnValue = stuff(lineLen, inf, cout);
        else
        {
            ofstream outf(outputFilename);
            if ( ! outf)
            {
                cerr << "Cannot create " << outputFilename << endl;
                continue;
            }
            returnValue = stuff(lineLen, inf, outf);
        }
        
        cout << "stuff returned " << returnValue << endl;
    }
}
