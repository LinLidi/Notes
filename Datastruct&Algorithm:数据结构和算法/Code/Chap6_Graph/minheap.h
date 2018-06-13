//最小堆

//自定义的swap函数
template<class Elem>
swap(Elem A[],int x,int y)
{
	Elem temp=A[x];
	A[x]=A[y];
	A[y]=temp;
}

//最小堆
template <class Elem>
class minheap
{
private:
	Elem *Heap;                         //堆指针
	int size;						    //堆大小
	int n;								//堆中实际元素个数

public:	
	//构造函数，以一个已有的数组为依据	
	minheap(Elem *A,int num,int max)    
	{
		Heap=A;                     //指向已有数组
		n=num;
		size=max;
		buildHeap();
	}

	bool isempty() const
	{
		return n<=0;
	}

	bool isLeaf(int pos)            //判断是否为叶
	{
		return (pos>=n/2)&&(pos<n);
	}
	int leftchild(int pos)          //左儿子
	{
		return 2*pos+1;
	}
	int rightchild(int pos)         //右儿子
	{
		return 2*pos+2;
	}
	int parent(int pos)             //父亲
	{
		return (pos-1)/2;
	}
	void buildHeap()                //建堆，参考siftdown函数
	{
		for(int i=n/2-1;i>=0;i--)
			siftdown(i);
	}
	//该函数将每一个元素放入其在堆中的合适位置
	void siftdown(int pos)
	{
		while(!isLeaf(pos))
		{
			int j=leftchild(pos);
			int rc=rightchild(pos);
			if((rc<n)&&(Heap[j]>Heap[rc]))    //取较小的儿子
				j=rc;
			if(!(Heap[pos]>Heap[j])) return;  //结束
			//比小儿子大，和小儿子交换
			swap(Heap,pos,j);
			pos=j;
		}
	}
	bool insert(Elem &val)
	{
		if(n>=size) return false;
		int curr=n++;               //先将插入的元素放到堆的末尾
		Heap[curr]=val;
		//这其实是一个siftup的过程
		while((curr!=0)&&(Heap[curr]<Heap[parent(curr)]))
		{
			swap(Heap,curr,parent(curr));
			curr=parent(curr);
		}
		return true;
	}
	Elem removemin()               //取最小元素
	{
		swap(Heap,0,--n);          //先将最小元素放到堆的末尾
		if(n!=0) siftdown(0);      //重建堆
		return Heap[n];
	}
	//取任何一个元素，比上面的函数多一个siftup的过程，注意siftup和siftdown两个过程只执行其中的一个
	bool remove(int pos,Elem &it)  
	{
		if((pos<0)||(pos>=n)) return false;
		swap(Heap,pos,--n);
		while(pos!=0&&(Heap[pos]<Heap[parent(pos)]))
		{
			swap(Heap,pos,parent(pos));
			pos=parent(pos);
		}
		//siftdown(pos);
		it=Heap[n];
		return true;
	}
};
