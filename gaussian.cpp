/*
GaussJorden in Cpp
 * gaussian.cpp
 *
 *  Created on: Sep 30, 2019
 *      Author: ramneet
 */
#include<iostream>
#include<iomanip>

using namespace std;

int main()
{
int n=3;
double a[3][3],b[3],x[3];
cout<<"enter the matrix A\n";
for (int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
cin>>a[i][j];
}

}
cout<<"you entered the following :\n";
for (int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
cout<<setw(4)<<a[i][j]<<endl;
}

}

cout<<"enter matrix B"<<endl;
for (int i=0;i<n;i++)
{
cin>>b[i];
}
cout<<"you entered"<<endl;
for (int i=0;i<n;i++)
{
cout<<b[i]<<endl;
}
for(int k = 1; k<= n-1; ++k)
{
for (int i = k+1; i<= n ; ++i)
{
int factor = a[i][k] / a[k][k] ;
for (int j = k+1 ; j<=n ; ++j)
{
a[i][j] = a[i][j]-factor*a[k][j];
b[i] = b[i]-factor*b[k];
}
}
}
x[n] = b[n] / a[n][n];
for (int i = n-1;i>=1; i--)
{
int sum = 0;
for( int j = i+1; j<= n ; ++j)
{
 sum = sum + a[i][j]*x[j];
x[i] = (b[i] -sum) / a[i][i];
}
cout<<x[i];
}
cout<<"\nsolution of equations are:"<<endl;


return 0;
}

