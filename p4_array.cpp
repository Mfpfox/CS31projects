//#define NDEBUG
#include <cassert>
#include <string>
#include <cctype>
#include <iostream>
using namespace std;

//fuctions prototypes

int tally(const string a[], int n, string target);
//returns number of strings in array equal to the target
//precondition: n not negative, if n < 1 return -1

int findMatch(const string a[], int n, string target);
//returns POSITION of string in array that is equal to target, return smallest position
//returns -1 if n < 0 && if target not found

bool findRun(const string a[], int n, string target, int& begin, int& end);
//finds earliest occurrence in array of one or more consecutive strings == target, sets begin to the POSITION of occurrence and end to POSITION of last occurence, and returns true
//if n < 0 or no string in array == target, leave begin and end unchanged return false

int positionOfMin(const string a[], int n);
//returns POSITION of string in array such that that string is <= every string in array, more than one return smallest POSITION
//return -1 if array is empty

int moveToEnd(string a[], int n, int pos);
//extra credit no additional array
//eliminates item at POSITION  pos by copying all elements after it one place to left.  put item now in last position of array.
//returns the original POSITION of item moved to end

int moveToBeginning(string a[], int n, int pos);
//extra credit no additional array
//Eliminates item at POSITION pos by copying all elements before it one place to RIGHT. puts item eliminated into the first position of array a[0]
//returns original position of item that was moved to beginning

int findDifference(const string a1[], int n1, const string a2[], int n2);
//returns the POSTION of first corresponding elements of a1 and a2 that are NOT EQUAL.  n1 is interesting elements in a1. n2 interesting elements in a2.  If arrays are equal up to the point where one or both run out, return the smaller of n1 and n2

int eliminateDups(string a[], int n);
//extra credit no additional array
//eliminates duplicates, retains only one item of that sequence. returns retained items, which is the SIZE of retained items. a[0] - a[4] not duplicates returns 5, no longer care what strings are in a[5] and beyond...other strings moves to end
//if trying to move items in an empty array return -1

bool subsequence(const string a1[], int n1, const string a2[], int n2);
//if all n2 elements of a2 appear in a1, in same order though not neccessarily consecutively, return true.  return false if a1 does not contain a2 as subsequence.
//a sequence with no elements (empty array) is a subsequence of any sequence...true
//return false instead of -1 if passed any bad arguments


int findSub(const string a1[], int n1, string target, int start);
//this function is called in subsequence function.  if takes the updated index (one position after the last found element in a1 (matches a2)
//preconditions same as subsequence function
//if element not found returns -1
//if found returns the position of found element in a1


int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max);
//extra credit no additional array
//if a1 has n1 elements in increasing order, and a2 has n2 elements in increasing order, place in results all the elements of a1 and a2, arranged in nondecreasing order, and return number of elements so placed!!
//return -1 if result would have more than max elements or if a1 and/or a2 are not in nondecreasing order (meaning item before not GREATER THAN item following)
//??all the elements or the elements with regard to n1 and n2

bool nondecreasing(const string a[], int n);
//same preconditions of makeMerger.  only called in makeMerger
//returns true if given string in nondecreasing order, else false
//returns true for n == 0

void fillArray(const string a1[], int n1, const string a2[], int n2, string result[]);
//same preconditions of makeMerger.  only called in makeMerger
//fills result with elements of n1 and n2
//if n1 or n2 == 0, 0 elements added

void arrange(string result[], int n);
//same preconditions of makeMerger.  only called in makeMerger
//arranges elements in result to be in nondecreasing order


int positionMin(const string a[], int n, int start);
//same preconditions of makeMerger.  only called in makeMerger
//takes start index and assigns variable min to that position, if it finds a position with variable less than min, it returns position of the variable that is less than variable at start index



int separate(string a[], int n, string separator);
//extra credit no additional array
//rearrange the elements of the array so that all the elements whose value is < separator come before all the other elements, and all the elements whose value is > seperator come after all the other elements.  return the POSITION of first element that, after the rearrangement, is not < separator, so could return item = to separator, or n if there are none

int findEdge(const string a[], int n, string target);
//same preconditions as separate, only called in separate
//finds the first element in array that is greater than or equal to targer
//if all elements are less than target, returns size of array
//if array size is 0 returns -1






