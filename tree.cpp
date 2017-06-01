#include <iostream>
using namespace std;
//声明模板类
template<class T>
class tree;
//声明模板栈
template<class T>
class stack_node;
//声明栈
template<class T>
class stack;
//声明队列节点
template<class T>
class queue_node;
//声明队列
template<class T>
class queue;
template<class T>
class tree_node
{
friend class tree<T>;
friend class stack_node<T>;
friend class queue_node<T>;
public:
	tree_node(){};
	//初始化
	tree_node(const T _data)
	{
		data=_data;
		left=NULL;
		right=NULL;
	}
	tree_node(const tree_node& _t)
	{
		this->data=_t.data;
		this->left=_t.left;
		this->right=_t.right;
	}
	//设置data
	void set_data(T _data)
	{
		data=_data;
	}
	//获取data
	T get_data() const
	{
		return data;
	}
	//设置左孩子
	void set_left(tree_node* _left)
	{
		left=_left;
	}
	//获取左孩子
	tree_node* get_left() const
	{
		return left;
	}
	//设置右孩子
	void set_right(tree_node* _right)
	{
		right=_right;
	}
	//获取右孩子
	tree_node* get_right() const
	{
		return right;
	}
private:
	T data;
	tree_node* left;
	tree_node* right;
};

//定义树
template<class T>
class tree
{
public:
	//初始化树
	tree()
	{
		root=NULL;
	}
	~tree()
	{
		delete root;
	}
	void set_root(tree_node<T>* r)
	{
		root=r;
	}
	//获取root
	tree_node<T>* get_right() const
	{
		return root;
	}
	//创建树
	tree_node<T>* creat_tree();
	//前序遍历
    void pre_order(tree_node<T> *r) const;
    //中序遍历
    void in_order(tree_node<T> *r) const;
    //后序遍历
    void post_order(tree_node<T> *r) const;
    //层次遍历
    void level_order(tree_node<T> *r) const;
    //获得叶子节点的个数
    int get_leaf_num(tree_node<T> *r) const;
    //获得二叉树的高度
    int get_hight(tree_node<T>* r);
    //二叉树前序遍历转双链表
    void pre_list(tree_node<T>* r);
    //二叉树中序遍历转双链表
    void in_list(tree_node<T>* r);
    //二叉树后、序遍历转双链表
    void post_list(tree_node<T>* r);
private:
	tree_node<T>* root;
};
//定义栈节点
template<class T>
class stack_node
{
friend class stack<T>;
public:
	stack_node()
	{
		next=NULL;
	}
private:
	tree_node<T> t;
	stack_node* next;
};
//定义栈
template<class T>
class stack
{
public:
	stack()
	{
		top=NULL;
	}
	~stack()
	{
		top=NULL;
	}
	//入栈
	void push_stack(tree_node<T>* root);
	//出栈
	void pop_stack();
	//判断栈是否为空
	bool is_stack_empty()
	{
		if(top==NULL)
		    return true;
		return false;
	}
	//获取栈顶值
	tree_node<T>* get_stack_top()
	{
		return top;
	}
private:
	stack_node<T>* top;
};
//定义队列节点
template<class T>
class queue_node
{
friend class queue<T>;
public:
	queue_node()
	{
		next=NULL;
	}
private:
	tree_node<T> queue_t;
	queue_node* next;
};
//定义队列
template<class T>
class queue
{
public:
	queue(queue_node<T>* _head=NULL,queue_node<T>* _tail=NULL):head(_head),tail(_tail){};
	//入队
	void push_queue(queue* q,tree_node<T>* r);
	//出队
	queue_node<T>* pop_queue(queue* q);
	//判断队列是否为空
	bool is_queue_empty()
	{
		if(head==NULL && tail==NULL)
			return true;
		return false;
	}
	//获取头结点值
	tree_node<T>* get_head() const
	{
		return &head->queue_t;
	}
	//获取节点值
	T get_data_queue() const
	{
		return head->queue_t.data;
	}
private:
	queue_node<T>* head;
	queue_node<T>* tail;
};
//创建树
template<class T>
tree_node<T>* tree<T>::creat_tree()
{
	T data;
	cin>>data;
	tree_node<T>* root=new tree_node<T>(data);
	if(data=='#')
	{
		root=NULL;
		return root;
	}
	else
	{
		root->set_left(creat_tree());//递归构建左子树
		root->set_right(creat_tree());//递归构建右子树
		return root;
	}
}

