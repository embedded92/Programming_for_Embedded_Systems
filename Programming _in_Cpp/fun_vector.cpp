/*
 * fun_vector.cpp
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

void func_largest_Num(vector<int> arr, int n)
{
	int i;
// store largest number to arr[0]
for(i = 1;i < n; ++i)
{
   if(arr[0] < arr[i])
       arr[0] = arr[i];
}
cout << "Largest element is = " << arr[0];
}

void func_bubble_sort(vector<int> arr, int n)
{
 int i,j,order;
    cout<<"Enter the order in which you want sorting: "
    		"Ascending = 0; "
    		"Descending =1; ";
    cin>>order;

    if(order==0)
    {
    	   for( i=0;i<n-1;i++)
    	    {
    	        for(j=0;j<n-i-1;j++)
    	        {
    	            //checking if previous value is
    	            //grater than next one or not
    	            if(arr[j]>arr[j+1])
    	            {
    	                //temp will temporarly store
    	                //the value of arr[j]
    	                //then we will swap the values
    	                int temp=arr[j];
    	                arr[j]=arr[j+1];
    	                arr[j+1]=temp;
    	            }
    	        }
    	    }
    }
    if(order==1)
    {
    	   for(i=0;i<n-1;i++)
    	    {
    	        for(j=0;j<n-i-1;j++)
    	        {
    	            //checking if previous value is
    	            //grater than next one or not
    	            if(arr[j]<arr[j+1])
    	            {
    	                //temp will temporarly store
    	                //the value of arr[j]
    	                //then we will swap the values
    	                int temp=arr[j];
    	                arr[j]=arr[j+1];
    	                arr[j+1]=temp;
    	            }
    	        }
    	    }
    }
    cout<<"After Bubble sort the array is:\n";
    for(i=0;i<n;i++)
    cout<<arr[i]<<" ";
	}

int main()
{
    int n;
    vector<int> arr1; //our container
       int fill; //our container content variable
       //invariant fill is the integer to be stored
       cout<<"Enter the number of elements: ";
       cin>>n;
       for (int j = 0; j != n; ++j)
       {
           cout<<"Enter your value ";
           cin>>fill;
           arr1.push_back(fill);
       }

       func_largest_Num(arr1,n);
       cout<<endl;
       func_bubble_sort(arr1,n);
           return 0;
}





