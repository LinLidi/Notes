void bubbleSort(int r[ ], int n){
    int bound;
    int exchange = n-1;
    int temp;
    while (exchange != 0){
        bound = exchange;
        exchange = 0;
        for (int i=0; i<bound; i++)
            if (r[i]>r[i+1]){
                temp = r[i];
                r[i] = r[i+1];
                r[i+1] = temp;
            }
    }
    for (int a = 0; a<=5; a++) {
        cout<<r[a]<<" ";
    }
}
