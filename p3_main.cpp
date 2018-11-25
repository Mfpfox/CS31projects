#include <cctype>
#include <string>
#include <iostream>
using namespace std;


//FUNCTION PROTOTYPES
bool hasCorrectSyntax(string song);
int translateSong(string song, string& instructions, int& badBeat);
bool isColor(char c);
int totalBeats(string song);


int main()
{
    string song;
    //assigned values to check whether my functions change variable successfully with pass by reference
    int badBeat = -20;
    string instructions = "unchanged";
    cout << "enter song: ";
    getline(cin, song);
    
    //int test assigned to output of translate song function helped me to check what cases my program was failing at in
    int test;
    test = translateSong(song, instructions, badBeat);
    cout << "instructions: " << instructions << endl;
    cout << "badBeat: " << badBeat << endl;
    
    switch(test)
    {
        case 0:
            cout << "song is translatable, instructions changed, badbeat unchanged ";
            break;
        case 1:
            cout << "Not syntactically correct ";
            break;
        case 2:
            cout << "syntac. correct, but sustained note < 2, badBeat changed ";
            break;
        case 3:
            cout << "sustained note consisted of something other than /, badBeat changed ";
            break;
        case 4:
            cout << "song ends prematurely, missing /, badB = beats in string + 1 ";
            break;
        default:
            cout << "something else happend ";
    }//end of switch
    
    return 5; //to distinguish from perfect song
}




//FUNCTION DEFINITIONS

int translateSong(string song, string& instructions, int& badBeat)
{
    //local variables of function
    int totalNumBeats = 0; //equal to # of slashes in the song
    int currentBeat = 0; //while looping thru what beat I am currently on
    int digitValue = 0; //value of the single or double digit characters, stored as integers
    string translation = ""; //translating as I go, if perfect instructions = translation
    int pos; //NOT SURE WHY I DECLARED UP HERE BUT WORKS AFTER
    
    
    //I start with easiest way to check if song is not translatable and end with the hardest check, which is sustained note with double digit
    if(!hasCorrectSyntax(song))
        return 1;
    
    
    //if song is empty string, instructions = song
    if(song == "")
    {
        instructions = song;
        return 0;
    }
    
    //total number of slashes in song, used to calculate badBeat for return 4 premature end
    totalNumBeats = totalBeats(song);
    
  
    //confirmed syntactically correct and not empty, now looping thru to check translatability
    for(pos = 0; pos != song.size(); pos++)
    {
        
        
        bool is_Color = isColor(song[pos]); //set is_color identifier to the output of boolean isColor at current position in song
        
        if(song[pos] == '/') //simplist case, / gets translated, current beat updated, dont need to adjust position because for loop will
        {
            currentBeat++;
            translation = translation + 'x';
            continue;
        }
        
        if(is_Color && song[pos + 1] == '/') // color and / case, need to now update position here to account for 1 beat = 2 char
        {
            currentBeat++;
            translation = translation + (char)tolower(song[pos]); //tolower function only worked when i casted to char
            pos++;
            continue;
        }
        
        if(is_Color && isdigit(song[pos + 1]) && song[pos + 2] == '/' )//color digit / case, 1st check easiest way to return, which is digitvalue < 2
        {
            digitValue = (song[pos + 1] - '0');
            if(digitValue < 2)
            {
                badBeat = currentBeat + 1;
                return 2;
            }
            
           
            
            //now iterating thru to check if the sustained note is correct, single digit value matches slash count
            for(int s = 0; s < digitValue && s + pos + 2 < song.size(); s++) //prevents going out of bounds to evaluate
            {
                
              //first thing after color digit is guranteed to be a slash because syntactically correct
                if((song[pos + 2 + s]) == '/')
                {
                    currentBeat++;
                    translation = translation + (char)toupper(song[pos]);
                    continue; //not sure about this
                }
                //if its not a slash in sustained beat the only other thing it could be (based on syntactically correct) is a color
                else  if(isColor(song[pos + 2 + s]))
                {
                    badBeat = currentBeat + 1;
                    return 3;
                }
                
                    
                }//END OF FOR LOOP for slash count single digit position is still at color, exited once color in sustained note or if s (representing position starting at first slash) reached the length of digit value making it correct
            
            
            //in for loop above with s, part of the boolean condition was also if s + position in song + digit value <song.size()
            //so now below outside of the loop i check to see if the song ended prematurely
            if(pos + 1 + digitValue >= song.size()) //checking if premature end without actually evaluating the position because that would be undefined
            {
                badBeat = totalNumBeats + 1;
                return 4;
            }
            
            pos = pos + 1 + digitValue; //update position after color digit / loop and premature ending test passed
            
            
            } //end of color digit slash,  translated
        
        
        
        
        //DOUBLE DIGIT, this is exactly the same as above, except the position and s loop positions are adjusted to account for now 2 digits being next to color
        if(is_Color && isdigit(song[pos + 1]) && isdigit(song[pos + 2]))//color digit digit / case
        {
            digitValue = ((song[pos + 1] - '0') * 10 + (song[pos + 2] - '0')); //accounting for 2 digits for digitValue now
            if(digitValue < 2)
            {
                badBeat = currentBeat + 1;
                return 2;
            }
            
            
            for(int s = 0; s < digitValue && s + pos + 3 < song.size(); s++) //prevents going out of bounds to evaluate, (s + pos + 2) now changed to (s + pos + 3)
            {
                
                
                if((song[pos + 3 + s]) == '/')
                {
                    currentBeat++;
                    translation = translation + (char)toupper(song[pos]); //had to cast this to char
                    continue;
                }
                
                else  if(isColor(song[pos + 3 + s]))
                {
                    badBeat = currentBeat + 1;
                    return 3;
                }
                
                
            }//END OF FOR LOOP for slash count double digit position is still at color
            
            
            if(pos + 2 + digitValue >= song.size())
            {
                badBeat = totalNumBeats + 1;
                return 4;
            }
            
            pos = pos + 2 + digitValue; //update position after color double digit / loop
            
            
        } //end of color double digit slash,  translated
        
        
    }//end of for loop at top of function
    
    
    
    //out of for loop if no errors occured, setting the translation to instructions
    instructions = translation;
    return 0;
}//end of function





