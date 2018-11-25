

#include <string>
#include <cstring>
#include <iostream>
#include <fstream> //includes if and of stream
#include <cctype>
#include <stdio.h>
#include <string.h> //strlen, strcpy, strcat
using namespace std;


int stuff(int lineLength, istream& inf, ostream& outf);
//precondition: lineLength > 1, inf and outf open successfully
//this funcx takes the parameter lineLength specificed by user, and writes to outf the formated version of inf words.  It handles paragraph breaks, words fitting imperfectly on the line, proper spacing after '.' and '?', and breaking hyphenated words.  It returns 0 if all words fit perfectly on lines and 1 if one or more words did not fit on the line. If invalid argument passed returns 2.

bool findToken(char a[], istream& inf, int& currentWordCount, bool& hyphenFound);
//precondition: takes array created to hold token.  The array size is set to constant 140 max size.
//this function collects all non whitespace characters, returns array filled with one word, and increments wordCount.  If during collecting the non whitespace character it encounters a '-', it sets the hypenFound flag to true.  Each time function entered flag reset, array position 0 set to zero byte, and index reset to 0.

void stuffNormalWord(const char a[], const int lineLength, int& remainingOnLine, ostream& outf, bool& perfectFit, const int tokenSize, bool twoSpaces, bool hyphenFound);
//takes the word just collected in c string, the line Length, outfile, size of word/token, the flag for two spaces and hyphen word, and returns the outfile with normal word stuffed, updates remaining on line integer, and updates perfect fit flag
//if the word does not fit perfectly, it calls another function to stuff word.  if the word that doesnt fit is a hyphen containing word, it calls a function to handle stuffing that type of word.

void imperfectFitNormalWord(const char a[], const int lineLength, int& remainingOnLine, ostream& outf);
//precondition: the array containing the word has a zero byte signaling end of word...or you will be in some trouble.
//this function handles normal words that do not fit on a line.  It also processes hyphen containing words that do not fit on the line.

void hyphenWord(const char a[], const int lineLength, int& remainingOnLine, ostream& outf, bool& perfectFit, const int tokenSize, bool twoSpaces);
//precondition: the word that will be processed contains a hyphen (aka word portions)
//This function is called only when a hyphen containing word does not fit on a line.  It will break up the word into its subsequent word portions (anytime a hyphen is seen that makes end of word portion) and fit the word portions on the lines in outfile

void stuffWordPortion(char wp[], const int lineLength, int& remainingOnLine, ostream& outf, bool& perfectFit, const int wordPortionSize, bool twoSpaces, bool& firstPortionAdded);
//precondition: the array passed is the word portion array, filled with portion ending at - or word end.
//the function is very similar to stuffNormalWord, except that it considers if the first word portion has been added..in that case the portions added after to not need to account for spacing.  The function will add portions and change bool firstPortionAdded, but if the portion does not fit, it calls the imperfectFit function and stuff it like any other normal word that wont fit.


//**************************************************************
int main()
{
    ifstream inf("/Users/mariapalafox/Desktop/Frost.txt");  //named infile
    if (! inf )
    {
        cerr << "ERROR: cannot open frost file" << endl; //test if opened successfully
    }
    
    ofstream outf("/Users/mariapalafox/Desktop/Results.txt");
    if ( ! outf)
    {
        cerr << "could not find output file";
    }
    
    cout << "Enter line length: ";
    int len;
    cin >> len;
    cin.ignore(1000, '\n');
    
    int returnCode = stuff(len, inf, outf);
    cout << "  return code is : " << returnCode << endl;
  
    
    

}//end of main

//**************************************************************