int main()
{
   //testing tally function
    string h[10] = {"romanoff", "thor", "rogers", "banner", "", "parker", "rogers", "Thor", "Rogers", "Banner"};
    assert(tally(h, 7, "rogers") == 2);
    assert(tally(h, 0, "") == 0); //0 because 0 items to search
    assert(tally(h, 10, "Banner") == 1);
    assert(tally(h, 2, "rogers") == 0); //test is size works
    assert(tally(h, 10, "Maria") == 0);
    assert(tally(h, 10, "THor") == 0);
    assert(tally(h, 1, "romanoff") == 1);
    assert(tally(h, -1, "romanoff") == -1);//testing precondition
    
    //testing findMatch
    string f[10] = {"bun bun", "Bun Bun", "bun", "bun", "maria f", "mariA f", "bUn", "", "mAria", "maria F"};
    string so[11]; //testing what happens when base type string array not initialized = automatically empty string at index variables
    assert(findMatch(so, 11, "") == 0);
    assert(findMatch(so, 11, " ") == -1); //testing not found returns -1
    assert(findMatch(so, 0, "") == -1);
    //no initializers automatically the empty string
    assert(findMatch(f, 10, "bun") == 2); //testing if multiple matches, returns earliest position
    assert(findMatch(f, 10, "Bun Bun") == 1);
    assert(findMatch(f, 1, "bun bun") == 0); //testing size
    assert(findMatch(f, 4, "maria f") == -1); //not found
    assert(findMatch(f, 8, "") == 7); //testing size
    assert(findMatch(f, 8, "will") == -1);
    assert(findMatch(f, -8, "") == -1); //testing precondition that size not be negative
  
    cout << "******testing findRun, bg en start at -1 *************" << endl;
    int bg = -5; //initilizing so that I can notice if they change
    int en = -5;
    
    string g[11] = {"star", "star", "Star", "triangle", "triangE", "circle", "circle", "circle","cir", "", "" };
    
    string s[11]; //testing uninitialized array size 11
    
    //testing false cases
    bool b0 = findRun(s, 11, "n", bg, en);  //no change in bg and en because n not found
    cout << "b0 = " << b0 << "  begin = " << bg << "  end = " <<  en << endl;
    //also tested with above bool b0 if s[11] with no initializers is automatically set to empty string elements.  yes, begin is 0 and end is 10.
    
    bool b1 = findRun(g, -2, "Star", bg, en); //bad argument
    cout << b1 << bg << en << endl;
    bool b2 = findRun(g, 8, "Circle", bg, en); //capital C not found
    cout << b2 << bg << en << endl;
    bool b3 = findRun(g, 0, "circle", bg, en); //testing searching 0 elements
    cout << b3 << bg << en << endl;
    
    //testing true cases, bg and en now should change to position of start and end of run
    assert(findRun(g, 8, "star", bg, en) && bg == 0 && en == 1); //two of target in position 0 and 1
    assert(findRun(g, 3, "Star", bg, en) && bg == 2 && en == 2); //testing run size of 1 element
    assert(findRun(g, 8, "circle", bg, en) && bg == 5 && en == 7);
    assert(findRun(g, 7, "circle", bg, en) && bg == 5 && en == 6); //recongnizes SIZE as n
    assert(findRun(g, 11, "circle", bg, en) && bg == 5 && en == 7); //testing run of 3 elements
    assert(findRun(g, 11, "cir", bg, en) && bg == 8 && en == 8); //testing run size of 1 element
    assert(findRun(g, 11, "", bg, en) && bg == 9 && en == 10); //handles end cases
    
    
    //testing positionOfMin
    string m[12] = {"bAt", "bat", "pple", "pple", "Cat", "apple", "Dog", "sad", "hello", "hell", "appl", "Bpp"};
    string ma[3]; //testing case of uninitialized array
    int test = (positionOfMin(m, 12));
    cout << "position of min = " << test << endl;
    string result = m[test];
    cout << "min result = " << result << endl;
    int test2 = (positionOfMin(ma, 3));
    cout << "position of min in uninitialized array is = " << test2 << endl;
    string mb[12] = {"hello", "hella", "hella", "pple", "Cat", "apple", "Dog", "sad", "Applesauce", "App", "", "A"};
    assert(positionOfMin(mb, 5) == 4); //testing capital come first
    assert(positionOfMin(mb, 3) == 1);//testing if 2 equal, returns smallest position
    assert(positionOfMin(mb, 7) == 4);
    assert(positionOfMin(mb, 12) == 10); //empty string is before all other cases as minimum
    assert(positionOfMin(mb, 0) == -1); //spec specification, 0 elements
    assert(positionOfMin(mb, -1) == -1); //bad argument
    
    //TESTING moveToEnd
    string move[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    //int j = moveToEnd(move, 10, 0); //moves pos 0 to the end
    //cout << "Position of string moved is: " << j << endl;
  //  for(int i = 0; i < 10; i++)
    //    cout << move[i] << ", ";
   // cout << endl;
    
    //had to comment out asserts unless testing because function changes array
    
    //assert(moveToEnd(move, 10, 0) == 0 && move[0] == "b" && move[9] == "a"); //moved first position to last
    //assert(moveToEnd(move, 3, 3) == -1); //undefined position, returns -1
    //assert(moveToEnd(move, 5, 1) == 1 && move[1] == "c" && move[4] == "b"); //testing size
    //assert(moveToEnd(move, 2, 1) == 1 && move[1] == "b" && move[0] == "a"); //handles case where position to be moved is already at the end of declared size
    
    //assert(moveToEnd(move, 7, 5) == 5 && move[5] == "g" && move[6] == "f"); //handles moving one element left case
    
     //Testing moveToBeginning
     cout << "****** moveToBeginning *************" << endl;
    //just like in moveToEnd, testing what happens when pos is already at beginning, if it recognizes size, if it handles end cases, middle move cases, and pos 1 move cases, also if error size = 0
    string mave[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    int j = moveToBeginning(mave, 0, 1);
    cout << "Position of string moved is: " << j << endl;
    for(int i = 0; i < 10; i++)
        cout << mave[i] << ", ";
   cout << endl;
    
    
    
    //Testing findDifference
    //int findDifference(const string a1[], int n1, const string a2[], int n2)
    string a1[10] = {"bAt", "bat", "pple", "pple", "Cat", "apple", "Dog", "Sad", "hello", "hell"};
    string a2[10] = {"bAt", "bat", "pple", "pple", "Cat", "apple", "Dog", "sad", "hello", "hell"};
    //tested size, equal until on array runs out, equal entirely, difference at position 0, difference at last position of one array
    //assert(findDifference(a1,10, a2, 10) == 2); //change a2 "ppe"
    //assert(findDifference(a1,10, a2, 5) == 5); //no differences just n2 runs out
    //assert(findDifference(a1,10, a2, 10) == 0); //changed a2[0] "At"
    //assert(findDifference(a1,5, a2, 5) == 4); //changed cat to at
   //assert(findDifference(a1,10, a2, 10) == 7); //changed sad to Sad
   assert(findDifference(a1,0, a2, 10) == -1); //error because cant compare two positions if size of one array is declared 0
    assert(findDifference(a1,10, a2, -1) == -1); //testing bad argument
    string a3[10] = {"bAt", "bat", "pple", "pple", "cat", "apple", "Dog", "Sad", "hello", "hell"};
    string a4[5] = {"bAt", "bat", "pple", "pple", "cat"};
    //assert(findDifference(a3, 10, a4, 10) == 0); //bat
    assert(findDifference(a3, 10, a4, 5) == 5); //returns smaller n
    
    
    
    
    //TESTING eliminateDups
    //int eliminateDups(string a[], int n)
    //checked precondition that n is not < = 0, bad arguments
    cout << "***********eliminateDups********************" << endl;
    string dup[10] = {"aa", "aa", "aa", "a", "e", "aa", "aa", "afa", "aa", "afa"};
    //tested 4 replicates at end to see how handles end of declared size cases
    //tested size of array 1, returned 1
    //tested replicated at beginning
    
    int dups = eliminateDups(dup, 10);
    cout << "Retained size is: " << dups << endl;
    for(int i = 0; i < 10; i++) //printed the original declared size to see how elements shift
        cout << dup[i] << ", ";
    cout << endl;
    
    cout << "*******************************" << endl;
    
    
    
    
    //TESTING bool subsequence
    cout << "**********bool subsequence*********************" << endl;
    string a15[12] = {"will", "thor", "stark", "thor", "maria", "bun", "h", "thor", "ban"};
   string a25[9] = {"thor", "bun", "thor", "maria", "h"};
    bool sub;
    sub = subsequence(a15, 12, a25, 4);
    if(sub)
        cout << "a2 IS a subsequence of a1" << endl;
    else
        cout << "a2 is NOT a subsequence of a1" << endl;
    
    
    
    //TESTING makeMerger
    cout << "*******MERGER***************" << endl;
    string a5[9] = {"a", "a", "b", "c", "d", "e", "f", "g", "h"};
    string a6[4] = {"A", "B", "C", "D"};
    const int MAX = 10000;
    string z[MAX];
    int merger = makeMerger(a5, 9, a6, 4, z, MAX);
    cout << "return value: " << merger << endl;
    for(int i = 0; i < merger; i++)
        cout << z[i] << " , ";
    cout << endl;
    
     cout << "*******SEPERATOR***************" << endl;
     //int separate(string a[], int n, string separator);
    string separator = "thor";
    string a7[6] = {"rhodes", "banner", "stark", "parker", "thor", "rogers"};
    int seperate_pos = separate(a7, 6, separator);
    cout << "return value: " << seperate_pos << endl;
    for(int i = 0; i < 6; i++)
        cout << a7[i] << " , ";
    cout << endl;
    
    
    cout << "all test passed" << endl;
    return 0;
}



//function definitions



//returns number of strings in array equal to the target
//precondition: n not negative, if n < 1 return -1
int tally(const string a[], int n, string target)
{
   if (n < 0)
       return -1;
    if(n == 0)
        return 0;
    int counter = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] == target)
            counter++;
    }
    return counter;
}


