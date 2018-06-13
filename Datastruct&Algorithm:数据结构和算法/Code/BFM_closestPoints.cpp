#include <iostream>
#include <cmath>
using namespace std;
struct point
{
    int x;
    int y;
};

int BFM_closestPoints(int n, point a[], point b[])
{
    int index1 = 0;
    int index2 = 0;
    int d;
    int minDist = 1000;
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            d=sqrt((a[i].x-b[j].x)*(a[i].x-b[j].x) + (a[i].y-b[j].y)*(a[i].y-b[j].y));
            if (d<minDist)
            { minDist=d;index1=i+1;index2=j+1;}
        }
    }
    cout<<"最近的点对是：第"<<index1<<"对和第"<<index2<<"对"<<endl;
    cout<<"最短距离为："<<minDist<<endl;
    return  0;
}
int main()
{
    point pointsPair[13]={{100,80},{12,8},{21,69},{43,23},{43,12},{95,42},{51,91},{61,68},{32,64},{63,21},{42,41},{57,84},{12,7}};
    cout<<BFM_closestPoints(13, pointsPair, pointsPair);
}