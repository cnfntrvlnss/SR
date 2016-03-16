#ifndef CFASTLIST_H
#define CFASTLIST_H

#include <afxtempl.h>
#define ZSR_MOCK
#ifdef ZSR_MOCK
#define CFastList CList
#else
//快速链表：是一种自定义的、为提高链表结点内存申请和释放效率的、采用数组代替链表的数据结构。
//宏定义和结构定义 
#define ASSERT assert #define FASTLIST_MAX_ARRAY_NUM 65536 
//最多可以为多少个数组申请内存 
#define FASTLIST_MAX_ARRAY_LEN 256 
//每个数组的结点个数 
#define FASTLIST_MAX_COUNT (FASTLIST_MAX_ARRAY_LEN * FASTLIST_MAX_ARRAY_NUM) 
//快速链表的最大结点个数 
template<class TYPE, class ARG_TYPE> 
class CFastList 
{ 
public:
	int GetCount() const; //返回链表结点数目 
	bool IsEmpty(); //返回是否空链表 
	TYPE& GetHead(); 
	//返回头结点 
	const TYPE& GetHead() const; //返回头结点 
	TYPE& GetTail(); //返回尾结点 
	const TYPE& GetTail() const; //返回尾结点 
	TYPE& RemoveHead(); //删除头结点，返回原头结点 
	TYPE& RemoveTail(); //删除尾结点，返回原尾结点 
	POSITION AddHead(ARG_TYPE Node); //添加头结点，返回头结点位置，失败返回NULL 
	bool AddHead(CFastList<TYPE, ARG_TYPE>* pList); //头结点前添加链表，成功返回true，失败返回false 
	POSITION AddTail(ARG_TYPE Node); //添加尾结点，返回尾结点位置，失败返回NULL 
	bool AddTail(CFastList<TYPE, ARG_TYPE>* pList); //尾结点后添加链表，成功返回true，失败返回false 
	void RemoveAll();//删除全部结点操作 POSITION GetHeadPosition(); //返回头结点位置，失败返回NULL 
	POSITION GetTailPosition(); //返回尾结点位置，失败返回NULL TYPE& GetNext(POSITION& pos); //得到后结点 
	const TYPE& GetNext(POSITION& pos) const; //得到后结点 TYPE& GetPrev(POSITION& pos); //得到前结点 
	const TYPE& GetPrev(POSITION& pos) const; //得到前结点 TYPE& GetAt(POSITION pos); //获取结点值 
	const TYPE& GetAt(POSITION pos) const; //获取结点值 TYPE& GetAt(int nIndex); //获取结点值 
	const TYPE& GetAt(int nIndex) const; //获取结点值 TYPE& operator[](int nIndex); //获取结点值
	const TYPE& operator[](int nIndex) const; //获取结点值 
	bool SetAt(POSITION pos, ARG_TYPE Node);//修改指定位置的结点素值 
	bool SetAt(int nIndex, ARG_TYPE Node); //修改指定位置的结点素值 
	bool RemoveAt(POSITION pos); //删除指定位置的结点 
	bool RemoveAt(int nIndex); //删除指定位置的结点 
	POSITION InsertBefore(POSITION pos, ARG_TYPE Node); //在pos前插入Node，失败返回NULL 
	POSITION InsertBefore(int nIndex , ARG_TYPE Node); //在nIndex前插入Node，失败返回NULL 
	POSITION InsertAfter (POSITION pos, ARG_TYPE Node); //在pos后插入Node，失败返回NULL 
	POSITION InsertAfter (int nIndex , ARG_TYPE Node); //在nIndex后插入Node，失败返回NULL 
	POSITION Find(ARG_TYPE Node, POSITION pos); //在pos后查找Node，未找到或失败返回NULL 
	POSITION Find(ARG_TYPE Node, int nIndex0); //在nIndex后查找Node，未找到或失败返回NULL
	POSITION FindIndex(int nIndex); // 找第nIndex个结点的位置，未找到或失败返回NULL

	//missings compared with CList
	POSITION &GetHeadPosition();
};
#endif // ZSR_MORK

#endif // CFASTLIST_H