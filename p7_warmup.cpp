//
//  main.cpp
//  P7
//
//  Created by Maria Palafox on 5/31/18.
//  Copyright © 2018 Maria Palafox. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

//class declar; (struct same but default is public) public and private members (variables or functions)
class Pet
{
public: //methods-FUNCTIONS INSIDE CLASS
    Pet(string nm, int initialHealth); //constructor
    void eat(int amt);
    void play();
    string name() const; //doesnt change anything about
    int health() const;
    bool alive();
private: //cant access outside of class
    string m_name;
    int m_health;
};

// Initialize the members of class type Pet, declared in the declaration of class.
Pet::Pet(string nm, int initialHealth)
{
    m_name = nm;
    m_health = initialHealth;
}

void Pet::eat(int amt)
{
    m_health += amt;
    return;
}

void Pet::play()
{
    // TODO: Decrease pet's health by 1 for the energy consumed
    m_health -= 1;
}

string Pet::name() const
{
    // TODO: Return the pet's name.  Delete the following line and
    // replace it with the correct code.
    
    return m_name;
}

int Pet::health() const
{
    // TODO: Return the pet's current health level.  Delete the
    // following line and replace it with the correct code.
    return m_health;
}

bool Pet::alive()
{
    // TODO: Return whether pet is alive.  (A pet is alive if
    // its health is greater than zero.)  Delete the following
    // line and replace it with the correct code.
    return(m_health > 0);
    
    
}

/////////
// Do not change any code below this point
/////////

void reportStatus(const Pet* p)
{
    cout << p->name() << " has health level " << p->health();
    if ( ! p->alive())
        cout << ", so has died";
    cout << endl;
}

void careFor(Pet* p, int d)
{
    if ( ! p->alive())
    {
        cout << p->name() << " is still dead" << endl;
        return;
    }
    
    // Every third day, you forget to feed your pet
    if (d % 3 == 0)
        cout << "You forgot to feed " << p->name() << endl;
    else
    {
        p->eat(1);  // Feed the pet one unit of food
        cout << "You fed " << p->name() << endl;
    }
    
    p->play();
    reportStatus(p);
}

int main()
{
    Pet* myPets[2]; //DURING POINTER DECLARATION:go right if you can, go left if you must..."mypet is an array of 2, array stores pointers of type pet."
    
    myPets[0] = new Pet("Fluffy",2); //initialize array of pointers, new returns address
    myPets[1] = new Pet("Frisky", 4);
    for (int day = 1; day <= 9; day++)
    {
        cout << "======= Day " << day << endl;
        for (int k = 0; k < 2; k++)
            careFor(myPets[k], day);
    }
    cout << "=======" << endl;
    for (int k = 0; k < 2; k++)
    {
        if (myPets[k]->alive())
            cout << "Animal Control has come to rescue "
            << myPets[k]->name() << endl;
        delete myPets[k];
    }
}

/*
Try declaring the health member function private instead of public, and make sure you understand the resulting compilation error.
 =if int health() const is in private... you cant access it in the main function
 
 
Comment out the entire implementation of Pet::eat, all the way from the void Pet::eat(int amt) to its close curly brace. Make sure you understand the resulting build error.

 
 
In main, try replacing myPets[0] = new Pet("Fluffy", 2); with myPets[0] = new Pet("Fluffy"); or myPets[0] = new Pet;, and make sure you understand the resulting compilation error.
 =you could make a constructor to fit only a name argument
 =for default you can declare the default as new pet; or new pet();
 can have many different constructors...one will have to be default with no parameters
 
 
Try removing the const from the implementation, but not the declaration of the alive member function. Notice the compilation error.
 
 
Try removing the const from both the declaration and the implementation of the alive member function. Make sure you understand why the use of that function doesn't compile in reportStatus, but does compile in careFor and main.

 
 *******if you dont have const at end of function, and you pass a pointer that is suppose to point at a const object...its considered by compiler that you have potential to change the object its an error....keep everything const within const
CS 31 THERE WILL NOT BE A CONSTANT POINTER...SO IF CONFUSED KNOW ITS THE OBJECT IT POINTS TOO THAT IS CONSTANT.
*/
