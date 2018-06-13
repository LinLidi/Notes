#define UNVISITED 0
#define VISITED 1
#define INFINITY 9999999
#define ROOT -1

#include <iostream>
#include <fstream>
#include "LList.h"
#include "minheap.h"
#include <queue>
using namespace std;

//数据结构部分:

/**************** 图的边的定义 ***************/
class Edge
{
public:
	int from,to,weight;    //from是边的始点,to是边的终点,weight是边的权

	Edge()                 //构造函数
	{
		from=-1;   
		to=-1;  
		weight=0;
	}
	
	Edge(int f,int t,int w)  //构造函数
	{
		from=f;   
		to=t;   
		weight=w;
	}

	bool operator >(Edge oneEdge)   //定义比较运算符>,边的大小比较即为边的权的大小比较
	{
		return weight>oneEdge.weight;
	}

	bool operator <(Edge oneEdge)  //定义比较运算符<,边的大小比较即为边的权的大小比较
	{
		return weight<oneEdge.weight;
	}
};

/**************** 图的定义 ***************/
//注意：该数据结构将有向图和无向图统一处理，无向图中的一条边将相当于有向图中的两条边
class Graph
{
public:
	int numVertex;	//图的顶点的个数
	int numEdge;    //图的边的个数
	int *Mark;      //Mark指针指向保存有图的顶点的标志位的数组,标志位用来标记某顶点是否被访问过
	int *Indegree;  //Indegree指针指向保存有图的顶点的入度的数组	
	
	Graph(int numVert)               //构造函数
	{
		numVertex=numVert;           //确定图的顶点的个数
		numEdge=0;                   //确定图的边数的个数
		Indegree=new int[numVertex]; //为保存图的顶点的入度申请数组,Indegree为数组指针
		Mark=new int[numVertex];     //为图的顶点的标志位申请数组,Mark为数组指针
		for(int i=0;i<numVertex;i++) //确定图的顶点的标志位和入度,即所有顶点的标志位初始化为未被访问过,入度初始化为0
		{
			Mark[i]=UNVISITED;
			Indegree[i]=0;
		}
	}

	~Graph()                         //析构函数
	{
		delete [] Mark;              //释放Mark数组
		delete [] Indegree;          //释放Indegree数组
	}

	virtual Edge FirstEdge(int oneVertex)=0;  //返回与顶点oneVertex相关联的第一条边
    virtual Edge NextEdge(Edge preEdge)=0;    //返回与边PreEdge有相同关联顶点oneVertex的下一条边

    int VerticesNum()              //返回图的顶点个数
	{
		return numVertex;
	}

    int EdgesNum()                 //返回图的边数
	{
		return numEdge;
	}
    
    bool IsEdge(Edge oneEdge)      //如果oneEdge是边则返回TRUE，否则返回FALSE
	{
		if(oneEdge.weight>0&&oneEdge.weight<INFINITY&&oneEdge.to>=0) 
			return true;
		else 
			return false;
	}

	int FromVertex(Edge oneEdge)   //返回边oneEdge的始点
	{
		return oneEdge.from;
	}

	int ToVertex(Edge oneEdge)     //返回边oneEdge的终点
	{
		return oneEdge.to;
	}

	int Weight(Edge oneEdge)	   //返回边oneEdge的权
	{
		return oneEdge.weight;
	}
	virtual void setEdge(int from,int to,int weight)=0;
	virtual void delEdge(int from,int to)=0;
};


/**************** 相邻矩阵方式实现的图 ***************/
class Graphm: public Graph   
{
private:
	int **matrix;           //指向相邻矩阵的指针
	
public:
	
