//FastList.h  语音识别接口定义
//设计人：秦榛

////////////////////////////////////////////////////////////////////////////////
//FastList快速链表
////////////////////////////////////////////////////////////////////////////////
//  快速链表，用一种自定义的、采用数组代替链表的数据结构。
//说明：
//    1.快速链表用法与CList基本类似，同时可以按数组方式操作。
//    2.与CList相同，不支持数组节点。
//    3.快速链表采用数组方式按批次申请内存，加快了添加删除队列末尾结点的速度。
//    4.快速链表的结点总数不允许超过FASTLIST_MAX_COUNT。注意：超过该数目的结点
//会被自动丢弃，但只要部分结点添加成功，添加结点的函数仍然返回true。
//    5.CFastList成员对内存资源占用的主要大小为：
//        FASTLIST_MAX_ARRAY_NUM * sizeof(NODE*)
//      + m_nArrayCount * FASTLIST_MAX_ARRAY_LEN * sizeof(TYPE)
//    6.插入、删除中间节点、头节点的效率比CList慢。
//
//设计人：张祺
//修改人：秦榛，修改时间2011年6月8日
//主要修改内容：
//    1.兼容64位系统
//    2.修改了m_ppArray数据类型为m_ppArray，使系统支持更大的数组
//    3.原来删除结点时就立即释放内存，现在删除结点不释放内存
//    4.部分函数改为内联函数
//    5.修改了Find()的返回值Bug
//    6.为以下函数增加了返回值：
//      —— AddHead(CFastList<TYPE, ARG_TYPE>*)
//      —— AddTail(CFastList<TYPE, ARG_TYPE>*)
//      —— SetAt()
//      —— RemoveAt()
//    7.修改了以下函数返回值，使快速链表支持数组节点。
//      —— RemoveHead()
//      —— RemoveTail()
//    7.修改了以下函数可能越界的Bug：
//      —— AddHead(CFastList<TYPE, ARG_TYPE>*)
//      —— InsertBefore()
//      —— InsertAfter()
//    8.修改了部分命名和缩写

//------------------------------------------------------------------------------
// 不支持拷贝调用

#include "zsr_port.h"
//宏定义和结构定义
#include "assert.h"
#ifndef ASSERT
#define ASSERT assert
#endif //ASSERT

//typedef struct{} *POSITION;

#ifndef FASTLIST_MAX_ARRAY_NUM
#define FASTLIST_MAX_ARRAY_NUM   65536 //最多可以为多少个数组申请内存
#endif //FASTLIST_MAX_ARRAY_NUM

#ifndef FASTLIST_MAX_ARRAY_LEN
#define FASTLIST_MAX_ARRAY_LEN   256   //每个数组的结点个数
#endif //FASTLIST_MAX_ARRAY_LEN

#ifndef FASTLIST_MAX_COUNT
#define FASTLIST_MAX_COUNT (FASTLIST_MAX_ARRAY_LEN * FASTLIST_MAX_ARRAY_NUM)
                                        //快速链表的最大结点个数
#endif //FASTLIST_MAX_COUNT

//------------------------------------------------------------------------------
//类定义
#ifndef _FastList_
#define _FastList_

template<class TYPE, class ARG_TYPE>
class CFastList
{
protected:
    struct NODE
    {
        TYPE  Data;     //结点数据
        NODE* pNext;    //后指针
        NODE* pPrev;    //前指针
        int   nInnerID; //数组内结点序号
        int   nOuterID; //数组序号
    };

public:
    CFastList();
    ~CFastList();

protected:
    //“结点数组的数组”
    NODE** m_ppArray;

    //已申请内存的数组数目，也是下一个待申请内存的数组序号，初始值0
    int m_nArrayCount;  

    //最后一个已申请内存的数组的结点数目，也是最后一个已申请内存的数组中下一个
    //待分配的结点序号，初始值FASTLIST_MAX_ARRAY_LEN
    int m_nLastArrayElementCount;

