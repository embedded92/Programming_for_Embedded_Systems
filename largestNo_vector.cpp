/*
 * largestNo_vector.cpp
 *
 *  Created on: Oct 3, 2019
 *      Author: ramneet
 */
#include<iostream>
#include <stdio.h>
#include<vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;

int main()
{
    int i, n;
    vector<int> arr; //our container
       int fill; //our container content variable
       //invariant fill is the integer to be stored
       cout<<"Enter the number of elements: ";
       cin>>n;
       for (int j = 0; j != n; ++j)
       {
           cout<<"Enter your value ";
           cin>>fill;
           arr.push_back(fill);
       }

    // store largest number to arr[0]
    for(i = 1;i < n; ++i)
    {

       if(arr[0] < arr[i])
           arr[0] = arr[i];
    }
    cout << "Largest element is = " << arr[0];
    return 0;
}