	Graphm(int numVert):Graph(numVert)    //构造函数
	{
		int i,j;                          //i,j仅仅作为for循环中的计数器		

		matrix=(int**)new int*[numVertex];     //申请matrix数组,该数组有numVertex个元素,每个元素是整型指针类型
		for(i=0;i<numVertex;i++)               //matrix数组的每个元素,都指向一个具有numVertex个元素的数组
			matrix[i] = new int[numVertex];
		for(i=0;i<numVertex;i++)               //相邻矩阵的所有元素都初始化为0,如果矩阵元素matrix[i][j]不为0,则表明顶点i与顶点j之间有一条边,边的权即为matrix[i][j]的值
			for(j=0;j<numVertex;j++)
				matrix[i][j]=0;
	}

	~Graphm()                        //析构函数
	{
		for(int i=0;i<numVertex;i++) //释放每个matrix[i]申请的空间
			delete [] matrix[i];
		delete [] matrix;            //释放matrix指针指向的空间
	}

	Edge FirstEdge(int oneVertex)    //返回顶点oneVertex的第一条边
	{
		Edge myEdge;                 //边myEdge将作为函数的返回值
		myEdge.from=oneVertex;       //将顶点oneVertex作为边myEdge的始点
		for(int i=0;i<numVertex;i++) //寻找第一个使得matrix[oneVertex][i]不为0的i值,那么(oneVertex,i)或者<oneVertex,i>即为顶点oneVertex的第一条边
		{
			if(matrix[oneVertex][i]!=0)
			{
				myEdge.to=i;         //将顶点i作为边myEdge的终点
				myEdge.weight=matrix[oneVertex][i];   //边myEdge的权为矩阵元素matrix[oneVertex][i]的值
				break;
			}			
		}
		return myEdge;               //如果找到了顶点oneVertex的第一条边,则返回的myEdge确实是一条边;如果没有找到顶点oneVertex的第一条边,则myEdge的成员变量to为-1,根据IsEdge函数判断可知myEdge不是一条边
	}

	Edge NextEdge(Edge preEdge)      //返回与边PreEdge有相同关联顶点oneVertex的下一条边
	{
		Edge myEdge;                 //边myEdge将作为函数的返回值
		myEdge.from=preEdge.from;    //将边myEdge的始点置为与上一条边preEdge的始点相同
	   
		for(int i=preEdge.to+1;i<numVertex;i++) //寻找下一个使得matrix[preEdge.from][i]不为0的i值,那么(preEdge.from,i)或者<preEdge.from,i>即为顶点preEdge.from的下一条边
		{
			if(matrix[preEdge.from][i]!=0)
			{
				myEdge.to=i;
				myEdge.weight=matrix[preEdge.from][i];
				break;
			}
		}
		
		return myEdge;                //如果找到了顶点preEdge.from的下一条边,则返回的myEdge确实是一条边;如果没有找到顶点preEdge.from的下一条边,则myEdge的成员变量to为-1,根据IsEdge函数判断可知myEdge不是一条边
	}

	void setEdge(int from,int to,int weight)      //为图设定一条边
	{
		if(matrix[from][to]==0)                   //如果matrix[from][to]==0，则边(from,to)或者<from,to>将是新增的一条边，否则该边已经存在（现在只是对该边进行修改）
		{
			numEdge++;
			Indegree[to]++;
		}
		matrix[from][to]=weight;  		      
	}

	void delEdge(int from,int to)               //删掉图的一条边
	{
		if(matrix[from][to]!=0)					//如果matrix[from][to]!=0，则边(from,to)或者<from,to>确实存在，否则该边实际上并不存在（从而不必对图的边数和顶点to的入度进行修改）
		{
			numEdge--;
			Indegree[to]--;
		}
		matrix[from][to]=0;		     
	}
};


/**************** 邻接表方式实现的图 ***************/
struct listUnit      //邻接表表目中数据部分的结构定义
{
	int vertex;      //边的终点
	int weight;      //边的权
};


class Graphl: public Graph                    
{
	friend class Graphdup;       //Graphdup是下面我们将讨论的邻接多重表的实现方式

private:
	LList<listUnit> *graList;    //graList是保存所有边表的数组
	
public:
	Graphl(int numVert):Graph(numVert)          //构造函数
	{
		graList=new LList<listUnit>[numVertex]; //为graList数组申请空间，图有numVertex个顶点，则有numVertex个边表
	}