//returns POSITION of string in array that is equal to target, return smallest position
//returns -1 if n < 0 && if target not found
int findMatch(const string a[], int n, string target)
{
    if (n <= 0)
        return -1; //include zero for target not found because zero things searched
    int i;
    for(i = 0; i < n; i++)
    {
        if(a[i] == target)
        {
            return i;
        }
        
    }
    return -1; //exit loop without returning
}//end of findMatch




//finds earliest occurrence in array of one or more consecutive strings == target, sets begin to the POSITION of occurrence and end to POSITION of last occurence, and returns true
//if n < 0 or no string in array == target, leave begin and end unchanged return false
bool findRun(const string a[], int n, string target, int& begin, int& end)
{
    if(n < 0)
        return false;
    const int SIZE = n;
    int index;
    bool found = false;
    for(index = 0; index < SIZE; index++)
    {
        if(a[index] != target)
            continue;
        else
        {
            found = true;
            begin = index;
            end = index;
            while(index != SIZE - 1)
            {
                if(a[index + 1] != target)
                    return found;
                else
                {
                    index++;
                    end = index;
                    continue;
                }
            }
            return found;
            
        }//end of else
        
        
        
        
    } //end of outter for loop
    return found;
}//end of findRun



//returns POSITION of string in array such that that string is <= every string in array, more than one return smallest POSITION
//return -1 if array is empty
int positionOfMin(const string a[], int n)
{
    if(n <= 0)
        return -1;
    const int SIZE = n;
    int index = 0, indexOfMin = 0;
    string min = a[index];
    for(int i = index + 1; i < SIZE; i++)
    {
        if(a[i] < min)
        {
            min = a[i];
            indexOfMin = i;
        }
    }
    return indexOfMin;
    
}

