/*
 * bubble_inCpp.cpp
 *
 *  Created on: Oct 2, 2019
 *      Author: ramneet
 */

#include<iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int n;
    int order;
    cout<<"Enter number of element you want to store: ";
    cin>>n;
    int arr[n],i,j=0;
    cout<<"Enter array values:\n";

    //taking the array value to sort from user
    for(i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    cout<<"Enter the order in which you want sorting: "
    		"Ascending = 0"
    		"Descending =1\n";
    cin>>order;

    if(order==0)
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
    if(order==1)
    {
    	   for(i=0;i<n-1;i++)
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
    cout<<"After Bubble sort the array is:\n";
    for(i=0;i<n;i++)
    cout<<arr[i]<<" ";
    return 0;
}