	~Graphl()                                   //析构函数
	{
		delete [] graList;						//释放空间
	}
	
	Edge FirstEdge(int oneVertex)              //返回顶点oneVertex的第一条边
	{
		Edge myEdge;                           //边myEdge将作为函数的返回值
		myEdge.from=oneVertex;                 //将顶点oneVertex作为边myEdge的始点
		Link<listUnit> *temp=graList[oneVertex].head;  //graList[oneVertex].head保存的是顶点oneVertex的边表，temp->next指向顶点oneVertex的第一条边(如果temp->next不为null)
		if(temp->next!=NULL)                   //如果顶点oneVertex的第一条边确实存在
		{
			myEdge.to=temp->next->element.vertex;
			myEdge.weight=temp->next->element.weight;
		}
		return myEdge;	                      //如果找到了顶点oneVertex的第一条边,则返回的myEdge确实是一条边;如果没有找到顶点oneVertex的第一条边,则myEdge的成员变量to为-1,根据IsEdge函数判断可知myEdge不是一条边
	}
	
	Edge NextEdge(Edge preEdge)               //返回与边PreEdge有相同关联顶点oneVertex的下一条边
	{
		Edge myEdge;                          //边myEdge将作为函数的返回值
		myEdge.from=preEdge.from;             //将边myEdge的始点置为与上一条边preEdge的始点相同
		Link<listUnit> *temp=graList[preEdge.from].head;           //graList[oneVertex].head保存的是顶点oneVertex的边表，temp->next指向顶点oneVertex的第一条边(如果temp->next不为null)
		while(temp->next!=NULL&&temp->next->element.vertex<=preEdge.to)  //确定边preEdge在边表中的位置,如果边preEdge的下一条边确实存在，则temp->next指针指向下一条边的表目
			temp=temp->next;
		if(temp->next!=NULL)                 //边preEdge的下一条边存在			                                
		{
			myEdge.to=temp->next->element.vertex;
			myEdge.weight=temp->next->element.weight;			
		}
		return myEdge;
	}
	
	void setEdge(int from,int to,int weight)   //为图设定一条边
	{
		Link<listUnit> *temp=graList[from].head;  //graList[from].head保存的是顶点from的边表，temp->next指向顶点from的第一条边(如果temp->next不为null)
		while(temp->next!=NULL&&temp->next->element.vertex<to)   //确定边(from,to)或<from,to>在边表中的位置,如果不存在,则边(from,to)或<from,to>为新加的一条边
			temp=temp->next;
		if(temp->next==NULL)                //边(from,to)或<from,to>在边表中不存在且在边表中其后已无其它边,则在边表中加入这条边
		{
			temp->next=new Link<listUnit>;
			temp->next->element.vertex=to;
			temp->next->element.weight=weight;
			numEdge++;
			Indegree[to]++;
			return;
		}
		if(temp->next->element.vertex==to) //边(from,to)或<from,to>在边表中已存在,故只需要改变边的权值
		{
            temp->next->element.weight=weight;
			return;
		}
		if(temp->next->element.vertex>to) //边(from,to)或<from,to>在边表中不存在,但在边表中其后存在其它边,则在边表中插入这条边
		{
			Link<listUnit> *other=temp->next;
			temp->next=new Link<listUnit>;
			temp->next->element.vertex=to;
			temp->next->element.weight=weight;
			temp->next->next=other;
			numEdge++;
			Indegree[to]++;			
		}
	}

	void delEdge(int from,int to)      //删掉图的一条边
	{
		Link<listUnit> *temp=graList[from].head;      //graList[from].head保存的是顶点from的边表，temp->next指向顶点from的第一条边(如果temp->next不为null)
		while(temp->next!=NULL&&temp->next->element.vertex<to)   //确定边(from,to)或<from,to>在边表中的位置(如果该边存在)
			temp=temp->next;
		if(temp->next==NULL) return;   //边(from,to)或<from,to>在边表中不存在,则不需要做任何操作	
		if(temp->next->element.vertex==to)  //边(from,to)或<from,to>在边表中存在且确定了该边在边表中的位置,则从边表中将其删掉
		{
			Link<listUnit> *other=temp->next->next;
			delete temp->next;
			temp->next=other;
			numEdge--;
			Indegree[to]--;			
		}
	}
};