//extra credit no additional array
//eliminates item at POSITION  pos by copying all elements after it one place to left.  put item now in last position of array.
//returns the original POSITION of item moved to end
//assumes size is not less or equal to 0 (undefined before to move elements in array with none)
int moveToEnd(string a[], int n, int pos)
{
    const int SIZE = n;
    const int POS = pos;
    const int LASTPOS = SIZE - 1;
    
    if(SIZE <= 0 || POS >= SIZE || POS < 0) //cant look at position of an empty array
        return -1;
    const string moving = a[POS];
    if(POS == LASTPOS) //already at end
        return POS;
    for(int index = POS; index < LASTPOS; index++)
        a[index] = a[index + 1]; //shift all things in front of pos left
    a[LASTPOS] = moving; //assign variable eliminated to last position
    return POS;
}


//extra credit no additional array
//Eliminates item at POSITION pos by copying all elements before it one place to RIGHT. puts item eliminated into the first position of array a[0]
//returns original position of item that was moved to beginning
int moveToBeginning(string a[], int n, int pos)
{
    const int SIZE = n;
    const int POS = pos;
    const int FIRSTPOS = 0;
    
    if(SIZE <= 0 || POS >= SIZE || POS < 0) //cant look at position of an empty array
        return -1;
    const string moving = a[POS];
    if(POS == 0) //already at beginning
        return POS;
    for(int index = POS; index > 0; index--)
        a[index] = a[index - 1]; //shift all elements behind one to be moved to the right to eliminate
    a[FIRSTPOS] = moving; //set varaible to the beginning position
    return POS;
}



