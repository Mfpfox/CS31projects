// Project 4 Solution

#include <string>

using namespace std;

int tally(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    int count = 0;
    for (int k = 0; k < n; k++)
        if (a[k] == target)
            count++;
    return count;
}

int findMatch(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    for (int k = 0; k < n; k++)
        if (a[k] == target)
            return k;
    return -1;
    //if for loop not entered return -1 n = 0. nice style on bottom
}

bool findRun(const string a[], int n, string target, int& begin, int& end)
{
    int start = findMatch(a, n, target);
    if (start == -1)
        return false;
    begin = start;
    for (end = begin; end+1 < n && a[end+1] == a[begin]; end++)
        ;
    return true;
}

int positionOfMin(const string a[], int n)
{
    if (n <= 0)
        return -1;
    int minPos = 0;  //  assume to start that min is at position 0
    for (int k = 1; k < n; k++)
        if (a[k] < a[minPos])
            minPos = k;
    return minPos;
}

int moveToEnd(string a[], int n, int pos)
{
    if (n < 0  ||  pos < 0  ||  pos >= n)
        return -1;
    
    // save the element that is to be moved
    string toBeMoved = a[pos];
    
    // shift to the left those elements past the one to be moved
    for (int k = pos; k < n-1; k++)
        a[k] = a[k+1];
    
    // place the moved element at the end
    a[n-1] = toBeMoved;
    return pos;
}

int moveToBeginning(string a[], int n, int pos)
{
    if (n < 0  ||  pos < 0  ||  pos >= n)
        return -1;
    
    // save the element that is to be moved
    string toBeMoved = a[pos];
    
    // shift to the right those elements before the one to be moved
    for (int k = pos; k > 0; k--)
        a[k] = a[k-1];
    
    // place the moved element at the beginning
    a[0] = toBeMoved;
    return pos;
}

int findDifference(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0  ||  n2 < 0)
        return -1;
    
    // n = minimum of n1 and n2
    int n;
    if (n1 < n2)
        n = n1;
    else
        n = n2;
    
    // find first position of difference
    for (int k = 0; k < n; k++)
        if (a1[k] != a2[k])
            return k;
    
    // no difference
    return n;
}

int eliminateDups(string a[], int n)
{
    if (n < 0)
        return -1;
    if (n <= 1)
        return n;
    
    // Copy elements that aren't consecutive duplicates from the
    // "from" position to the "to" position in the array
    int to = 0;
    for (int from = 1; from < n; from++)
    {
        if (a[from] != a[to])
        {
            to++;
            a[to] = a[from];
        }
    }
    return to+1;
}

bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0  ||  n2 < 0)
        return false;
    
    // Walk through a1, marking off elements of a2 as we find them
    int k2 = 0;
    for (int k1 = 0; k1 < n1  &&  k2 < n2; k1++)
    {
        if (a1[k1] == a2[k2])
            k2++;
    }
    return k2 == n2; //can use an expression for return of bool type function
}

// Return true iff the elements of a are in nondecreasing order.

bool isOrdered(const string a[], int n)
{
    for (int k = 0; k < n-1; k++)
        if (a[k] > a[k+1])
            return false;
    return true;
}

int makeMerger(const string a1[], int n1, const string a2[], int n2,
               string result[], int max)
{
    if (n1 < 0  ||  n2 < 0  ||  n1+n2 > max  || !isOrdered(a1, n1)  ||
        !isOrdered(a2, n2))
        return -1;
    
    int k1 = 0;
    int k2 = 0;
    while (k1+k2 < n1+n2)
    {
        // If we've run out of a2 elements, use the next one from a1.
        // If we've run out of a1 elements, use the next one from a2.
        // Otherwise, if the next one from a1 is smaller, use it,
        //            otherwise the next one from a2.
        if (k2 == n2  ||  (k1 < n1  &&  a1[k1] < a2[k2]))
        {
            result[k1+k2] = a1[k1];
            k1++;
        }
        else
        {
            result[k1+k2] = a2[k2];
            k2++;
        }
    }
    return n1+n2;
}

void exchange(string& s1, string& s2)
{
    string t = s1;
    s1 = s2;
    s2 = t;
}

int separate(string a[], int n, string separator)
{
    if (n < 0)
        return -1;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstKnownGreater
    //  Every element at positions earlier than firstNotLess is < separator
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstKnownGreater-1 is not
    //     known yet
    //  Every element at position firstKnownGreater or later is > separator
    
    int firstNotLess = 0;
    int firstUnknown = 0;
    int firstKnownGreater = n;
    while (firstUnknown < firstKnownGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstKnownGreater--;
            exchange(a[firstUnknown], a[firstKnownGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
    return firstNotLess;
}
