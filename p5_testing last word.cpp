



#include <cstring>
#include <iostream>
#include <fstream> //includes if and of stream
#include <cctype>
#include <stdio.h>
#include <string.h> //strlen, strcpy, strcat
using namespace std;


int stuff(const int lineLength, istream& inf, ostream& outf);
bool findToken(char a[], istream& inf, int& wordCount, bool& lastWord);



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
    cout << "  stuff output: " << returnCode << endl;
    
    
    
    
}//end of main









int stuff(const int lineLength, istream& inf, ostream& outf)
{
    int wordCount = 0;
    const int LINEMAX = 140;
    char token[LINEMAX];
    if (lineLength < 1)
        return 2;
    
    bool lastWord = false;
    bool perfectFit = true;
    int remainingOnLine = lineLength;
    
    for(;;)
    {
        bool tokenFound = findToken(token, inf, wordCount, lastWord);
        if(!tokenFound)
            break;
        
        outf << token;
        outf << endl;
        
        //if token is paragraph break
        //else if token is hyphen
        //else if token is . or ?
        //else token is normal word
       
        
        
        
    }//end of for loop, broke out because end of file
    
    
    
    
    
    if(perfectFit)
        return 0;
    else
        return 1;
    
}

//**************************************************************
bool findToken(char a[], istream& inf, int& wordCount,bool& lastWord)
{
    char c;
    a[0] = '\0'; //clear array for each new word to be entered
    int k = 0;
    while(inf.get(c) && k < 140) //max char are 139, which leaves 140 char to be zero byte
    {
        if(isspace(c) && k == 0)
            continue;
        if(!isspace(c)) //if its an interesting character
        {
            a[k] = c;
            k++;
            continue;
        }
        
        if (isspace(c) && k > 0) //end of collecting word
        {
            a[k] = '\0';
            wordCount++;
            return true;
        }
    }
    
    if(k > 0) //the array is filled and exited while loop because end of file
    {
        a[k] = '\0';
        wordCount++;
        cout << "last word entered";
        return true;
    }
    
    return false; //end of file and no elements in array
}