//算法部分:


//深度优先周游（从一个点开始周游）：
void DFS(Graph& G, int V)
{
	G.Mark[V]= VISITED;                           //标记该点
	cout<<V<<"\t";								  //打印
	for(Edge e=G.FirstEdge(V);G.IsEdge(e);e=G.NextEdge(e))  //由该点所连的边进行深度优先周游
	{
	
		if(G.Mark[G.ToVertex(e)]==UNVISITED)               //访问V邻接到的未被访问过的顶点，并递归地按照深度优先的方式进行周游
			DFS(G, G.ToVertex(e));	
	}
}

//广度优先周游（从一个点开始周游）：
void BFS(Graph& G, int V)
{
	using std::queue;
	queue<int> Q;                   //初始化广度优先周游要用到的队列
	
	G.Mark[V]= VISITED;             //访问顶点V，并标记其标志位
	cout<<V<<"\t";                  //打印
	Q.push(V);                      //V入队
	
	while(!Q.empty())               //如果队列仍然有元素
	{
		int V=Q.front();		    //顶部元素
		Q.pop();                    //出队
	
		for(Edge e=G.FirstEdge(V);G.IsEdge(e);e=G.NextEdge(e))    //将与该点相邻的每一个未访问点都入队
		{			
			if(G.Mark[G.ToVertex(e)]== UNVISITED)   //访问V邻接到的所有未被访问过的顶点
			{				
				G.Mark[G.ToVertex(e)]= VISITED;     //访问顶点V，并标记其标志位
	        	cout<<G.ToVertex(e)<<"\t";          //打印
				Q.push(G.ToVertex(e));              //入队				
			}			
		}
	}
}

//图周游：
void graph_traverse(Graph& G,bool useDFS)
{
	for(int i=0;i<G.VerticesNum();i++)  //对图所有顶点的标志位进行初始化
		G.Mark[i]=UNVISITED;
	for(i=0;i<G.VerticesNum();i++)      //检查图的所有顶点是否被标记过，如果未被标记，则从该未被标记的顶点开始继续周游
    {
		if(G.Mark[i]== UNVISITED)
		{
			if(useDFS)
				DFS(G,i);       //深度优先搜索
			else
				BFS(G,i);       //广度优先搜索
		}
	}
	cout<<endl;
}

//队列方式实现的拓扑排序
void TopsortbyQueue(Graph& G)                     
{
	for(int i=0;i<G.VerticesNum();i++)     //初始化Mark数组
		G.Mark[i]=UNVISITED;

    using std::queue;
	queue<int> Q;                          //初始化队列
	
	for(i=0; i<G.VerticesNum(); i++)       //图中入度为0的顶点入队
	{
		if(G.Indegree[i]==0)    
		{
			Q.push(i);                            
		}
	}

	while(!Q.empty())                 //如果队列中还有图的顶点
	{
		int V=Q.front();		
		cout<<V<<"\t";               //打印输出该顶点
		G.Mark[V]=VISITED;
		Q.pop();                     //一个顶点出队
			
		for(Edge e= G.FirstEdge(V);G.IsEdge(e);e=G.NextEdge(e))  //所有与之相邻的点入度-1
		{				
			G.Indegree[G.ToVertex(e)]--;   //边e的终点的入度值减1
			if(G.Indegree[G.ToVertex(e)]==0)
			{
				Q.push(G.ToVertex(e));    //入度为0的顶点入队				
			}
		}
	}
	
	cout<<endl;

	for(i=0; i<G.VerticesNum(); i++)
	{ 
      if(G.Mark[i]==UNVISITED)
	  {            
	    cout<<"此图有环！"<<endl;        //图有环
        break;
      }
	}            
}


