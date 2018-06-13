#include <iostream>
#include <cmath>
using namespace std;
struct point
{
    int x;
    int y;
};
int Partition(point r[ ], int first, int end)
{
    int i = first;
    int j = end;
    while (i < j)//1-从下标开始
    {
        while (i<j && r[i].y<=r[j].y)//1-2 从右向左移动下标
            j--;
        if (i < j)//1-2-1交换，左边下标向右移
        {
            int temp = r[i].y;r[i].y = r[j].y;r[j].y = temp;
            i++;
        }
        while (i<j && r[i].y<=r[j].y)
            i++;
        if (i < j)
        {
            int temp = r[i].y;r[i].y = r[j].y;r[j].y = temp;
            j--;
        }
    }
    return i;
}
void quickSort(point r[ ], int first, int end)
{
    int pivot;
    if (first < end)
    {
        pivot = Partition(r, first, end);
        quickSort(r, first, pivot-1);
        quickSort(r, pivot+1, end);
    }
}


double Distance(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double DCM_closestPoints(point S[],int low, int high)
{
    double d1;
    double d2;
    double d3;
    double d;
    int index=0;
    int n;
    point P[n];
    
    if(high-low == 1)
        return Distance(S[low],S[high]);
    if(high-low == 2)
    {
        d1=Distance(S[low],S[low+1]);
        d2=Distance(S[low+1],S[high]);
        d3=Distance(S[low],S[high]);
        if ((d1<d2) && (d1<d3))
            return d1;
        else if (d2<d3)
            return d2;
        else
            return d3;
    }
    
    int mid = (low+high)/2;
    d1 = DCM_closestPoints(S, low, mid);
    d2 = DCM_closestPoints(S, mid+1, high);
    if (d1 <= d2)
        d = d1;
    else
        d = d2;
    
    for (int i=mid; (i>=low)&&(S[mid].x-S[i].x<d); i--)
        P[index++]=S[i];
    for (int i=mid+1; (i<=high)&&(S[i].x-S[mid].x<d); i++)
        P[index++]=S[i];
    quickSort(P, 0, index-1);
    for (int i=0;i<index;i++)
    {
        for (int j=i+1;j< index;j++)
        {
            if (P[j].y-P[i].y>=d)
                break;
            else
            {
                d3=Distance(P[i],P[j]);
                if (d3<d) d=d3;
            }
        }
    }
    return d;
}
int main()
{
    point pointsPair[13]={{100,80},{12,8},{21,69},{43,23},{43,12},{95,42},{51,91},{61,68},{32,64},{63,21},{42,41},{57,84},{12,7}};
    cout<<DCM_closestPoints(pointsPair, 0, 12);
}