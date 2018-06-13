void Merge(int r[],int rNew[],int s,int m, int t){  // i,j分别指向两个待合并的有序子序列，k指向最终有序序列的当前记录
    int i=s;
    int j=m+1;
    int k=s;
    while (i<=m && j<=t){
        if (r[i]<=r[j])
            rNew[k++] = r[i++];   //取r[i]和r[j]中较小者放入r1[k]
        else rNew[k++] = r[j++];
    }
    while (i<=m)
        rNew[k++] = r[i++];
    while (j<=t)
        rNew[k++]=r[j++];
}
void mergeSort(int r[],int s,int t){//对r[s]~r[t]进行归并排序
    int m;
    int rNew[1000];
    if (s == t) return;
    else{
        m = (s+t)/2;
        mergeSort(r,s,m);    //归并排序前半个子序列
        mergeSort(r,m+1,t);   //归并排序后半个子序列
        Merge(r,rNew,s,m,t);//合并两个已排序的子序列
        for (int i = s;i<=t;i++)
            r[i] = rNew[i];
    }
}
