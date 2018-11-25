//
//  main.cpp
//  P6
//
//  Created by Maria Palafox on 5/27/18.
//  Copyright © 2018 Maria Palafox. All rights reserved.
//
/*
 
 #include <iostream>
 using namespace std;
 
 
 int main()
 {
 int arr[3] = {5, 10, 15};
 
 const int MAX = 3;
 
 int* ptr = &arr[0]; //initializing pointer to beginning of array, func parameter declaration
 
 *ptr = 10; //dereferencing
 
 *(ptr + 1) = 20;
 
 *(ptr + 2) = 30; //pointer never moved
 
 ptr += MAX; //(index positions are 0-2)
 
 while(ptr > &arr[0]) //not >= because then out of bounds
 {
 ptr--;
 cout << ' ' << *ptr;
 }
 cout << endl;
 }

 
 
#include <iostream>
#include <cmath>
using namespace std;

(B)
void findDisorder(int arr[], int n, int*& p);


int main()
{
    int nums[6] = {10, 20, 20, 40, 30, 50};
    int* ptr;
    
    findDisorder(nums, 6, ptr);
    
    
    
    if (ptr == nullptr)
        cout << "The array is ordered" << endl;
    else
    {
        cout << "The disorder is at address " << ptr << endl;
        cout << "It's at position " << ptr - nums << endl;
        cout << "The item's value is " << *ptr << endl;
    }
}


    void findDisorder(int arr[], int n, int*& p)
    {
        for (int k = 1; k < n; k++)
        {
 
 
 // better to start at index 1 and check item preceding...index 0 doesnt have anything preceeding it...this way you dont have to do weird things to index (k < size is normal)
 //sizeof(nums)/sizeof(int) is the size of array 6.
 
            if (arr[k] < arr[k-1])
            {
              p = arr + k;  //&nums[[0+k]
                return;
            }
        }
        p = nullptr;
    }
 
(C)
#include <iostream>
#include <cmath>
using namespace std;

void hypotenuse(double leg1, double leg2, double* resultPtr)
{
    *resultPtr = sqrt(leg1*leg1 + leg2*leg2);
}

int main()
{
    double p;
    hypotenuse(1.5, 2.0, &p);
    cout << "The hypotenuse is " << p << endl;
}
 


//(D)
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

// return true if two C strings are equal
bool match(const char str1[], const char str2[])
{
    while (*str1 != '\0'  &&  *str2 != '\0')  // zero bytes at ends
    {
        if (*str1 != *str2)  // compare corresponding characters
            return false;
        
        str1++;            // advance to the next character
        str2++;
    }
    if(*str1 == *str2) //end at same time?
        return true;
    else
        return false;
    
}

int main()
{
    char a[10] = "Shankar";
    char b[10] = "Shweta";
    
    if (match(a,b))
        cout << "They're the same!\n";
    else
        cout << "They're NOT the same!\n";
}

 

 #include <iostream>
 using namespace std;
 
 int* computeSquares(int& n)
 {
 int arr[10];
 n = 10;
 for (int k = 0; k < n; k++)
 arr[k] = (k+1) * (k+1);
 //return arr; not like parameter of function, need to specify address
 int* ptr = &arr[0];
 return ptr;
 }
 
 void f()
 {
 int junk[100];
 for (int k = 0; k < 100; k++)
 junk[k] = 123400000 + k;
 }
 
 int main()
 {
 int m;
 int* ptr = computeSquares(m);
 f();
 for (int i = 0; i < m; i++)
 cout << *(ptr + i) << ' ';
 //cout << ptr[i] << ' ';
}

#include <iostream>
using namespace std;

int* computeSquares(int& n)
{
    int arr[10];
    n = 10;
    for (int k = 0; k < n; k++)
        arr[k] = (k+1) * (k+1);
    return arr;
    //int* ptr = &arr[0];
    //return ptr;
}

void f()
{
    int junk[100];
    for (int k = 0; k < 100; k++)
        junk[k] = 123400000 + k;
}

int main()
{
    int m;
    int* ptr = computeSquares(m);
    cout << ptr <<  endl;
    f();
    for (int i = 0; i < m; i++)
        cout << *(ptr + i) << ' ';
    //cout << ptr[i] << ' ';
}


#include <iostream>
using namespace std;
#include <string>

int main()
{
    string* fp;
    string fish[5];
    fp = fish + 4;
    *fp = "yellowtail";
    
    *(fish + 3) = "salmon";
    fp -= 3; //this moved the point to position [1]
    
    //*fp = "2";
    
    fp[1] = "loach"; //pointer still on proceeding position
    
    fp[0] = "eel"; //pointer on this position
    
    //fp--;
    
    //bool d = (fp == fish);
   //cout << "d = " << d << endl;
    
    bool b = (*fp == *(fp + 1));
    cout << "b = " << b << endl;
    
    //cout << fish;
    //test so far
    for(int k = 0; k < 5; k++)
        cout << fish[k] << " [] ";
    //worked so far
 
    
}


//3
//a

#include <iostream>
using namespace std;
#include <string>

double computeAverage(const double* scores, int nScores)
{
    double tot = 0;
    for(int i = 0; i < nScores; i++)
    {
        tot += *(scores + i);
    }
    return tot/nScores;
}

int main()
{
    double scores[3] = {10, 10, 30};
    double total = computeAverage(scores, 3);
    cout << total << endl;
}
 
 
 b
 


#include <iostream>
using namespace std;
#include <string>

// This function searches through str for the character chr.
// If the chr is found, it returns a pointer into str where
// the character was first found, otherwise nullptr (not found).

const char* findTheChar(const char* str, char chr)
{
   
    while(*str != 0)
    {
        if(*str == chr)
            return str;

        str++;
    }
    
    return nullptr;
}


int main()
{
    char chr = 'b';
    char str[] = "cabd";
    const char* ans = findTheChar(str, chr);
    
    cout << ans-str << endl;
}


#include <iostream>

using namespace std;

int* minimart(int* a, int* b)
{
    if (*a < *b)
        return a;
    else
        return b;
}

void swap1(int* a, int *b)
{
    int* temp = a;
    a = b;
    b = temp;
}

void swap2(int* a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int array[6] = { 5, 3, 4, 17, 22, 19 };
    
    int* ptr = minimart(array, &array[2]);
    ptr[1] = 9;
    ptr += 2;
    *ptr = -1;
    *(array+1) = 79;
    
    cout << "diff=" << &array[5] - ptr << endl;
    
    swap1(&array[0], &array[1]);
    swap2(array, &array[2]);
    
    for (int i = 0; i < 6; i++)
        cout << array[i] << endl;
}



#include <iostream>
using namespace std;

void deleteG(char* m)
{
    char* e; //new variable of pointer type
    while(*m != 0) //while not at end of string
    {
        if(*m == 'g' || *m == 'G') //if m value is a g
        {
            *m = *(m + 1); //set the value m points to, to the char value proceeding where m points
            for(e = m + 1; *e != 0; e++) //e initialized to point at position proceeding m, break out when e points to end, increment e position
                *e = *(e+1); //moving all the chars over one to delete the G or g char
        }
        
        m++; //after done looping with e pointer, update m pointer address to point to next element
    }
}

int main()
{
    char msg[100] = "I recall the glass gate next to Gus in Lagos, near the gold bridge.";
    deleteG(msg);
    cout << msg;  // prints   I recall the lass ate next to us in Laos, near the old bride.
}
  */

#include <iostream>
using namespace std;

int* computeSquares(int& n)
{
    int arr[10];
    n = 10;
    for (int k = 0; k < n; k++)
        arr[k] = (k+1) * (k+1);
    return arr;
}

void f()
{
    int junk[100];
    for (int k = 0; k < 100; k++)
        junk[k] = 123400000 + k;
}

int main()
{
    int m;
    int* ptr = computeSquares(m);
    f();
    for (int i = 0; i < m; i++)
        cout << ptr[i] << ' ';
}

