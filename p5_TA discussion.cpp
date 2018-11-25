//
//  
#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;


int main() {
    bool haveASpaceBefore = false; //a flag to detect if I have seen a space before this character
    char myCharArr[100] = "  Hello,   this      is a string with       extra white spaces.   ";
    char trimmedArray[100]; // a buffer array to store words with at most 1 space apart
    int indexForTrimmedArray = 0;
    for(int i = 0; myCharArr[i] != '\0'; i++)
    {
        //leading whitespace
        if(myCharArr[i] == ' ' && i == 0)
        {
            while(myCharArr[i] == ' ')
            {
                i++;
            }
            i--; // make sure you set this i backwards to compansate the i++ when exit this for loop's iteration
        }
        //none a space
        else if(myCharArr[i] != ' ')
        {
            haveASpaceBefore = false; // make sure to reset this flag
            trimmedArray[indexForTrimmedArray] = myCharArr[i];
            indexForTrimmedArray++;
        }
        // not a leading whitespace
        else if(myCharArr[i] == ' ' && i != 0)
        {
            if(haveASpaceBefore) // a flag to detect if I have seen a space before this character
            {
                while(myCharArr[i] == ' ')
                {
                    i++;
                }
                i--;// make sure you set this i backwards to compansate the i++ when exit this for loop's iteration
            }
            else
            {
                haveASpaceBefore = true;
                trimmedArray[indexForTrimmedArray] =  myCharArr[i];
                indexForTrimmedArray++;
            }
        }
        trimmedArray[indexForTrimmedArray+1] = '\0'; // terminate this c-string with a '\0'
    }
    
    cout << trimmedArray << endl;
    
}
/*
    ifstream infile("Untitled.txt"); //can store these with main.cpp
    const int MAX = 140;
    char line[MAX];
    infile.getline(line,MAX);
    
    cout << line << endl; //outputs file line
    
    infile.getline(line,MAX);
    infile.getline(line,MAX);//gets next line overwrites what was in first
    while(infile.getline(line,MAX)) //always true when you have something to read, keeps reading in until the end
    
        ofstream outfile("results.txt);
                         outfile << "what";
                         outfile << "fjdklsa"; //adds
    
    infile.getline(line,MAX);
    



void printchars(const char* str)
                {
                    int i = 0;
                    while(*(str + 1) != '\0')
                            cout << *(str + i) << endl;
                }
//break function
//in main
                         int *ptr = nullptr;
                         cout << *ptr << endl; //cant output nullptr, dont access address of nullptr
                         char arr[2] = {}
                         printchars(ptr)//this will break function
