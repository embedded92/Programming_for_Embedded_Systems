/*
 * Recursion.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: ramneet
 */
// Recursion program
#include <iostream>
#include <string>
using namespace std;

void printnum ( int begin )  //Function for recursion
{

//To print capital letters(A-Z) the ASCII starts from 65 upto 90.
cout<< (char)begin;
if ( begin < 90 ) // The base case is when begin is greater than 9
 // for it will not recurse after the if-statement
printnum ( begin + 1 );
}

void printnum1 ( int begin )////Function for recursion
{
//To print capital letters(A-Z) the ASCII starts from 97 upto 122.

cout<< (char)begin;
if ( begin < 122 ) // The base case is when begin is greater than 9
// for it will not recurse after the if-statement
printnum1 ( begin + 1 );

}

int main (int argc,char *argv[])   // passing command line arguments
{

for(int i=0;i<argc; i++)
{

cout<<"Argument " <<i<< " is"<< argv[i];

}

string print1="1"; //To print "capital case letters"
string print2="2"; //to print "Small case letters"

if (argv[1]==print1)  //when argument is "1", it will print ASCII of 65 and onwards
{
printnum (65);  //ASCII of 65 is "A"
}
else if (argv[1]==print2)//when argument is  "2", it will print ASCII of 97 and onwards
{
printnum1 (97); //ASCII of 97 is "a"
}
else //if argument passed is neither 1 nor 2
cout<<"you entered wrong value(enter either 1 or 2)"<<endl;


}//end of program





