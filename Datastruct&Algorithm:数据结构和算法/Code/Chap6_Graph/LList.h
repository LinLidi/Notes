//链表，这个链表除了头定义以外没有任何操作函数，

//链表元素
template<class Elem>
class Link
{
public:
	Elem element;      //表目的数据
	Link *next;        //表目指针，指向下一个表目
	Link(const Elem& elemval,Link *nextval=NULL)  //构造函数
	{ element=elemval; next=nextval; }
	Link(Link *nextval=NULL) { next=nextval; }    //构造函数
};

//链表
template<class Elem>
class LList
{
public:
	Link<Elem>* head;  //head指针并不储存任何实际元素，其存在只是为了操作方便
	
	LList()            //构造函数
	{
		head=new Link<Elem>();
	}

	void removeall()        //释放边表所有表目占据的空间
	{
		Link<Elem> *fence;
		while(head!=NULL)   //逐步释放每个表目占据的空间
		{  
			fence=head;
			head=head->next;
			delete fence;
		}
	}

	~LList() { removeall(); } //析构函数
};