    //快速链表的结点总数 = ( m_nArrayCount - 1 ) * FASTLIST_MAX_ARRAY_LEN
    //                     + m_nLastArrayElementCount
    //初始值0
    int m_nCount;

    //头指针，初始值NULL
    NODE* m_pHead;

    //尾指针，初始值NULL
    NODE* m_pTail;

public:
//属性------------------------------------------------------
    //结点数目
    int GetCount() const; //返回链表结点数目
    bool IsEmpty();       //返回是否空链表

    TYPE&       GetHead();          //返回头结点      
    const TYPE& GetHead() const;    //返回头结点
    TYPE&       GetTail();          //返回尾结点
    const TYPE& GetTail() const;    //返回尾结点

//操作------------------------------------------------------
    //删除头尾结点操作
    TYPE& RemoveHead();    //删除头结点，返回原头结点
    TYPE& RemoveTail();    //删除尾结点，返回原尾结点

    //添加头尾结点操作
    POSITION AddHead(ARG_TYPE Node);                    //添加头结点，返回头结点位置，失败返回NULL
    bool     AddHead(CFastList<TYPE, ARG_TYPE>* pList); //头结点前添加链表，成功返回true，失败返回false
    POSITION AddTail(ARG_TYPE Node);                    //添加尾结点，返回尾结点位置，失败返回NULL
    bool     AddTail(CFastList<TYPE, ARG_TYPE>* pList); //尾结点后添加链表，成功返回true，失败返回false

    //删除全部结点操作
    void RemoveAll();

    //用于遍历链表的操作
    POSITION    GetHeadPosition() const;              //返回头结点位置，失败返回NULL
    POSITION    GetTailPosition() const;              //返回尾结点位置，失败返回NULL
    TYPE&       GetNext(POSITION& pos);         //得到后结点
    const TYPE& GetNext(POSITION& pos) const;   //得到后结点
    TYPE&       GetPrev(POSITION& pos);         //得到前结点
    const TYPE& GetPrev(POSITION& pos) const;   //得到前结点

    //结点访问和修改操作
    TYPE&       GetAt(POSITION pos);               //获取结点值
    const TYPE& GetAt(POSITION pos) const;         //获取结点值
    TYPE&       GetAt(int nIndex);                 //获取结点值
    const TYPE& GetAt(int nIndex) const;           //获取结点值
    TYPE&       operator[](int nIndex);            //获取结点值
    const TYPE& operator[](int nIndex) const;      //获取结点值
    bool        SetAt(POSITION pos, ARG_TYPE Node);//修改指定位置的结点素值
    bool        SetAt(int nIndex, ARG_TYPE Node);  //修改指定位置的结点素值
    bool        RemoveAt(POSITION pos);            //删除指定位置的结点
    bool        RemoveAt(int nIndex);              //删除指定位置的结点

    //插入操作
    POSITION InsertBefore(POSITION pos, ARG_TYPE Node); //在pos前插入Node，失败返回NULL
    POSITION InsertBefore(int nIndex  , ARG_TYPE Node); //在nIndex前插入Node，失败返回NULL
    POSITION InsertAfter (POSITION pos, ARG_TYPE Node); //在pos后插入Node，失败返回NULL
    POSITION InsertAfter (int nIndex  , ARG_TYPE Node); //在nIndex后插入Node，失败返回NULL

    //查找操作
    POSITION Find(ARG_TYPE Node, POSITION pos); //在pos后查找Node，未找到或失败返回NULL
    POSITION Find(ARG_TYPE Node, int nIndex0);  //在nIndex后查找Node，未找到或失败返回NULL
    POSITION FindIndex(int nIndex);             //找第nIndex个结点的位置，未找到或失败返回NULL
};

