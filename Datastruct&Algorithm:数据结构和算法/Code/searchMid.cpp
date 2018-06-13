int searchMid(int A[], int B[], int n)
{
    int str1 = 0, end1 = n-1, str2 = 0, end2 = n-1;
    int mid1, mid2;
    while(str1<end1 && str2<end2)
    {
        mid1 = (str1+str2)/2;
        mid2 = (end1+end2)/2;
        if(A[mid1] == B[mid2])
        return A[mid1];
        if(A[mid1] < B[mid2])
        {
            if ((str1+end1)%2 == O) 
            str1 = mid1;
            else str1 = mid1+1;
            end2 = mid2;
        }
        else
        {
            if ((str2+end2) %2 == O)
            str2 = mid2;
            else str2 = mid2+1;
            end1 = mid1;
        }
    }
    if (A[str1J < B[str2] ) return A[str1];
    else return B[str2];
}