void Do_topsort(Graph& G, int V,int *result,int& tag)    //深度优先搜索方式实现拓扑排序
{
	G.Mark[V]= VISITED;
	for(Edge e= G.FirstEdge(V);G.IsEdge(e);e=G.NextEdge(e))
    {		
		if(G.Mark[G.ToVertex(e)]== UNVISITED)            //访问V邻接到的所有未被访问过的顶点
			Do_topsort(G, G.ToVertex(e),result,tag);     //递归调用        
	}
	result[tag++]=V;
}

void TopsortbyDFS(Graph& G)               //深度优先搜索方式实现的拓扑排序,结果是颠倒的
{
	for(int i=0; i<G.VerticesNum(); i++)  //对图所有顶点的标志位进行初始化
		G.Mark[i]=UNVISITED;

	int *result=new int[G.VerticesNum()];
	int tag=0;
	for(i=0; i<G.VerticesNum(); i++)      //对图的所有顶点进行处理
		if(G.Mark[i]== UNVISITED)
			Do_topsort(G,i,result,tag);   //调用递归函数

	for(i=G.VerticesNum()-1;i>=0;i--)     //逆序输出
	{		
		cout<<result[i]<<"\t";
	}
	cout<<endl;
}

//Dijkstra算法

//用最小堆的方法实现实现寻找离访问组距离最小的点的功能
//为利用minheap，定义特别的DijElem类
class DijElem
{
public:
	int vertex;
	int distance;
	
	DijElem(int v=-1,int d=INFINITY)
	{
		vertex=v;
		distance=d;
	}	

	bool operator<(const DijElem &ele) const
	{
		return distance<ele.distance;
	}

	bool operator>(const DijElem &ele) const
	{
		return distance>ele.distance;
	}

	bool operator==(const DijElem &ele) const
	{
		return distance==ele.distance;
	}
};

//D的初始值为D[s]=0, D[else]=INFINITY
void Dijkstra(Graph& G,int *D,int s)
{
	int v;
	for(int i=0;i<G.VerticesNum();i++)           //初始化Mark数组
		G.Mark[i]=UNVISITED;
	
	//用最小堆方式实现找距离最小的顶点
	DijElem *E=new DijElem[G.VerticesNum()];
	DijElem temp;
	temp.vertex=s;
	temp.distance=0;	
	E[0]=temp;
	minheap<DijElem> H(E,1,G.VerticesNum());

	for(i=0;i<G.VerticesNum();i++)
	{	    
		do
		{
			if(H.isempty())
				return;
			temp=H.removemin();
			v=temp.vertex;
		}while(G.Mark[v]==VISITED);
		

		if(D[v]==INFINITY)                       			
			break;
		G.Mark[v]=VISITED;                       //把该点加入已访问组
		cout<<v<<"\t";                           //输出
		for(Edge e=G.FirstEdge(v);G.IsEdge(e);e=G.NextEdge(e)) //刷新D中的值，因为v的加入，D的值需要改变，只要刷新与v相邻的点的值
		{			
			if(D[G.ToVertex(e)]>(D[v]+G.Weight(e)))
			{
				D[G.ToVertex(e)]=D[v]+G.Weight(e);	                
				temp.vertex=G.ToVertex(e);
				temp.distance=D[G.ToVertex(e)];
				H.insert(temp);
			}
		}
	}	
}