int stuff(int lineLength, istream& inf, ostream& outf)
{
    
    const int LINEMAX = 140;
    //array to hold the word collected by findToken function.
    
    char token[LINEMAX];
   //array to hold the word collected by findToken function char by char
    
    if (lineLength < 1)
        return 2;
    //invalid argument
    
    char paragraph[] = "#P#";
    
    
    int currentWordCount = 0;
    //counter for total number of words processed by func
    //used in testing
    
    int remainingOnLine = lineLength;
    //object representing fluctuating amount of space remaining on line after adding a word
    
    int tokenSize = 0;
    //size of word collected by findToken function
    
    bool perfectFit = true;
    //set to false if a word does not fit on line
    
    bool twoSpaces = false;
    //set to true if the word that was just written to outf contained a '.' or '?' at end
    //reset after checking word just written
    
    bool firstWordPara = false;
    //set to true while processing #P# paragraph break case, prevents a file beginning with an empty line
    
    bool tokenFound;
    //set to true is a word was collected by findToken function
    //false if no more words remain to be processed in the input file
    
    bool hyphenFound = false;
    //if in findToken function a word is collected that contains one or more hyphens, this flag is set to true.
    //this is reset to false at beginning of findToken function
    
    
    for(;;)
    {
        
        tokenFound = findToken(token, inf, currentWordCount, hyphenFound);
        //call findToken, collects one word
        
        if(!tokenFound)
            break;
        //done collecting words
        
        
        //check if word "token" just collected is a paragraph break
        if(strcmp(token, paragraph) == 0)
        {
            if(currentWordCount == 1)
                firstWordPara = true;
            //set flag to true to prevent top empty line in outf
            
            //takes care of consecutive paragraph breaks
            do
            {
                tokenFound = findToken(token, inf, currentWordCount, hyphenFound);
            }while(strcmp(token, paragraph) == 0);
            
            //collects next word until it is a word other than "#P#", or at end of file
            if(!tokenFound)
                break;
            //prevents processing paragraph break if its the last paragraph
            
            //here because found a word after paragraph, process the break
            if(!firstWordPara)
            {
                outf << '\n' << '\n';
                remainingOnLine = lineLength;
            }
            if(firstWordPara)
                firstWordPara = false;
            //reset flag before continuing
            
        }//end of paragraph processing
        
        
        //get token size
        tokenSize = strlen(token);
        
        
        //IF we are at this point, the word collected is either a normal word, a word that will require two spaces after punctuation, or its a hyphen containing word
        //if its a hyphen word, the function that processes the word to fit on line is only called in case where it wont fit.  Essentially it is handled like a normal word unless it can not fit on remaining line size.
      stuffNormalWord(token,lineLength, remainingOnLine, outf, perfectFit, tokenSize, twoSpaces, hyphenFound);
        
       
        
        
       //already stuffed token, if it had . or ? at end, set twoSpaces to true for next word
        if(token[tokenSize - 1] == '.' || token[tokenSize - 1] == '?')
            twoSpaces = true;
        else
            twoSpaces = false;
        
        //this resets twoSpaces flag and token size is reset immediately following collecting the word
        
    }//end of for loop, end of processing input file
   
    //adds newline char just after last word on output file only if there was at least one word written to outfile
   if(currentWordCount != 0)
       outf << '\n';
    
    //for testing purposes
  //  outf << "this should be on new line";
    
    
    if(perfectFit)
        return 0;
    else
        return 1;
    
}

//**************************************************************
bool findToken(char a[], istream& inf, int& currentWordCount, bool& hyphenFound)
{
    
    
    char c;
    hyphenFound = false; //clear it each time you enter function
    a[0] = '\0'; //clear array for each new word to be entered
    int k = 0;
    while(inf.get(c) && k < 139) //max char are 139, which leaves 140 char to be zero byte. , will exit when at end of file
    {
        if(isspace(c) && k == 0) //skip over all spaces, just find words
            continue;
        if (isspace(c) && k > 0) //end of collecting word
        {
            a[k] = '\0'; //add zero byte to end of word collected
            currentWordCount++;
            return true;
        }
        if(!isspace(c)) //if its an interesting character, add to array
        {
            a[k] = c;
            //testing
            k++;
            if( c == '-' )
            {
              hyphenFound = true; //set flag to true
            }
        }
        
    }
    
    if(k > 0) //the array is filled and exited while loop because end of file OR at max array size (138 chars in) 139 position is zero byte
    {
        a[k] = '\0';
        currentWordCount++;
        return true;
    }
    return false; //end of file and no elements in array
}