//returns the POSTION of first corresponding elements of a1 and a2 that are NOT EQUAL.  n1 is interesting elements in a1. n2 interesting elements in a2.  If arrays are equal up to the point where one or both run out, return the smaller of n1 and n2
int findDifference(const string a1[], int n1, const string a2[], int n2)
{
    const int N1 = n1;
    const int N2 = n2;
    
    if(N1 < 0 || N2 < 0)
        return -1;

    if(N1 == 0 || N2 == 0)
        return -1; // because cant compare elements if one doesnt have elements
    
    int index = 0;
    while(index < N1 && index < N2)
    {
        if(a1[index] == a2[index])
            index++;
        else
            return index;
    }//either left loop because found difference or index = size
    
    
    if(N1 < N2)
        return N1;
    else //n2 <= n1
        return N2;
    
}




//extra credit no additional array
//eliminates duplicates, retains only one item of that sequence. returns retained items, which is the SIZE of retained items. a[0] - a[4] not duplicates returns 5, no longer care what strings are in a[5] and beyond...other strings moves to end
//if trying to move items in an empty array return -1
int eliminateDups(string a[], int n)
{
    if(n <= 0)
        return -1; //test bad arguments
    
    const int SIZE = n;
    int retain = SIZE; //new variable that will change with each elimination of duplicate
    for(int i = 0; i < retain - 1; i++) //condition is retain size - 1 because next you check position + 1 (so cant be at end of array)
    {
        if(a[i] == a[i + 1]) //if there is a duplicate, i remains on position, i + 1 is eliminated
        {
           if((i + 1) == (retain - 1)) //if duplicate at the end like abcc
           {
               retain--;
               return retain;
           }
           
            for(int j = i + 1; j < retain - 1; j++)
            {
                a[j] = a[j + 1];
            }
            retain--; //for each loop iteration, retain size decreases
            //a b b c d
            //  i j
            
        }//end of comparing neighbor
        
        //a b b (b) c d
        //  i j
        //a b b c d
        //a i j ...have to set i back again in case of replicates consisting of 3 or more elements
        if (a[i] == a[i + 1]) //if there is more than 1 replicate, set i back and loop will update forward again
        {
            i--;
        }
    } //end for loop
    return retain;
}


//if all n2 elements of a2 appear in a1, in same order though not neccessarily consecutively, return true.  return false if a1 does not contain a2 as subsequence.
//a sequence with no elements (empty array) is a subsequence of any sequence...true
//return false instead of -1 if passed any bad arguments
bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0 || n1 == 0)
        return false;
    if(n2 == 0)
        return true;
    if(n2 > n1)
        return false;
    
    int SIZE1 = n1;
    int SIZE2 = n2;
    
    
    
    int start = 0;
    string target;
    int found;
    
    for(int index2 = 0; index2 < SIZE2; index2++) //looping thru interesting elements in a2
    {
        target = a2[index2]; //assign target to elements of a2, and search for them in order in a1
        found = findSub(a1, SIZE1, target, start); //takes array 1, size, target (element of a2) and start index (initialized to 0)
        if(found < 0) //means that target not found in a1
            return false;
        start = found + 1; //the next starting position for findSub is one after the position it just returned, this maintains that a2 elements are in order in a1 if found
        
    }
    
    return true;//if exited loop, you completed looping thru a2 elements and they were all present in order in a1
}

int findSub(const string a1[], int n1, string target, int start)
{
    int i;
    for(i = start; i < n1; i++) //index starts at 0 or, if found a2 in a1, right after the position of found variable
    {
        if(a1[i] == target)
        {
            return i;
        }
        
    }
    return -1; //exit loop without returning
}





//extra credit no additional array
//if a1 has n1 elements in nondecreasing order, and a2 has n2 elements in nondecreasing order, place in results all the elements of a1 and a2, arranged in nondecreasing order, and return number of elements so placed!!
//return -1 if result would have more than max elements or if a1 and/or a2 are not in nondecreasing order (meaning item before not GREATER THAN item following)