//每对顶点之间的最短距离，用Floyd算法实现
void Floyd(Graph& G,int **D)
{
	
	int i,j,v;                 //i,j是计数器，v记录相应顶点

	//初始化D数组
	for(i=0;i<G.VerticesNum();i++)
	{
		for(j=0;j<G.VerticesNum();j++)
		{
			if(i==j) 
				D[i][j]=0;
			else				
				D[i][j]=INFINITY;			
		}
	}
	
	//D=adj[0]，将边的值填入D数组
	for(v=0;v<G.VerticesNum();v++)
	{
		for(Edge e=G.FirstEdge(v);G.IsEdge(e);e=G.NextEdge(e))
		{			
			D[v][e.to]=G.Weight(e);			
		}
	}

	//如果两个顶点间的最短路径经过顶点v，则有D[i][j]>(D[i][v]+D[v][j])
	//通过对v的循环，相当于将图一个顶点一个顶点的扩大
	for(v=0;v<G.VerticesNum();v++)
		for(i=0;i<G.VerticesNum();i++)
			for(j=0;j<G.VerticesNum();j++)
				if(D[i][j]>(D[i][v]+D[v][j]))
					D[i][j]=D[i][v]+D[v][j];
	
	for(i=0;i<G.VerticesNum();i++)
	{
		for(j=0;j<G.VerticesNum();j++)
			cout<<D[i][j]<<"\t";
		cout<<endl;
	}
}


//最小支撑树的算法

//添加边
void AddEdgetoMST(int i,int j,Edge *MST,int tag)
{
	MST[tag].from=i;
	MST[tag].to=j;
}

//最小支撑树的Prim算法,寻找下一条权最小的边采用最小堆的方式
void Prim(Graph& G, int s)        
{	
	int MSTtag=0;                            //最小支撑树边的标号
	Edge *MST=new Edge[G.VerticesNum()-1];   //存储最小支撑树的边
	int Etag=0;
	Edge *E=new Edge[G.EdgesNum()];

	for(int i=0;i<G.VerticesNum();i++)       //初始化Mark数组
	{
		G.Mark[i]=UNVISITED;			                    
	}	
	G.Mark[s]=VISITED;

	for(Edge e=G.FirstEdge(s);G.IsEdge(e);e=G.NextEdge(e))
	{
		E[Etag++]=e;		
	}
	
	minheap<Edge> H(E,Etag,G.EdgesNum());

	for(i=1; i<G.VerticesNum(); i++)
	{
        //寻找权最小的边
		if(H.isempty())
		{
			cout<<"不存在最小支撑树！";
			return;
		}
		Edge temp=H.removemin();
		
		if(G.Mark[temp.to]==UNVISITED)
		{
			AddEdgetoMST(temp.from,temp.to,MST,MSTtag++);
			G.Mark[temp.to]=VISITED;
			for(e=G.FirstEdge(temp.to);G.IsEdge(e);e=G.NextEdge(e))
			{
				if(G.Mark[e.to]==VISITED)
					continue;				
				H.insert(e);
			}
		}
		else
			i--;
	}      	

	//输出
	for(i=0;i<G.VerticesNum()-1;i++)
		cout<<MST[i].from<<"-"<<MST[i].to<<"\t";
	cout<<endl;
}

//Kruskal算法
//用“父指针”法表示等价类的类
class Gentree
{
private:
	int* array;             //叶结点数组
	int size;               //叶结点的大小
public:
	Gentree(int sz)         //构造函数
	{
		size=sz;
		array=new int[sz];
		for(int i=0;i<sz;i++) 
			array[i]=ROOT;  //ROOT表示整个树的根结点
	}
	~Gentree()           //析构函数，释放空间
	{
		delete [] array;
	}
	int FIND(int curr)   //寻找根的函数
	{
		while(array[curr]!=ROOT)
			curr=array[curr];
		return curr;
	}

	void UNION(int a,int b)     //将a和b合并到一个等价类中，a和b在一个等价类中就是他们有相同的根
	{
		int root1=FIND(a);
		int root2=FIND(b);
		if(root1!=root2) 
			array[root2]=root1;
	}

	bool differ(int a,int b)    //判断a和b是否不等价
	{
		int root1=FIND(a);
		int root2=FIND(b);
		return root1!=root2;
	}
};

