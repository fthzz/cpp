#include <iostream>
using namespace std;
#include <assert.h>
#include <vector>
#include <time.h>

/*红黑树需要满足的四个条件：
1.左<中<右
2.根节点和叶子节点都是黑色，且叶子节点是空节点，不存储数据
3.不存在连续相连的两个红色节点
4.任意一条路径从根节点到叶子节点的黑色节点个数相同
*/

/*性质
1.所有红黑树左右子树的高度不会相差两倍，这是由条件决定的
2.AVL树查询效率更高，红黑树在插入删除上效率更高
*/


enum Colour
{
	RED,
	BLACK
};
template<typename K, typename V> //这里定义模板，在输入的时候就可以输入任意类型的变量了

class RBTreeNode
{
public:
	RBTreeNode(const std::pair<K, V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_col(RED)
	{

	}
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	std::pair<K, V> _kv;
	Colour _col;
};



template<typename K, typename V>
class RBTree
{
public:
    typedef RBTreeNode<K, V> Node;  //为上一个类起一个别名，方便使用
	RBTree()
		:_root(nullptr)
	{
 
	}

    //插入
	bool insert(const std::pair<K,V> &kv)
	{
		//如果是空树，变为根节点，设置为黑色（默认是红）
        if (_root == nullptr)
		{
			_root = new Node(kv); //根节点
			_root->_col = BLACK;
			return true;
		}

        //遍历二叉树，查找该输入值需要插入的位置，寻找它的父节点指针
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}//得到parent指针


		//初始化输入节点
		cur = new Node(kv);
		cur->_col = RED;
		if (kv.first > parent->_kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}


		//控制平衡，检查是否破坏了红黑树平衡
        //cur表示当前节点  parent父节点  grandfather祖父节点（父节点的父节点）  uncle父节点的同层兄弟节点
		while (parent != nullptr && parent->_col == RED)  //如果父亲存在并且父亲的节点为红色
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//情况1 ：叔叔节点存在且叔叔节点颜色为红
				if (uncle != nullptr && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;  //父亲节点和叔叔节点变黑
					grandfather->_col = RED;
					
					//grandfather可能不是根节点，继续往上更新
					cur = grandfather;
					parent = cur->_parent;
				}
				else //情况2 + 3，uncle不存在 / 存在且为黑    可能是由情况1 -> 情况2 / 情况 3
				{
					//        g
					//      p
					//    c
					if (cur == parent->_left)   
					{
						//右单旋
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//触发左右双旋
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//情况1： uncle 存在且 uncle的颜色为红
				if (uncle != nullptr && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;  //叔叔和父亲变色
					grandfather->_col = RED;
 
					//grandfather可能不是根节点，所以可能一直往上更新
					cur = grandfather;
					parent = cur->_parent;
				}
				else  //情况2 + 3 ，uncle不存在 / 存在且为黑
				{
					if (cur == parent->_right)  //触发左旋
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else  
					{
						//触发右左双旋
						RotateR(parent);
						RotateL(grandfather);
						grandfather->_col = RED;
						cur->_col = BLACK;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

private:
	Node* _root;

private:
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentparent = parent->_parent;
 
		parent->_left = subLR;
		if (subLR != nullptr)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;
		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parentparent->_left == parent)
				parentparent->_left = subL;
			else
				parentparent->_right = subL;
			subL->_parent = parentparent;
		}
	}
	void RotateL(Node* parent)
	{
		
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* parentparent = parent->_parent;
 
		parent->_right = subRL;
		if (subRL != nullptr)
			subRL->_parent = parent;
 
		subR->_left = parent;
		parent->_parent = subR;
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parentparent->_left == parent)
				parentparent->_left = subR;
			else
				parentparent->_right = subR;
 
			subR->_parent = parentparent;
		}
	}
public:
    //红黑树检验分为两步：第一步判断是否是二叉搜索树，第二部判断是否是红黑树
	void inoder()//中序遍历检验
	{
		Node* cur = _root;
		Node* MostRight = nullptr;
		while (cur != nullptr)
		{
			MostRight = cur->_left;
			if (MostRight != nullptr)
			{
				while (MostRight->_right != nullptr && MostRight->_right != cur)
				{
					MostRight = MostRight->_right;
				}
				if (MostRight->_right == nullptr)
				{
					MostRight->_right = cur;
					cur = cur->_left;
					continue;
				}
				else
				{
					MostRight->_right = nullptr;
				}
			}
			std::cout << cur->_kv.first << ":" << cur->_kv.second << std::endl;
			cur = cur->_right;
		}
	}

	bool IsBalance()
	{
		if (_root && _root->_col == RED)
		{
			std::cout << "根节点不是黑色" << std::endl;
			return false;
		}
 
		// 最左路径黑色节点数量做基准值
		int banchmark = 0;
		Node* left = _root;
		while (left)
		{
			if (left->_col == BLACK)
				++banchmark;
 
			left = left->_left;
		}
 
		int blackNum = 0;
		return _IsBalance(_root, banchmark, blackNum);
	}
 
	bool _IsBalance(Node* root, int banchmark, int blackNum)
	{
		if (root == nullptr)
		{
			if (banchmark != blackNum)
			{
				std::cout << "存在路径黑色节点的数量不相等" << std::endl;
				return false;
			}
 
			return true;
		}
 
		if (root->_col == RED && root->_parent->_col == RED)
		{
			std::cout << "出现连续红色节点" << std::endl;
			return false;
		}
 
		if (root->_col == BLACK)
		{
			++blackNum;
		}
 
		return _IsBalance(root->_left, banchmark, blackNum)
			&& _IsBalance(root->_right, banchmark, blackNum);
	}
};

//测试代码
void RBTreeTest(void)
{
	RBTree<int, int> rb;
	int array[] = { 9,6,4,3,7,3,2,0,544,43224,23,423,42,4234,2,4242,423,42,7,11,98,5 };
	for (const auto& e : array)
	{
		rb.insert(std::pair<int, int>(e, e));
		std::cout << rb.IsBalance() << std::endl;
	}
	rb.inoder();
}


int main()
{
	//AVLTreeTest();
	RBTreeTest();
}