int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
    const int SIZE1 = n1;
    const int SIZE2 = n2;
    const int MAX = max; //max declared in main as 10000
    const int COMBOSIZE = SIZE1 + SIZE2;
    if(SIZE1 < 0 || SIZE2 < 0) //bad arguments
        return -1;
    
    bool A1 = nondecreasing(a1, SIZE1);
    bool A2 = nondecreasing(a2, SIZE2);
    if(!A1) //if a1 not nondecreasing return -1...!false = true
        return -1;
    if(!A2) ////if a2 not nondecreasing return -1
        return -1;
    
    if(COMBOSIZE > MAX) //bad argument elements wont fit in results array
        return -1;
    
    fillArray(a1, SIZE1, a2, SIZE2, result);
    arrange(result, COMBOSIZE);
    
    
    return (COMBOSIZE);
}

bool nondecreasing(const string a[], int n)
{
  if(n == 0)
      return true; //0 elements, doesnt mean they are in nondecreasing order...so true
    else
    {
        int index = 0;
        while(index < (n - 1)) //index never reaches last position
        {
            if(a[index] > a[index +1]) //if it violates that before <= after
                return false;
            else
                index++;
        }
        
        return true; //done checking array
    }
}


void fillArray(const string a1[], int n1, const string a2[], int n2, string result[])
{
    int index = 0;
    while(index < n1) //doesnt do anything if size is 0
    {
        result[index] = a1[index]; //fill all elements of a1 into result
        index++; //will exit loop with index = size
    }
    int index2 = index; //continue at position = array 1 size
    int i = 0;
    while(i < n2)
    {
        result[index2] = a2[i]; //continues filling elements from a2 in result at end of a1 elements
        index2++;
        i++;
    }
    
    return;
}

void arrange(string result[], int n) //n is combosize of n1 + n2 of array 1 and 2 added to result
{
    int posmin_index;
    for(int index = 0; index < n -1; index++)
    {
        posmin_index = positionMin(result, n, index);
        string hold;
        //swapping so that next min value is at current index, then advance index and check from that point on if there is a value less than or equal to it.
        hold = result[index];
        result[index] = result[posmin_index]; //assinging current position to string with next minimum value
        result[posmin_index] = hold; //swaps the string that use to be at current position to the position where the posmin was
        
    }
    
}


int positionMin(const string a[], int n, int start)
{
    const int SIZE = n;
    int indexOfMin = start;
    string min = a[start]; //set min to position you are on
    for(int i = start + 1; i < SIZE; i++) //start on the position after start, and loop till at end of combined size (elements in result from a1 and a2)
    {
        if(a[i] < min) //if position before(min) > position after, else min <= next position
        {
            min = a[i];
            indexOfMin = i;
        }
    }
    return indexOfMin; //returns index of next min found starting from start index to end size (combosize) of result
    
}




//extra credit no additional array
//rearrange the elements of the array so that all the elements whose value is < separator come before all the other elements, and all the elements whose value is > seperator come after all the other elements.  return the POSITION of first element that, after the rearrangement, is not < separator, so could return item = to separator, or n if there are none
int separate(string a[], int n, string separator)
{
    if(n <= 0)
        return -1; //cant rearrange elements of empty array
    
    int moveCount = 0; //if all elements are greater than seperator, moveCount prevents infinite loop, say string is xyz and seperator is b, you will only move thru this string 3 times, equal to its size because at that point you have check all the positions
    for(int i = 0; i < n; i++)
    {
        if(a[i] >= separator)
        {
            moveToEnd(a, n, i);
            moveCount++; //prevents infinite loop
            if(moveCount == n)
                break;
            i--; //will be updated at for loop, corrects for move count changing the string at the position you were at, all elements shifting left
        }
      
    }
    int edge = findEdge(a, n, separator); //returns position of element after rearrangement that is >= to separator, or
    
    return edge; //this will either be position of first element that is >= separator, or if there are none the size of array
    
}

int findEdge(const string a[], int n, string target)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(a[i] >= target) //finds first element >= to separator
        {
            return i;
        }
        
    }
    return n; //exit loop, returns size because no element in array is >= to target, they must all be less than target
}//end of findMatch



