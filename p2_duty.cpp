//
//  main.cpp
//  P2
//
//  Created by Maria Palafox on 4/16/18.
//  Copyright © 2018 Maria Palafox. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
int main()
{
    // added modifier to variable named constant numbers
    const double FIRST_CHUNK = 155;
    const double SECOND_CHUNKPM = 271;
    const double SECOND_CHUNK = 255;
    
    
    cout<< "Importer: ";
    string importerName;
    getline(cin,importerName);
    
    
    //error 1
    if (importerName == "")
    {
       cout<< "---"<<endl;
       cout<< "You must enter an importer."<<endl;
       return 0;
    }
    
    cout<< "Product value (in trillions): ";
    double productValue;
    cin >> productValue;
    cin.ignore(10000, '\n');
    
    cout.setf(ios::fixed);
    cout.precision(2);
    
    
    //error 2
    if (productValue < 0)
    {
        cout<< "---" << endl;
        cout << "The product value must not be negative." <<endl;
        return 0;
    }
    
    
    
    cout << "Product: ";
    string productName;
    getline(cin,productName);
    
    
    //error 3
    if (productName == "")
    {
       cout<< "---" << endl;
       cout<< "You must enter a product."<<endl;
        return 0;
    }
    
    //i avoided using the OR and != in the else-if statements to prevent the condition from always being true.  also I added in some constants to prevent messing up re typing the numbers.
    
    double duty;
    if (productValue <= 500)
        duty = productValue * 0.31;
    else if (productValue <= 900 && (productName == "pigs" || productName == "mud"))
        duty = 0.29*(productValue - 500) + FIRST_CHUNK;
    else if (productValue <= 900)
        duty = 0.25*(productValue - 500) + FIRST_CHUNK;
    else if (productValue > 900 && (productName == "pigs" || productName == "mud"))
        duty = 0.22*(productValue - 900) + SECOND_CHUNKPM;
    else
        duty = 0.22*(productValue - 900) + SECOND_CHUNK;
    
    cout<< "---" << endl;
    cout<< "The import duty for " << importerName << " is G" << duty<< " trillion."<< endl;
    
    
    
}
