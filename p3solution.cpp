//  Project 3:  Heroic Grazblatnik

#include <string>

using namespace std;

const char END_OF_BEAT = '/';

//*************************************
//  hasCorrectSyntax
//*************************************

bool hasCorrectSyntax(string song)
{
    // An empty song is syntactically correct.
    
    if (song.size() == 0)
        return true;
    
    // A non-empty song must end with an end-of-beat marker.
    
    if (song[song.size()-1] != END_OF_BEAT)
        return false;
    
    // At this point, we know the song ends properly, so in the following
    // loop, we do not have to worry about, say, there not being a character
    // following a digit.
    
    // Each iteration of the loop recognizes one beat.
    //decouples type from the job (looping thru string
    //size_t is the type used to represent sizes (as its names implie//). Its platform (and even potentially implementation) dependent, //and should be used only for this purpose.
    An int is signed by default, and even though its size is also platform dependant, it will be a fixed 32bits on most modern machine (and though size_t is 64 bits on 64-bits architecture, int remain 32bits long on those architectures).
    
    
    size_t k = 0;
    while (k != song.size())
    {
        // The beat might have no note.
        
        if (song[k] == END_OF_BEAT)
        {
            k++;
            continue;
        }
        
        // Verify color letter.
        
        char color = tolower(song[k]);
        if (color != 'g'  &&  color != 'r'  &&  color != 'y'  &&
            color != 'b'  &&  color != 'o')
            return false;
        k++;
        
        // There might be a digit.
        //second digit nested in first if
        
        if (isdigit(song[k]))
        {
            k++;
            
            // There might be a second digit.
            
            if (isdigit(song[k]))
                k++;
        }
        
        // Verify end of beat.
        
        if (song[k] != END_OF_BEAT)
            return false;
        k++;
    }
    
    // We get here if we got through the song without a problem.
    
    return true;
    
}

//*************************************
//  translateSong
//*************************************

int translateSong(string song, string& instructions, int& badBeat)
{
    // Define return values
    
    const int RET_OK                    = 0;
    const int RET_NOT_WELL_FORMED       = 1;
    const int RET_BAD_SUSTAINED_LENGTH  = 2;
    const int RET_SUSTAINED_INTERRUPTED = 3;
    const int RET_PREMATURE_END         = 4;
    
    // A song that is not syntactically correct is not translatable.
    
    if (!hasCorrectSyntax(song))
        return RET_NOT_WELL_FORMED;
    
    // We will build the translation in the string named result, and
    // modify the instructions parameter only if the entire translation
    // succeeds.
    
    string result;
    
    int sustainedRemaining = 0;
    
    // How many beats left in the current
    // sustained note
    
    char sustainedColor;
    
    // Color of the current sustained
    // note (upper case)
    
    // Each iteration of the loop translates one beat.
    
    int beatNumber;
    size_t k = 0;
    for (beatNumber = 1; k != song.size(); beatNumber++)
    {
        // A beat with no note is either a beat with no required action or
        // a continuation of a sustained note.
        
        if (song[k] == END_OF_BEAT)
        {
            if (sustainedRemaining == 0)
                result += 'x';
            else
            {
                // Continue current sustained note
                result += sustainedColor;
                sustainedRemaining--;
            }
            k++;
            continue;
        }
        
        // The beat is not empty if we get here, so a sustained note had
        // better not still be in effect.
        
        if (sustainedRemaining > 0)
        {
            badBeat = beatNumber;
            return RET_SUSTAINED_INTERRUPTED;
        }
        
        // Since we know the song is syntactically correct, we know that
        // song[k] is a valid color.  Record it and advance past the color.
        
        char color = tolower(song[k]);
        k++;
        
        // If there's a digit, this beat specifies a sustained note.
        // Determine the sustained note length.
        
        if (isdigit(song[k]))
        {
            sustainedRemaining = song[k] - '0';
            k++;
            if (isdigit(song[k]))
            {
                sustainedRemaining = 10 * sustainedRemaining + song[k] - '0';
                k++;
            }
            
            // The sustained note length can't be < 2.
            if (sustainedRemaining < 2)
            {
                badBeat = beatNumber;
                return RET_BAD_SUSTAINED_LENGTH;
            }
            
            // Record the sustained note color and translate this first beat
            // of the sustained note.
            sustainedColor = toupper(color);
            result += sustainedColor;
            sustainedRemaining--;
        }
        else  // Not a sustained note, so translate normal note.
        {
            result += tolower(color);
        }
        
        // Advance past the end-of-beat marker.
        
        k++;
    }
    
    // We've finished the song, so no sustained note should still be
    // in effect.
    
    if (sustainedRemaining > 0)
    {
        badBeat = beatNumber;
        return RET_PREMATURE_END;
    }
    // We've successfully translated the entire song, so set instructions.
    
    instructions = result;
    
    return RET_OK;
}