//最小支撑树的Kruskal算法
void Kruskal(Graph& G)       
{	
	Gentree A(G.VerticesNum());            //等价类
    Edge *E=new Edge[G.EdgesNum()];        //记录图的所有边
	Edge *MST=new Edge[G.VerticesNum()-1]; //最小支撑树
	int MSTtag=0;
	int edgecount=0;

    for(int i=0; i<G.VerticesNum(); i++)    //将图的所有边记录在数组E中
	{
		for(Edge e= G.FirstEdge(i);G.IsEdge(e);e=G.NextEdge(e))
		{			
			if(G.FromVertex(e)< G.ToVertex(e)) 
				E[edgecount++]=e;		
		}
	}
    
	edgecount--;                                    //得到图的边数
	minheap<Edge> H(E,edgecount,edgecount);        //最小堆（min-heap）
    
	int EquNum=G.VerticesNum();  //开始时有|V|个等价类
    for(i=0; EquNum>1;i++)      //合并等价类
	{
		Edge e=H.removemin();       //获得下一条权最小的边
		if(e.weight>=INFINITY)
		{
			cout<<"不存在最小支撑树."<<endl;
			return;
		}
        int from=G.FromVertex(e);   //记录该条边的信息
        int to= G.ToVertex(e);
        if(A.differ(from,to))       //如果边e的两个顶点不在一个等价类
		{
			A.UNION(from,to);       //将边e的两个顶点所在的两个等价类合并为一个
			AddEdgetoMST(from,to,MST,MSTtag++); //将边e加到MST
			EquNum--;             //将等价类的个数减1
		}
	}
	
	for(i=0;i<G.VerticesNum()-1;i++)
		cout<<MST[i].from<<"-"<<MST[i].to<<"\t";
	cout<<endl;
}


