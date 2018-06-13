int dist(char T[],char ch){
	int len=strlen(T);
	int i=len-1;
	if(ch==T[i])return len;
	i--;
	while (i>=0){
		 if(ch==T[i]){return len-1-i;}
		 else{i--;}
	}
	return len;
}
int BM(char S[],char T[]){
	int n=strlen(S);
	int m=strlen(T);
	int i=m-1;
	while(i<=n){
		int j=m-1;
		 while(j>0&&S[i]==T[j]){
			 j=j-1;
			 i=i-1;
		 }
		 if(j==0) return i+1;
		 else
		 { i=i+dist(T,S[i]);}
	 }
	 return 0;
}