//------------------------------------------------------------------------------
//类实现
template<class TYPE, class ARG_TYPE>
CFastList<TYPE, ARG_TYPE>::CFastList()
{
    //初始化结点
    m_ppArray = NULL;
    //m_ppArray = new NODE*[FASTLIST_MAX_ARRAY_NUM];
	m_ppArray = (NODE**)GlobalAlloc(GMEM_FIXED, sizeof(NODE*)*FASTLIST_MAX_ARRAY_NUM);
    if (m_ppArray != NULL)
    {
        for (int i = 0; i < FASTLIST_MAX_ARRAY_NUM; i++)
        {
            m_ppArray[i] = NULL; 
        }
    }

    //初始化链表状态
    m_nArrayCount = 0;
    m_nLastArrayElementCount = FASTLIST_MAX_ARRAY_LEN;
    m_nCount = 0;
    m_pHead = NULL;
    m_pTail = NULL;
}

template<class TYPE, class ARG_TYPE>
CFastList<TYPE, ARG_TYPE>::~CFastList()
{
    RemoveAll();
	GlobalFree( /*(HGLOBAL)*/m_ppArray );
	m_ppArray = NULL;
    ASSERT(m_nCount == 0);
}

template<class TYPE, class ARG_TYPE>
inline int CFastList<TYPE, ARG_TYPE>::GetCount() const
{
    return m_nCount;
}

template<class TYPE, class ARG_TYPE>
inline bool CFastList<TYPE, ARG_TYPE>::IsEmpty()
{
    return (m_nCount == 0);
}