//**************************************************************
void stuffNormalWord(const char a[], const int lineLength, int& remainingOnLine, ostream& outf, bool& perfectFit, const int tokenSize, bool twoSpaces, bool hyphenFound)
{
    
    for(;;)
    {
        if(remainingOnLine == lineLength)//on newline, will it fit?
        {
            
            if(tokenSize <= lineLength)//fits, awesome, add to outfile
            {
                outf << a;
                remainingOnLine = lineLength - (tokenSize);
                return;
            }
            
            if(tokenSize > lineLength) //doesnt fit on line, darn!
            {
                if(hyphenFound)//check word type
                {
                    hyphenWord(a, lineLength, remainingOnLine, outf, perfectFit, tokenSize, twoSpaces);
                    return;
                }
                else
                {
                    perfectFit = false; //set flag to return 1 later
                    imperfectFitNormalWord(a, lineLength,remainingOnLine, outf); //call function that handles this case
                    return;
                }
                
            }
            
        }
        
        if(remainingOnLine < lineLength) //already words on line?
        {
            //check if word before it is . or ? for appropriate spacing
            if(twoSpaces)
            {
                if(tokenSize <= (remainingOnLine - 2)) //adds spaces before adding word
                {
                    outf << ' ' << ' ';
                    outf << a;
                    remainingOnLine = remainingOnLine - (tokenSize + 2);
                    return;
                }
                
                if(tokenSize > (remainingOnLine - 2)) //wont fit? that sucks
                {
                    if(hyphenFound)//this flag is reset in findToken function each call
                    {
                        hyphenWord(a, lineLength, remainingOnLine, outf, perfectFit, tokenSize, twoSpaces);
                        return;
                    }
                    else
                    {
                        outf << endl; //try fitting it on a newline, maybe you will be in luck then!
                        remainingOnLine = lineLength;
                        continue;
                    }
                    
                }
            }
            if(!twoSpaces) //the case where each word is seperated by one space
            {
                
                if(tokenSize <= (remainingOnLine - 1)) //YAY it fits, including the space the preceeds it
                {
                    outf << ' ';
                    outf << a;
                    remainingOnLine = remainingOnLine - (tokenSize + 1);
                    return;
                }
                
                if(tokenSize > (remainingOnLine - 1))
                {
                    if(hyphenFound)
                    {
                        hyphenWord(a, lineLength, remainingOnLine, outf, perfectFit, tokenSize, twoSpaces);
                        
                        return;
                    }
                    else
                    {
    
                      outf << endl; //going to next line to try and fit word there
                      remainingOnLine = lineLength;
                      continue;
                    }
                    
                   
                }
            }
        }
        
    }//end of forever for loop
    
}

//**************************************************************
void imperfectFitNormalWord(const char a[], const int lineLength, int& remainingOnLine, ostream& outf)
{
    
    
    int i = 0;
    remainingOnLine = lineLength; //just a precaution, but they should already be set to equal each other
    
    while(a[i] != '\0') //keep adding word to outfile until reaching zero byte
    {
        if(remainingOnLine > 0) //keep adding to line until all positions taken
        {
            outf << a[i];
            i++;
            remainingOnLine--;
            continue;
        }
        
        if(remainingOnLine <= 0) //go to the next line and continue adding characters there
        {
            outf << endl;
            remainingOnLine = lineLength;
            outf << a[i];
            i++;
            remainingOnLine--;
        }
    }

}

//**************************************************************
void hyphenWord(const char a[], const int lineLength, int& remainingOnLine, ostream& outf, bool& perfectFit, const int tokenSize, bool twoSpaces)
{
    
    
    //creates array to hold word portion
    char wordPortion[140]; //max line is 139...position 139 is zero byte...so 0-138 are char
    wordPortion[0] = '\0';
    
    bool firstPortionAdded = false; //flag to see if spaces need to be considered before adding word portion
    
    int curTokenPos = 0; //index for token
    
    while(a[curTokenPos] != '\0')
    {
        //get wordPortion
        for(int i = 0; a[curTokenPos] != '\0'; i++) //filling new array up to - or when at end of token array
        {
            //adds to new array
            wordPortion[i] = a[curTokenPos];
            
            if(a[curTokenPos] == '-' || curTokenPos == (tokenSize - 1))
            {
                curTokenPos++;
                i++;
                wordPortion[i] = '\0'; //add zero byte to new array at end of word portion
                break;
            }
            else
            {
                curTokenPos++;
                continue;
            }
        }
        //broke out because have hyphen portion or because curTokenPos at zero byte
        
        
        //check if wordPortion[0] is equal to zero byte, if so then break out of loop because you are done processing the portions
        if(wordPortion[0] == '\0')
            return;
        
        //get size of portion
        int wordPortionSize = strlen(wordPortion);
        
        //stuff word portion
        stuffWordPortion(wordPortion, lineLength, remainingOnLine, outf, perfectFit, wordPortionSize, twoSpaces, firstPortionAdded);
        
    }
    
    return;
    
}
//**************************************************************
        
