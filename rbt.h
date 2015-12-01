#ifndef __RBT__
#define __RBT__
#ifndef __ALLOCATOR__
#include "allocator.h"
#endif
#ifndef __MALLOC_ALLOC_TEMPLATE__
#include "__malloc_alloc_template.h"
#endif
#ifndef __G_CUN__
#include "g_func.h"
#endif
enum br_color{black = 0,red};
template<class T>
struct rbt_node{
	rbt_node *l_child;
	rbt_node *r_child;
	rbt_node *parent;
	T data;
	br_color color;//here the color of the rbt_node
};
template<class T,class Alloc>
class RBT{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef size_t size_type;
	typedef rbt_node<T> node;
	typedef typename __allocator<node,Alloc> allocator_t;
	
	RBT() :root(nullptr){}
	node *create_node(const value_type& lhs)
	{
		node* tmp = (node*)allocator_t::allocate();
		construct(&tmp->data, lhs);
		tmp->color = red;
		tmp->l_child = nullptr;
		tmp->r_child = nullptr;
		tmp->parent = nullptr;
	}
	void delete_node(node* lhs)
	{
		if (lhs)
		{
			destory(&lhs->data);
			allocator_t::deallocate(lhs);
		}
	}
	void rotate_left(node *lhs)
	{
	
		if (lhs)
		{
			//here  record the right node of the lhs
			node* _tmp = lhs->r_child;
			/* here complete the _tmp's lchild transfered to lhs's rchild*/
			//here assign _tmp's lchild to lhs's rchild;
			lhs->r_child = _tmp->l_child;
			//here  assign lhs to _tmp's lchild's parent;
			if (_tmp->l_child)
				_tmp->l_child->parent = lhs;

			/*here to deal the _tmp's parent so */
			//here put the lhs's parent to _tmp's parent;
			//exchange there parents;
			_tmp->parent = lhs->parent;

			/*here deal the lhs's parent's child
			and assign the _tmp to lhs's parent's child
			*/
			if (!lhs->parent)
				root = _tmp;

			/*here assign _tmp to lhs's parent's lchild while lhs's parent's lchild equal lhs*/
			else if (lhs->parent->l_child == lhs)
				lhs->parent->l_child = _tmp;

			else
				lhs->parent->r_child = _tmp;

			/*
			here only left that _tmp and lhs
			then link the _tmp and lhs
			*/
			_tmp->l_child = lhs;
			lhs->parent = _tmp;
		}
	}
	void rotate_right(node *lhs)
	{
		if (lhs)
		{
			node *_tmp = lhs->l_child;
			lhs->l_child = _tmp->r_child;
			if (_tmp->r_child){
				_tmp->r_child->parent = lhs;
			}
			//find the _tmp's parent
			_tmp->parent = lhs->parent;

			//find the which child of the parent;
			if (!lhs->parent)
			{
				root = _tmp;
			}
			else if (lhs->parent->l_child = lhs)
			{
				lhs->parent->l_child = _tmp;
			}
			else
			{
				lhs->parent->r_child = _tmp;
			}
			//find lhs's parent and 
			_tmp->r_child = lhs;
			lhs->parent = _tmp;
		}
	}

	void insert(value_type lhs)
	{
		node *tmp = create_node(lhs);
		node *rbt_node = root;
		node *_cur_node = nullptr;
		while (rbt_node){
			_cur_node = rbt_node;
			if (rbt_node->data > lhs)
			{
				rbt_node = rbt_node->l_child;
			}
			else{
				rbt_node = rbt_node->r_child;
			}
		}
		tmp->parent = _cur_node;
		if (_cur_node == nullptr){
			root = tmp;
		}
		else if (_cur_node->data > lhs){
			_cur_node->l_child = tmp;
		}
		else{
			_cur_node->r_child = tmp;
		}
		insert_update(tmp);
	}
	void insert_updata(node *lhs)
	{
		while (lhs->parent->color == red)
		{
			if (lhs->parent == lhs->parent->parent->l_child){
				//here record the lhs's parent's parent's rchild;
				//and tmp is the uncle

				node *uncle = lhs->parent->parent->r_child;

				if (uncle->color == red)
				{
					lhs->parent->color = black;
					lhs->parent->parent->color = red;
					uncle->color = black;
					lhs = lhs->parent->parent;
				}
				//here judge the lhs is there parent's which child

				else if (lhs->parent->r_child == lhs)
				{
					lhs = lhs->parent;
					rotate_left(lhs);
				}
				lhs->parent->color = black;
				lhs->parent->parent->color = red;
				rotate_right(lhs->parent->parent);
			}
			else if (lhs->parent == lhs->parent->parent->r_child)
			{
				node *uncle_t = lhs->parent->parent->l_child;
				if (uncle_t->color == red)
				{
					lhs->parent->color = black;
					lhs->parent->parent->color = red;
					uncle_t->color = black;
					lhs = lhs->parent->parent;
				}
				else if (lhs->parent->l_child == lhs){
					lhs->parent = lhs;
					retote_right(lhs);
				}
				lhs->parent->color = black;
				lhs->parent->parent->color = red;
				rotate_left(lhs->parent->parent);
			}
		}
		root->color = black;
	}
	//under construction
	void delete_node(node *lhs)
	{

	}
	//under construction
	
	void delete_update(node *lhs){

	}
private:
	node *root;
};
#endif
