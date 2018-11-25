//
//  main.cpp
//  Project 1
//
//  Created by Maria Palafox on 4/6/18.
//  Copyright © 2018 Maria Palafox. All rights reserved.
//

// Code for Project 1
// Report poll results

#include <iostream>
using namespace std;   // pp. 38-39 in Savitch 6/e explains this line

int main()
{
    int numSurveyed; // creating integer
    int numApprove;
    int numDisapprove;
    
    cout << "How many people were surveyed? "; //outputs this onto screen
    cin >> numSurveyed; //inputing things from the screen, the box the spits out answers
    cout << "How many of them approve of the U.S. getting into a trade war with China? ";
    cin >> numApprove;
    cout << "How many of them disapprove of the U.S. getting into a trade war with China? ";
    cin >> numDisapprove;
    
    double pctApprove = 100.0 * numApprove / numSurveyed;  //make logic error here
    double pctDisapprove = 100.0 * numDisapprove / numSurveyed;
    
    cout.setf(ios::fixed);       // see pp. 32-33 in Savitch 6/e
    cout.precision(1); // says show 1 decimal
    
    cout << endl;
    cout << pctApprove << "% say they approve." << endl;
    cout << pctDisapprove << "% say they disapprove." << endl;
    
    if (numApprove > numDisapprove)
        cout << "More people approve than disapprove." << endl;
    else
        cout << "More people disapprove than approve." << endl;
    }