void stuffWordPortion(char wp[], const int lineLength, int& remainingOnLine, ostream& outf, bool& perfectFit, const int wordPortionSize, bool twoSpaces, bool& firstPortionAdded)
{
    for(;;)
    {
        if(!firstPortionAdded) //first portion not added so need to account for spaces
        {
           
                if(remainingOnLine == lineLength)//on newline, will it fit?
                {
                    if(wordPortionSize <= lineLength)
                    {
                        outf << wp;
                        remainingOnLine = lineLength - (wordPortionSize);
                        wp[0] = '\0'; //reset array to indicate word portion already added
                        firstPortionAdded = true;
                        return;
                    }
                    
                    if(wordPortionSize > lineLength) //if the word portion is too big to fit, treat it like a normal word that wont fit
                    {
                        perfectFit = false;
                        imperfectFitNormalWord(wp, lineLength,remainingOnLine, outf);
                        wp[0] = '\0';
                        firstPortionAdded = true;
                        return;
                    }
                }
            
                if(remainingOnLine < lineLength) //already words on line
                {
                    //check if word before it is . or ? for appropriate spacing
                    if(twoSpaces)
                    {
                        if(wordPortionSize <= (remainingOnLine - 2))
                        {
                            outf << ' ' << ' ';
                            outf << wp;
                            remainingOnLine = remainingOnLine - (wordPortionSize + 2);
                            wp[0] = '\0';
                            firstPortionAdded = true;
                            return;
                        }
                        
                        if(wordPortionSize > (remainingOnLine - 2)) //go to newline to fit word portion
                        {
                            outf << endl;
                            remainingOnLine = lineLength;
                            continue;
                        }
                    }
                    
                    if(!twoSpaces)
                    {
                        if(wordPortionSize <= (remainingOnLine - 1))
                        {
                            outf << ' ';
                            outf << wp;
                            remainingOnLine = remainingOnLine - (wordPortionSize + 1);
                            wp[0] = '\0';
                            firstPortionAdded = true;
                            return;
                        }
                        
                        if(wordPortionSize > (remainingOnLine - 1)) //go to newline to fit word portion
                        {
                            outf << endl;
                            remainingOnLine = lineLength;
                            continue;
                        }
                    }
                
            }
            
        }
        //now dont have to worry about spacing because there are no spaces between word portions that came from same fragment
        if(firstPortionAdded)
        {
                if(remainingOnLine == lineLength)//on newline, will it fit?
                {
                    if(wordPortionSize <= lineLength)
                    {
                        outf << wp;
                        remainingOnLine = lineLength - (wordPortionSize);
                        wp[0] = '\0';
                        return;
                    }
                    
                    if(wordPortionSize > lineLength) //wont fit, stuff like normal imperfect word
                    {
                        perfectFit = false;
                        imperfectFitNormalWord(wp, lineLength,remainingOnLine, outf);
                        wp[0] = '\0';
                        return;
                    }
                    
                }
                
                if(remainingOnLine < lineLength) //already words on line
                {
                    if(wordPortionSize <= remainingOnLine)
                    {
                        outf << wp;
                        remainingOnLine = remainingOnLine - wordPortionSize;
                        wp[0] = '\0';
                        return;
                    }
                    
                    if(wordPortionSize > remainingOnLine)
                    {
                        outf << endl;
                        remainingOnLine = lineLength;
                        continue;
                    }
                }
                
        }//end if portion added
            
            
    }//end of forever for loop
    
}