//to cout up all the beats (aka /'s) in a syntactically correct song
int totalBeats(string song)
{
    int count = 0;
    for(int i = 0; i != song.size(); i++)
    {
        if(song[i] == '/')
            count++;
    }
    return count;
    
}






//to see if alpha position is a color
bool isColor(char c)
{
    if (tolower(c) == 'g' || tolower(c) == 'r' || tolower(c) == 'y' || tolower(c) == 'b' || tolower(c) == 'o')
        return true;
    else
        return false;
    
}




//to check if correct syntax: empty || slash || color slash || color digit slash || color digit digit slash
bool hasCorrectSyntax(string song)
{
    if (song == "")
        return true; //zero beat is syntac correct
    for(int k = 0; k < song.size(); k++ )
    {
        if (song[k] == '/')
            continue;
        if (isalpha(song[k]))
        {
            if(isColor(song[k])) //if its a color
            {
                if(k == song.size() - 1) //color not followed by anything
                    return false;
                if(song[k + 1] != '/' && !isdigit(song[k + 1]) ) //color followed by something else
                    return false;
                if(song[k + 1] == '/') //if its / return to top of loop
                {
                    k++;
                    continue;
                }
                if(isdigit(song[k + 1])) //if its color digit...
                {
                    if(k + 1 == song.size() - 1) //if digit at end, false
                        return false;
                    if(song[k + 2] != '/' && !isdigit(song[k + 2])) //color digit not followed by slash or another digit
                        return false;
                    if(song[k + 2] == '/') //its color, digit, slash
                    {
                        k = k + 2;
                        continue;
                    }
                    if(isdigit(song[k + 2])) //color, digit, digit
                    {
                        if(k + 2 == song.size() - 1) //last digit end, false
                            return false;
                        if(song[k + 3] != '/') //if 2nd digit not followed by slash
                            return false;
                        if(song[k + 3] == '/') //color digit digit slash
                        {
                            k = k + 3;
                            continue;
                        }
                        
                    }
                }
                
            }
            
            else
                return false; //not a color
            
        }
        else
            return false; //not alpha
        
    }//end of for loop
    
    return true;
}// end of function

               
               
               

            
           
        