void main()
{
	//依用户的选择实现功能
	cout<<"——————第一步：构造图——————"<<endl;
	//获取构图方式
	cout<<"请选择构图方式："<<endl;
	cout<<"(1)相邻矩阵"<<endl;
	cout<<"(2)邻接表"<<endl;
	
	int choice;
	cout<<"你的选择是(例如，输入1，然后回车，即表示用相邻矩阵的构图方式)：";
	cin>>choice;
	if(choice>2||choice<1)
	{
		cout<<"错误的输入！"<<endl;
		return;
	}
	cout<<endl;

	int isDirected;                        //标记是否有向图
	int numVertex;                         //图的顶点个数（边数将在setEdge中被自动修改）
	int from,to,weight;                    //读入每条边的起点，终点和权
	ifstream GraphSou;                     //输入文件流
	//文件格式必须正确无误，否则无法工作
	cout<<"请输入构图文件（例如，输入a.txt，然后回车。请确保构图文件是正确的格式，可参见同目录下文件a.txt的格式及说明文件readme.txt）:";
	char filename[20];
	cin>>filename;                         //获取文件名
	
	GraphSou.open(filename);
	GraphSou>>isDirected;                  //是否有向
	if(isDirected!=1&&isDirected!=0)
	{
		cout<<"文件格式不正确，请重新输入。"<<endl;
		return;
	}

	GraphSou>>numVertex;                   //顶点个数
	Graph *myGra;                          //图本身
	if(choice==1)                          //相邻矩阵
		myGra=new Graphm(numVertex);
	else                                   //因为邻接多重表是通过邻接表来初始化的
		myGra=new Graphl(numVertex);
	
	while(!GraphSou.eof())                 //顺次读取边的信息
	{
		GraphSou>>from>>to>>weight;
		if(from>=0&&to>=0&&weight>0&&from<numVertex&&to<numVertex)
		{
			myGra->setEdge(from,to,weight);
			if(!isDirected)
				myGra->setEdge(to,from,weight);
		}
		else
		{
			cout<<"文件数据非法，请重新输入。"<<endl;
			return;
		}
	}	
	
	cout<<endl;
	//输出图的构造情况以便用户检查
	cout<<"**********你所构造的图具体情况如下：**********"<<endl;
	if(isDirected)
		cout<<"该图为有向图。"<<endl;
	else
		cout<<"该图为无向图。"<<endl;
	cout<<"顶点数——"<<myGra->VerticesNum()<<endl;
	cout<<"存在边如下——"<<endl;
	for(int i=0;i<myGra->VerticesNum();i++)
	{
		for(Edge e=myGra->FirstEdge(i);myGra->IsEdge(e);e=myGra->NextEdge(e))
		{			
			cout<<"始点："<<e.from<<" 终点："<<e.to<<" 权："<<e.weight<<endl;			
		}
		cout<<endl;
	}	
	
	//依据用户的选择来验证各种算法
	cout<<"——————第二步：验证图的算法——————"<<endl;
	cout<<"请选择要进行的操作（例如，输入1，然后回车，表示你选择进行“图的深度优先周游”，按除1-8之外的其它键则自动退出）:"<<endl;
	cout<<"(1)图的深度优先周游"<<endl;
	cout<<"(2)图的广度优先周游"<<endl;
	cout<<"(3)由队列方式实现的拓扑排序"<<endl;
	cout<<"(4)由深度优先搜索方式实现的拓扑排序"<<endl;
	cout<<"(5)单源最短路径(Dijkstra算法)"<<endl;
	cout<<"(6)每对顶点之间的最短路径(Floyd算法)"<<endl;
	cout<<"(7)最小支撑树(Prim算法)"<<endl;
	cout<<"(8)最小支撑树(Kruskal算法)"<<endl;	
	while(1)
	{		
		cout<<"你的选择是：";
		cin>>choice;
		if(choice==1)
			graph_traverse(*myGra,true);
		else if(choice==2)
			graph_traverse(*myGra,false);
		else if(choice==3)
		{
			if(!isDirected)
			{
				cout<<"此图是无向图，而拓扑排序算法适用于有向无环图！"<<endl;
				continue;
			}
			TopsortbyQueue(*myGra);
		}
		else if(choice==4)
		{
			if(!isDirected)
			{
				cout<<"此图是无向图，而拓扑排序算法适用于有向无环图！"<<endl;
				continue;
			}
			TopsortbyDFS(*myGra);
		}
		else if(choice==5)
		{
			int start;
			while(1)
			{
				cout<<"请选择源点(例如，输入0，然后回车，表示你选择以顶点0为源点)：";
				cin>>start;
				if(start<0||start>=myGra->VerticesNum())
					cout<<"输入非法。"<<endl;
				else break;
			}
			int *DforDijkstra=new int[myGra->VerticesNum()];
			for(i=0;i<myGra->VerticesNum();i++)
				DforDijkstra[i]=INFINITY;
			DforDijkstra[start]=0;
			Dijkstra(*myGra,DforDijkstra,start);
			cout<<endl;
			for(i=0;i<myGra->VerticesNum();i++)
				cout<<start<<"，"<<i<<"="<<DforDijkstra[i]<<endl;
		}
		else if(choice==6)
		{
			int **DforFloyd=(int **)new int*[myGra->VerticesNum()];
			for(i=0;i<myGra->VerticesNum();i++)
				DforFloyd[i]=new int[myGra->VerticesNum()];
			Floyd(*myGra,DforFloyd);
		}
		else if(choice==7)
		{
			if(isDirected)
			{
				cout<<"此图是有向图，而最小支撑树的Prim算法适用于连通无向图！"<<endl;
				continue;
			}
			int start;
			while(1)
			{
				cout<<"请选择起始点(例如，输入0，然后回车，表示你选择以顶点0为始点)：";
				cin>>start;
				if(start<0||start>=myGra->VerticesNum())
					cout<<"输入非法。"<<endl;
				else break;
			}
			Prim(*myGra,start);
		}
		else if(choice==8)
		{		
			if(isDirected)
			{
				cout<<"此图是有向图，而最小支撑树的Kruskal算法适用于连通无向图！"<<endl;
				continue;
			}
			Kruskal(*myGra);
		}
		else 
			return;
		cout<<endl;
	}
}