//======================================栈相关函数=============================================================
//入栈
template<class T>
void stack<T>::push_stack(tree_node<T>* root)
{
	stack_node<T>* ptr_new=new stack_node<T>();
	ptr_new->t=*root;
	ptr_new->next=top;
	top=ptr_new;
}
//出栈
template<class T>
void stack<T>::pop_stack()
{
	if(!is_stack_empty())
	{
		stack_node<T>* temp=top;
		top=top->next;
		delete temp;
		temp=NULL;
	}
}

//================================================队列相关函数================================================
//入队
template<class T>
void queue<T>::push_queue(queue<T>* q,tree_node<T>* r)
{
	queue_node<T>* ptr_new=new queue_node<T>;
	ptr_new->queue_t=*r;
	ptr_new->next=NULL;
	if(q->head==NULL)
	{
		q->head=ptr_new;
	}
	else
	{
		q->tail->next=ptr_new;
	}
	q->tail=ptr_new;
}
//出队
template<class T>
queue_node<T>* queue<T>::pop_queue(queue<T>* q)
{
	if(!is_queue_empty())
	{
		queue_node<T>* ptr_cur=q->head;
		q->head=q->head->next;
		if(q->head==NULL)
		{
			q->tail=NULL;
		}
		return ptr_cur;
	}
}
//==============================================遍历===========================================================
//前序遍历
template<class T>
void tree<T>::pre_order(tree_node<T> *r) const
{
	stack<T> st;
	while(r!=NULL || (! st.is_stack_empty()))
	{
		while(r!=NULL)
		{
			cout<<r->get_data()<<endl;
			st.push_stack(r);
			r=r->get_left();
		}
		if(!st.is_stack_empty())
		{
			r=st.get_stack_top();
			st.pop_stack();
			r=r->get_right();
	    }
	}
}
//中序遍历
template<class T>
void tree<T>::in_order(tree_node<T> *r) const
{
	stack<T> st;
	while(r!=NULL || (! st.is_stack_empty()))
	{
		while(r!=NULL)
		{
			st.push_stack(r);
			r=r->get_left();
			cout<<r->get_data()<<endl;
		}
		if(!st.is_stack_empty())
		{
			r=st.get_stack_top();
			st.pop_stack();
			r=r->get_right();
	    }
	}
}
//后序遍历
template<class T>
void tree<T>::post_order(tree_node<T> *r) const
{
	stack<T> st;
	int flag=1;
	while(r!=NULL || (! st.is_stack_empty()))
	{
		while(r!=NULL)
		{
			st.push_stack(r);
			r=r->left;
		}
		if(!st.is_stack_empty())
		{
			stack_node* temp=st.get_stack_top();
			r=&temp->t;
			if(flag==1)
			{
				st.pop_stack();
				st.push_queue();
				r=r->right;
				flag=2;
			}
			if(flag==2)
			{
				cout<<r->get_data()<<endl;
				st.pop_stack();
				root=NULL;
				flag=1;
			}
		}
	}
}
//层次遍历???
template<class T>
void tree<T>::level_order(tree_node<T>* r) const
{
	queue<T> q;
	queue<T>* p;
	if(r==NULL)
		return;
	q.push_queue(p,r);
	while(!q.is_queue_empty())
	{
		tree_node<T>* ptmp=&q.get_head();
		cout<<q.get_data_queue()<<endl;
		q.pop_queue();
		if(ptmp->get_left()!=NULL)
		{
			q.push_queue(p,r->get_left());
		}
		if(ptmp->get_right()!=NULL)
		{
			q.push_queue(p,r->get_right());
		}
	}
}
//===========================================个数与高度========================================================
//叶子节点个数
template<class T>
int tree<T>::get_leaf_num(tree_node<T>* r) const
{
	if(r==NULL)
	{
		return 0;
	}
	if(r->left==NULL && r->right==NULL)
	{
		return 1;
	}
	int left_num=get_leaf_num(r->get_left());
	int right_num=get_leaf_num(r->get_right());
	return left_num>=right_num?left_num:right_num;
}
//获得二叉树的高度
template<class T>
int get_hight(tree_node<T>* r)
{
	if(r==NULL)
		return 0;
	if(r->left==NULL && r->right==NULL)
		return 1;
	int RightHigh=get_hight(r->right);
	int LiftHigh=get_hight(r->left);
	return RightHigh>=LiftHigh?RightHigh+1:LiftHigh+1;
}
//=======================================转双链表==============================================================
//前序遍历转双链表
template<class T>
void teee<T>::pre_list(tree_node<T>* r)
{
	stack<T> st;
	queue<T> qu;
	tree_node<T>* head=NULL;
	tree_node<T>* tail=NULL;
	while(r!=NULL || (! st.is_stack_empty()))
	{
		while(r!=NULL)
		{
			qu.push_stack(r);//将根节点入队
			st.push_stack(r);
			r=r->get_left();
		}
		if(!st.is_stack_empty())
		{
			r=st.get_stack_top();
			st.pop_stack();
			r=r->get_right();
	    }
	}
	while(!qu.is_queue_empty())
	{
		r=&(qu.pop_queue()->queue_t);
		if(head==NULL)
		{
			head=r;
			tail=r;
		}
		else
		{
			tail->set_right(r);
			r->set_left(tail);
			tail=r;
		}
	}
}
//中序遍历转双链表
template<class T>
void teee<T>::in_list(tree_node<T>* r)
{
	stack<T> st;
	queue<T> qu;
	tree_node<T>* head=NULL;
	tree_node<T>* tail=NULL;
	while(r!=NULL || (! st.is_stack_empty()))
	{
		while(r!=NULL)
		{
			st.push_stack(r);
			r=r->get_left();
			qu.push_stack(r);//将根节点入队
		}
		if(!st.is_stack_empty())
		{
			r=st.get_stack_top();
			st.pop_stack();
			r=r->get_right();
	    }
	}
	while(!qu.is_queue_empty())
	{
		r=&(qu.pop_queue()->queue_t);
		if(head==NULL)
		{
			head=r;
			tail=r;
		}
		else
		{
			tail->set_right(r);
			r->set_left(tail);
			tail=r;
		}
	}
}
//后序遍历转双链表
template<class T>
void teee<T>::post_list(tree_node<T>* r)
{
	queue<T> qu;
	stack<T> st;
	int flag=1;
	while(r!=NULL || (! st.is_stack_empty()))
	{
		while(r!=NULL)
		{
			st.push_stack(r);
			r=r->left;
		}
		if(!st.is_stack_empty())
		{
			stack_node* temp=st.get_stack_top();
			r=&temp->t;
			if(flag==1)
			{
				st.pop_stack();
				st.push_queue();
				r=r->right;
				flag=2;
			}
			if(flag==2)
			{
				qu.push_stack(r);//将根节点入队
				st.pop_stack();
				root=NULL;
				flag=1;
			}
		}
	}
	while(!qu.is_queue_empty())
	{
		r=&(qu.pop_queue()->queue_t);
		if(head==NULL)
		{
			head=r;
			tail=r;
		}
		else
		{
			tail->set_right(r);
			r->set_left(tail);
			tail=r;
		}
	}
}
int main(int argc, char const *argv[])
{
	tree<int> t;
    tree_node<int>* root;
	root=t.creat_tree();
	cout<<"该树的前序遍历为:"<<endl;
	t.pre_order(root);
	return 0;
}