//
//  Classes class.cpp
//  P7
//
//  Created by Maria Palafox on 6/4/18.
//  Copyright © 2018 Maria Palafox. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
/*
no memory until object created with that class as type= initialize objects (new)
 
 two ways to return class person:
 
 pass by reference for small or large:
const Person& older2(const person &a, const person &b)
 {
 if(a.getAge() > b.getApge()) ....
 }
 
 const is optional is making a copy.
 
 -dont pass by reference to local object, the local objects destructor called with function terminates
  not existing out of scope.. just return the object passed itself or pointer to object
 
 RETURNING A POINTER TO AN OBJECT:
 bob.intro() calls object of class . member
 if it were a pointer
 bob -> intro()
 ****2 ways to return...
 
[DELETE]
 delete: deletes object the pointer points too....so
 person *teen = makePerson2("al", 19);
 teen-> intro();
 delete teen; //oject deleted
 (teen = nullptr;)
 
 teen = makePerson1(...) //this is legal because pointer not deleted yet
 //delete again;//pointer deleted..this is really baD!!!!
 
 
 [on test # of new == # of deletes, set teen to nullptr when you delete object that teen points to]
 
 HOW NEW WORKS
 person *a = makePerson2("a1", 17);
 when dynamically allocating with new, memory in heap reserved...
 
 [IF IN CLASS YOU HAVE DYNAMICALLY ALLOCATED ARRAY], you would have to use destructor to delete all objects in array.
    for loop to go thru and delete
 */

// class Class{
// public:
//     Class(string name) {
//         enrollment = 0;
// }
//     bool addStudent(string name, int age)
//     {
//    Students[enrollment] = new Person(name, age);
//         //Students is an array of pointers initializes to Person object (dynamic)
//    enrollment++;
//    return true;
//     }
//     ~Class()
//     {
//         for(int i = 0; i < enrollment; i++)
//             delete students[i];
//     } //delete every student allocated dynamically...with new...
//     
//private:
//     Person* Students[MAX_STUDENTS];
//     int enrollment;
//     //an array of pointers that point to dynamically allocated object of type Person
//     
//     
// }
//
////RETURNING A REFERRENCE TO A CONST OBJECT
//class Person;
//const Person& older2(const string& a, const string& b);
//class Person {
//public:
//    Person(string name, int age){
//        m_name = name;
//        m_age = age;
//    }
//    int getAge() const {
//        return m_age;
//    }
//
//private:
//    string m_name;
//    int m_age;
//
//};
//
//const Person& older2(const Person& a, const Person& b){
//    if(a.getAge() > b.getAge())
//        return a;
//    else
//        return b;
//}
//
//int main(){
//    Person a("Josie", 20);
//    Person b("Joe", 18);
//
//    const Person& c = older2(a,b);
//    //above, c is an alias to a
//
//
//    Person c = older2(a,b);
//    //c is not an alias to a,  initialized with a values
//
//    const Person* c = &older2(a,b);
//    //this works but im not sure why the (&) is in front of function that returns a reference type
//    cout<< a.getAge();
//
//}
//
//
//CODE TRACING EXAMPLES:

#include <iostream>
using namespace std;

class A {
    int foo = 0;

public:
    int& getFoo()  { //cant have const here because it doesnt know whether the value set to return will be an alias or not and if alias then it could change it
        return foo;
    }
    void printFoo() const {
        cout << foo;
    }
};

int main() {
    A a;
 //int bar = a.getFoo();
    int& bar = a.getFoo();
//now bar is a alias for foo, so if you increase barr it increases foo
    //int bar = a.getFoo(), this is not an alias
    //like ** pointers to pointers...&& ref of ref
    cout << bar;
    ++bar;

    a.printFoo();
}




//Output:
//00
//
//

//#include <string>
//#include <iostream>
//using namespace std;
//
//class Person
//{
//    //private default
//    string first_name;
//    string last_name;
//    int m_age;
//public:
//    void set_name(string first, string second);
//
//    void set_age(int m_age);
//    string get_name() const;
//    string get_last_name() const;
//    int get_age() const;
//};
//
//
//void Person::set_name(string first, string second) {
//    first_name = first;
//    last_name = second;
//}
//
//void Person::set_age(int age)
//{
//    m_age = age;
//}
//
//string Person::get_name() const {
//    return first_name + " " + last_name;
//}
//
//string Person::get_last_name() const {
//    return last_name;
//}
//
//int Person::get_age() const {
//    return m_age;
//}
//
//Person have_baby(Person parent1, Person parent2) {
//    Person child;
//
//    //function call within function call
//    child.set_name("Cade", parent1.get_name() + parent2.get_name());
//    //parent1.get_last_name()...extra member functions that do stuff
//    child.set_age(0);
//    return child;
//    //returning the object before it is destroyed since local variable..if you returned a reference to this object you would be UNDEFINed Line cross
//}
//
//int main() {
//    Person mommy; //make object mommy, if there was a default constructor it would initialize mommy rn
//    mommy.set_name("Vickie", "Topmiller"); //mommy name = vickie topmiller
//    Person daddy;
//    daddy.set_name("Mike", "Mallett");
//    Person baby = have_baby(daddy, mommy);
//    cout << baby.get_age() << "  " << baby.get_name() << endl;
//}
//


//
//Output:
//0  Cade Mike MallettVickie Topmiller
//
//
//
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//class Enemy {
//    int secret;
//public:
//    Enemy() {
//        secret = -1;
//        cout << "You've made an Enemy!" << endl;
//    }
//    Enemy(int i) {
//        secret = i;
//        cout << "You've made Enemy " << i << endl;
//    }
//    ~Enemy() {
//        cout << "Destroying the enemy" << secret << endl;
//    }
//    void be_evil(int i)  {
//        cout << "I'm evil " << i << endl;
//    }
//    int get_secret() const {
//        return secret;
//    }
//};
//
//
////const pass by ref..save memory
//void foo(const Enemy& thisGuy) {
//    Enemy thatGuy;
//    //default constructor called...no ()
//    thatGuy.be_evil(thisGuy.get_secret());
//    //member function call as member function parameter..inception
//}
//
//int main() {
//    Enemy booper;
//    //default called
//    Enemy bopper(3);
//    //constructor with 1 parameter called
//    foo(bopper);
//    cout << "Done!" << endl;
//}
//
//
////
////
////Output
////
////You've made an Enemy!
////You've made Enemy 3
////You've made an Enemy!
////I'm evil 3
////Destroying the enemy -1 //destroying in inverse order they are created.. 1st destroy thatGuy when leaving foo
////Done!//end of main
////Destroying the enemy 3 //prints last 2 things made.. bopper(3)
////Destroying the enemy -1//prints booper()
////
////
//
//
//
//
//
//
//
//
//
//