template<class TYPE, class ARG_TYPE>
inline TYPE& CFastList<TYPE, ARG_TYPE>::GetHead()
{
    ASSERT(m_ppArray != NULL && m_ppArray[0] != NULL);
    return m_ppArray[0][0].Data;
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& CFastList<TYPE, ARG_TYPE>::GetHead() const
{
    ASSERT(m_ppArray != NULL && m_ppArray[0] != NULL);
    return m_ppArray[0][0].Data;
}

template<class TYPE, class ARG_TYPE>
inline TYPE& CFastList<TYPE, ARG_TYPE>::GetTail()
{
    ASSERT(m_ppArray != NULL && m_ppArray[m_nArrayCount - 1] != NULL);
    return m_ppArray[m_nArrayCount - 1][m_nLastArrayElementCount - 1].Data;
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& CFastList<TYPE, ARG_TYPE>::GetTail() const
{
    ASSERT(m_ppArray != NULL && m_ppArray[m_nArrayCount - 1] != NULL);
    return m_ppArray[m_nArrayCount - 1][m_nLastArrayElementCount - 1].Data;
}

template<class TYPE, class ARG_TYPE>
TYPE& CFastList<TYPE, ARG_TYPE>::RemoveHead()
{
    ASSERT(m_ppArray != NULL && m_ppArray[0] != NULL);

    //复制头结点
    TYPE HeadNode = m_ppArray[0][0].Data;    

    //所有结点向前移
    NODE* p = m_ppArray[0];
    while (p->pNext != NULL)
    {
        p->Data = p->pNext->Data;
        p = p->pNext;
    }

    //改变尾结点指针
    if (m_pTail != m_pHead)
    {
        m_pTail = m_pTail->pPrev;
        m_pTail->pNext = NULL;
    }
    else
    {
        //如删除后链表为空，需将头尾指针置空
        m_pHead = NULL;
        m_pTail = NULL;
    }

    //改变计数器
    m_nCount--;
    m_nLastArrayElementCount--;
    if (m_nLastArrayElementCount == 0)//如果最后一个数组为空
    {
        m_nArrayCount--;
        m_nLastArrayElementCount = FASTLIST_MAX_ARRAY_LEN;
    }

    //返回头结点
    return HeadNode;
}

template<class TYPE, class ARG_TYPE>
TYPE& CFastList<TYPE, ARG_TYPE>::RemoveTail()
{
    ASSERT(m_ppArray != NULL && m_ppArray[0] != NULL);

    //复制尾结点值
    TYPE TailNode =
        m_ppArray[m_nArrayCount - 1][m_nLastArrayElementCount - 1].Data;

    //改变尾结点指针
    if (m_pTail != m_pHead)
    {
        m_pTail = m_pTail->pPrev;
        m_pTail->pNext = NULL;
    }
    else
    {
        //如删除后链表为空，需将头尾指针置空
        m_pHead = NULL;
        m_pTail = NULL;
    }

    //改变计数器
    m_nCount--;
    m_nLastArrayElementCount--;
    if (m_nLastArrayElementCount == 0)//如果最后一个数组为空
    {
        m_nArrayCount--;
        m_nLastArrayElementCount = FASTLIST_MAX_ARRAY_LEN;
    }

    //返回尾结点
    return TailNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::AddHead(ARG_TYPE Node)
{
    if (m_ppArray == NULL) return NULL;

    //如果链表为空，则为第一个结点及所在数组申请内存
    if (m_nCount == 0)
    {
        //为第一个结点所在数组申请内存
        if (m_ppArray[0] == NULL)
        {
            //m_ppArray[0] = new NODE[FASTLIST_MAX_ARRAY_LEN];
			m_ppArray[0] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
            if (m_ppArray[0] == NULL) return NULL;
        }

        //为第一个结点赋值
        m_ppArray[0][0].Data = Node;
        m_ppArray[0][0].pPrev = NULL;
        m_ppArray[0][0].pNext = NULL;
        m_ppArray[0][0].nInnerID = 0;
        m_ppArray[0][0].nOuterID = 0;

        //为链表状态赋值
        m_nArrayCount = 1;
        m_nLastArrayElementCount = 1;
        m_nCount = 1;
        m_pHead = m_ppArray[0];
        m_pTail = m_ppArray[0];

        //返回头指针
        return (POSITION)m_pHead;
    }

    //如果已申请内存空间的数组用满，需要开辟新数组
    if (m_nLastArrayElementCount == FASTLIST_MAX_ARRAY_LEN)
    {
        //开辟新数组
        if (m_nArrayCount == FASTLIST_MAX_ARRAY_NUM) return NULL;//数组已用完
        if (m_ppArray[m_nArrayCount] == NULL)    //如果已申请内存，则不再申请
        {
            //m_ppArray[m_nArrayCount] = new NODE[FASTLIST_MAX_ARRAY_LEN];
			m_ppArray[0] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
            if (m_ppArray[m_nArrayCount] == NULL) return NULL;
        }

        //修改链表状态
        m_nArrayCount++;
        m_nLastArrayElementCount = 0;
    }

    //尾部添加一个新尾结点
    {
        //原尾结点的后指针 指向 新尾结点
        int nLastArrayID = m_nArrayCount - 1;
        m_pTail->pNext = m_ppArray[nLastArrayID] + m_nLastArrayElementCount;

        //新尾结点的前指针 指向原尾结点
        m_ppArray[nLastArrayID][m_nLastArrayElementCount].pPrev = m_pTail;

        //修改尾指针
        m_pTail = m_pTail->pNext;

        //修改新尾结点
        m_pTail->pNext = NULL;
        m_pTail->nOuterID = nLastArrayID;
        m_pTail->nInnerID = m_nLastArrayElementCount;

        //修改链表状态
        m_nLastArrayElementCount++;
        m_nCount++;
    }

    //将所有结点后移
    NODE* p = m_pTail;
    while(p->pPrev != NULL)
    {
        p->Data = p->pPrev->Data;
        p = p->pPrev;
    }

    //头结点赋值
    m_pHead->Data = Node;

    //返回头指针
    return (POSITION)m_pHead;
}

template<class TYPE, class ARG_TYPE>
bool CFastList<TYPE, ARG_TYPE>::AddHead(CFastList<TYPE, ARG_TYPE>* pList)
{
    //参数检查
    if (m_ppArray == NULL ||
        pList == NULL ||
        pList->m_pHead == NULL ||
        pList->GetCount() <= 0)
    {
        return false;
    }

    //增加链表
    int m, n, i, j;
    m = pList->GetCount();
    n = GetCount();
    int nTotal = m + n;
    if (nTotal > FASTLIST_MAX_COUNT)
    {
        m = FASTLIST_MAX_COUNT - n;
    }
    if (m > n)
    {
        j = m - n;
        for (i = 0; i < j; i++)
        {
            if (AddTail(pList->GetAt(n + i)) == NULL) return false;
        }
        for (i = 0; i < n; i++)
        {
            if (AddTail(GetAt(i)) == NULL) return false;
            if (!SetAt(i, pList->GetAt(i))) return false;
        }
    }
    else
    {
        j = n - m;
        for (i = 0; i < m; i++)
        {
            if (AddTail(GetAt(j + i)) == NULL) return false;
        }
        for (i = j - 1; i >= 0; i--)
        {
            if (!SetAt(m + i, GetAt(i))) return false;
        }
        for (i = 0; i < m; i++)
        {
            if (!SetAt(i, pList->GetAt(i))) return false;
        }
    }
    return true;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::AddTail(ARG_TYPE Node)
{
    if (m_ppArray == NULL) return NULL;

    //如果链表为空，则为第一个结点及所在数组申请内存
    if (m_nCount == 0)
    {
        //为第一个结点所在数组申请内存
        if (m_ppArray[0] == NULL)
        {
            //m_ppArray[0] = new NODE[FASTLIST_MAX_ARRAY_LEN];
			m_ppArray[0] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
            if (m_ppArray[0] == NULL) return NULL;
        }

        //为第一个结点赋值
        m_ppArray[0][0].Data = Node;
        m_ppArray[0][0].pPrev = NULL;
        m_ppArray[0][0].pNext = NULL;
        m_ppArray[0][0].nInnerID = 0;
        m_ppArray[0][0].nOuterID = 0;

        //为链表状态赋值
        m_nArrayCount = 1;
        m_nLastArrayElementCount = 1;
        m_nCount = 1;
        m_pHead = m_ppArray[0];
        m_pTail = m_ppArray[0];

        //返回头指针
        return (POSITION)m_pHead;
    }

    //如果已申请内存空间的数组用满，需要开辟新数组
    if (m_nLastArrayElementCount == FASTLIST_MAX_ARRAY_LEN)
    {
        //开辟新数组
        if (m_nArrayCount == FASTLIST_MAX_ARRAY_NUM) return NULL;//数组已用完
        if (m_ppArray[m_nArrayCount] == NULL)    //如果已申请内存，则不再申请
        {
            //m_ppArray[m_nArrayCount] = new NODE[FASTLIST_MAX_ARRAY_LEN];
			//m_ppArray[0] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
			m_ppArray[m_nArrayCount] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
           if (m_ppArray[m_nArrayCount] == NULL) return NULL;
        }

        //修改链表状态
        m_nArrayCount++;
        m_nLastArrayElementCount = 0;
    }

    //尾部添加一个新尾结点
    {
        //原尾结点的后指针 指向 新尾结点
        int nLastArrayID = m_nArrayCount - 1;
        m_pTail->pNext = m_ppArray[nLastArrayID] + m_nLastArrayElementCount;

        //新尾结点的前指针 指向原尾结点
        m_ppArray[nLastArrayID][m_nLastArrayElementCount].pPrev = m_pTail;

        //修改尾指针
        m_pTail = m_pTail->pNext;

        //修改新尾结点
        m_pTail->pNext = NULL;
        m_pTail->nOuterID = nLastArrayID;
        m_pTail->nInnerID = m_nLastArrayElementCount;

        //修改链表状态
        m_nLastArrayElementCount++;
        m_nCount++;
    }

    //尾结点赋值
    m_pTail->Data = Node;

    //返回尾指针
    return (POSITION) m_pTail;
}

template<class TYPE, class ARG_TYPE>
bool CFastList<TYPE, ARG_TYPE>::AddTail(CFastList<TYPE, ARG_TYPE>* pList)
{
    //参数检查
    if (m_ppArray == NULL ||
        pList == NULL ||
        pList->m_pHead == NULL)
    {
        return false;
    }

    //参数检查
    NODE* p = pList->m_pHead;
    while (p != NULL)
    {
        if (AddTail(p->Data) == NULL) return false;
        p = p->pNext;
    }
    return true;
}

template<class TYPE, class ARG_TYPE>
void CFastList<TYPE, ARG_TYPE>::RemoveAll()
{
    //释放结点
    if (m_ppArray != NULL)
    {
        for (int i = 0; i < FASTLIST_MAX_ARRAY_NUM; i ++)
        {
            if (m_ppArray[i] != NULL)
            {
                //delete []m_ppArray[i];
				GlobalFree( /*(HGLOBAL)*/m_ppArray[i] );
                m_ppArray[i] = NULL; 
            }
        }
        //delete []m_ppArray;
		//GlobalFree( /*(HGLOBAL)*/m_ppArray );
        //m_ppArray = NULL;
    }

    //初始化链表状态
    m_nArrayCount = 0;
    m_nLastArrayElementCount = FASTLIST_MAX_ARRAY_LEN;
    m_nCount = 0;
    m_pHead = NULL;
    m_pTail = NULL;
}

template<class TYPE, class ARG_TYPE>
inline POSITION CFastList<TYPE, ARG_TYPE>::GetHeadPosition() const
{
    if (m_ppArray == NULL) return NULL;
    return (POSITION)m_pHead;
}

template<class TYPE, class ARG_TYPE>
inline POSITION CFastList<TYPE, ARG_TYPE>::GetTailPosition() const
{
    if (m_ppArray == NULL) return NULL;
    return (POSITION)m_pTail;
}

template<class TYPE, class ARG_TYPE>
inline TYPE & CFastList<TYPE, ARG_TYPE>::GetNext(POSITION& pos)
{
    ASSERT(m_ppArray != NULL);
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    pos = (POSITION)p->pNext;
    return p->Data;
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& CFastList<TYPE, ARG_TYPE>::GetNext(POSITION& pos) const
{
    ASSERT(m_ppArray != NULL);
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    pos = (POSITION)p->pNext;
    return p->Data;
}

template<class TYPE, class ARG_TYPE>
inline TYPE & CFastList<TYPE, ARG_TYPE>::GetPrev(POSITION& pos)
{
    ASSERT(m_ppArray != NULL);
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    pos = (POSITION) p->pPrev;
    return p->Data;
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& CFastList<TYPE, ARG_TYPE>::GetPrev(POSITION& pos) const
{
    ASSERT(m_ppArray != NULL);
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    pos = (POSITION) p->pPrev;
    return p->Data;
}

template<class TYPE, class ARG_TYPE>
inline TYPE& CFastList<TYPE, ARG_TYPE>::GetAt(POSITION pos)
{
    ASSERT(m_ppArray != NULL);
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    return p->Data;
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& CFastList<TYPE, ARG_TYPE>::GetAt(POSITION pos) const
{
    ASSERT(m_ppArray != NULL);
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    return p->Data;
}

template<class TYPE, class ARG_TYPE>
TYPE& CFastList<TYPE, ARG_TYPE>::GetAt(int nIndex)
{
    ASSERT(m_ppArray != NULL);
    int i = nIndex / FASTLIST_MAX_ARRAY_LEN;
    int j = nIndex % FASTLIST_MAX_ARRAY_LEN;
    ASSERT((nIndex < m_nCount) && 
        (m_ppArray[i][j].nOuterID == i) && 
        (m_ppArray[i][j].nInnerID == j));
    return m_ppArray[i][j].Data;
}

template<class TYPE, class ARG_TYPE>
const TYPE& CFastList<TYPE, ARG_TYPE>::GetAt(int nIndex) const
{
    ASSERT(m_ppArray != NULL);
    int i = nIndex / FASTLIST_MAX_ARRAY_LEN;
    int j = nIndex % FASTLIST_MAX_ARRAY_LEN;
    ASSERT((nIndex < m_nCount) && 
        (m_ppArray[i][j].nOuterID == i) && 
        (m_ppArray[i][j].nInnerID == j));
    return m_ppArray[i][j].Data;
}

template<class TYPE, class ARG_TYPE>
inline TYPE& CFastList<TYPE, ARG_TYPE>::operator[](int nIndex)
{
    ASSERT(m_ppArray != NULL);
    return GetAt(nIndex);
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& CFastList<TYPE, ARG_TYPE>::operator[](int nIndex) const
{
    ASSERT(m_ppArray != NULL);
    return GetAt(nIndex);
}

template<class TYPE, class ARG_TYPE>
bool CFastList<TYPE, ARG_TYPE>::SetAt(POSITION pos, ARG_TYPE Node)
{
    if (m_ppArray == NULL) return false;
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    p->Data = Node;
    return true;
}

template<class TYPE, class ARG_TYPE>
bool CFastList<TYPE, ARG_TYPE>::SetAt(int nIndex, ARG_TYPE Node)
{
    if (m_ppArray == NULL || nIndex >= m_nCount) return false;
    int i = nIndex / FASTLIST_MAX_ARRAY_LEN;
    int j = nIndex % FASTLIST_MAX_ARRAY_LEN;
    m_ppArray[i][j].Data = Node;
    return true;
}

template<class TYPE, class ARG_TYPE>
bool CFastList<TYPE, ARG_TYPE>::RemoveAt(POSITION pos)
{
    if (m_ppArray == NULL) return false;
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    while(p->pNext != NULL)
    {
        p->Data = p->pNext->Data;
        p = p->pNext;
    }
    RemoveTail();
    return true;
}

template<class TYPE, class ARG_TYPE>
bool CFastList<TYPE, ARG_TYPE>::RemoveAt(int nIndex)
{
    if (m_ppArray == NULL || nIndex >= m_nCount) return false;
    int i = nIndex / FASTLIST_MAX_ARRAY_LEN;
    int j = nIndex % FASTLIST_MAX_ARRAY_LEN;
    NODE* p = m_ppArray[i] + j;
    while(p->pNext != NULL)
    {
        p->Data = p->pNext->Data;
        p = p->pNext;
    }
    RemoveTail();
    return true;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::InsertBefore(POSITION pos, ARG_TYPE Node)
{
    if (m_ppArray == NULL) return NULL;
    NODE* p = (NODE*)pos;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    if (AddTail(m_pTail->Data) == NULL) return NULL;
    NODE* p1 = m_pTail->pPrev;
    while (p1 != p)
    {
        p1->Data = p1->pPrev->Data;
        p1 = p1->pPrev;
    }
    p->Data = Node;
    return (POSITION)p;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::InsertBefore(int nIndex, ARG_TYPE Node)
{
    if (m_ppArray == NULL || nIndex >= m_nCount) return NULL;
    int i = nIndex / FASTLIST_MAX_ARRAY_LEN;
    int j = nIndex % FASTLIST_MAX_ARRAY_LEN;
    if (AddTail(m_pTail->Data) == NULL) return NULL;
    NODE* p = m_ppArray[i] + j;
    NODE* p1 = m_pTail->pPrev;
    while (p1 != p)
    {
        p1->Data = p1->pPrev->Data;
        p1 = p1->pPrev;
    }
    p->Data = Node;
    return (POSITION)p;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::InsertAfter(POSITION pos, ARG_TYPE Node)
{
    if (m_ppArray == NULL) return NULL;
    NODE* p = (NODE*)pos;
    ASSERT(AfxIsValidAddress(p, sizeof(Node)));
    p = p->pNext;
    if (AddTail(m_pTail->Data) == NULL) return NULL;
    NODE* p1 = m_pTail->pPrev;
    while (p1 != p)
    {
        p1->Data = p1->pPrev->Data;
        p1 = p1->pPrev;
    }
    p->Data = Node;
    return (POSITION)p;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::InsertAfter(int nIndex, ARG_TYPE Node)
{
    if (m_ppArray == NULL || nIndex >= m_nCount) return NULL;
    nIndex++;
    int i = nIndex / FASTLIST_MAX_ARRAY_LEN;
    int j = nIndex % FASTLIST_MAX_ARRAY_LEN;
    if (AddTail(m_pTail->Data) == NULL) return NULL;
    NODE* p = m_ppArray[i] + j;
    NODE* p1 = m_pTail;
    while (p1 != p)
    {
        p1->Data = p1->pPrev->Data;
        p1 = p1->pPrev;
    }
    p->Data = Node;
    return (POSITION)p;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::Find(ARG_TYPE Node, POSITION pos)
{
    if (m_ppArray == NULL) return NULL;
    NODE* p = (NODE*)pos;
    if (p == NULL) p = m_pHead;
    //ASSERT(AfxIsValidAddress(p, sizeof(NODE)));
    while (p != NULL)
    {
        if (p->Data == Node) return (POSITION)p;
        p = p->pNext;
    }
    return NULL;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::Find(ARG_TYPE Node, int nIndex)
{
    if (m_ppArray == NULL || nIndex >= m_nCount) return NULL;
    int i = nIndex / FASTLIST_MAX_ARRAY_LEN;
    int j = nIndex % FASTLIST_MAX_ARRAY_LEN;
    NODE* p = m_ppArray[i] + j;
    while (p != NULL)
    {
        if (p->Data == Node) return (POSITION)p;
        p = p->pNext;
    }
    return NULL;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::FindIndex(int nIndex)
{
    if (m_ppArray == NULL || nIndex >= m_nCount) return NULL;
    int i = nIndex / FASTLIST_MAX_ARRAY_LEN;
    int j = nIndex % FASTLIST_MAX_ARRAY_LEN;
    NODE* p = m_ppArray[i] + j;
    return (POSITION)p;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ZSR's work: add some tools to extend functionality.

#include <list>
template<typename TYPE, typename ARG_TYPE>
void cfastlist_sort(CFastList<TYPE, ARG_TYPE> &cli)
{
	int cnt = cli.GetCount();
	std::list<TYPE> tmpLi;
	for (POSITION po = cli.GetHeadPosition(); po != NULL;){
		tmpLi.push_back(cli.GetNext(po));
	}
	tmpLi.sort();
	POSITION po = cli.GetHeadPosition();
	for (std::list<TYPE>::iterator it = tmpLi.begin(); it != tmpLi.end(); it++){
		cli.SetAt(po, *it);
		cli.GetNext(po);
	}
}

template<typename TYPE, typename ARG_TYPE, typename Compare>
void cfastlist_sort(CFastList<TYPE, ARG_TYPE> &cli, Compare comp)
{
	int cnt = cli.GetCount();
	std::list<TYPE> tmpLi;
	for (POSITION po = cli.GetHeadPosition(); po != NULL;){
		tmpLi.push_back(cli.GetNext(po));
	}
	tmpLi.sort(comp);
	POSITION po = cli.GetHeadPosition();
	for (std::list<TYPE>::iterator it = tmpLi.begin(); it != tmpLi.end(); it++){
		cli.SetAt(po, *it);
		cli.GetNext(po);
	}
}

template<typename TYPE, typename ARG_TYPE, typename Compare>
void cfastlist_sort_copy(const CFastList<TYPE, ARG_TYPE> &cli, CFastList<TYPE, ARG_TYPE> &desli, Compare comp)
{
	int cnt = cli.GetCount();
	std::list<TYPE> tmpLi;
	for (POSITION po = cli.GetHeadPosition(); po != NULL;){
		tmpLi.push_back(cli.GetNext(po));
	}
	tmpLi.sort(comp);

	for (std::list<TYPE>::iterator it = tmpLi.begin(); it != tmpLi.end(); it++){
		desli.AddTail(*it);
	}
}
#endif //_FastList_
