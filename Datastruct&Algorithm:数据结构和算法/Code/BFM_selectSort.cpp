void selectSort(int r[ ], int n)
{
    int i;
    int j;
    int index;
    int temp;
    for (i=0; i<n-1; i++){//选择r[]里面的一个数
        index=i;
        for (j=i+1; j<n; j++)//选择r[i]后面比r[i]小的数
            if (r[j]<r[index]) index=j;
        if (index!=i){
            temp = r[i];
            r[i] = r[index];
            r[index] = temp;
        }
    }
}
