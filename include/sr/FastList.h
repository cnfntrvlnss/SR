//FastList.h  ����ʶ��ӿڶ���
//����ˣ����

////////////////////////////////////////////////////////////////////////////////
//FastList��������
////////////////////////////////////////////////////////////////////////////////
//  ����������һ���Զ���ġ��������������������ݽṹ��
//˵����
//    1.���������÷���CList�������ƣ�ͬʱ���԰����鷽ʽ������
//    2.��CList��ͬ����֧������ڵ㡣
//    3.��������������鷽ʽ�����������ڴ棬�ӿ������ɾ������ĩβ�����ٶȡ�
//    4.��������Ľ��������������FASTLIST_MAX_COUNT��ע�⣺��������Ŀ�Ľ��
//�ᱻ�Զ���������ֻҪ���ֽ����ӳɹ�����ӽ��ĺ�����Ȼ����true��
//    5.CFastList��Ա���ڴ���Դռ�õ���Ҫ��СΪ��
//        FASTLIST_MAX_ARRAY_NUM * sizeof(NODE*)
//      + m_nArrayCount * FASTLIST_MAX_ARRAY_LEN * sizeof(TYPE)
//    6.���롢ɾ���м�ڵ㡢ͷ�ڵ��Ч�ʱ�CList����
//
//����ˣ�����
//�޸��ˣ���黣��޸�ʱ��2011��6��8��
//��Ҫ�޸����ݣ�
//    1.����64λϵͳ
//    2.�޸���m_ppArray��������Ϊm_ppArray��ʹϵͳ֧�ָ��������
//    3.ԭ��ɾ�����ʱ�������ͷ��ڴ棬����ɾ����㲻�ͷ��ڴ�
//    4.���ֺ�����Ϊ��������
//    5.�޸���Find()�ķ���ֵBug
//    6.Ϊ���º��������˷���ֵ��
//      ���� AddHead(CFastList<TYPE, ARG_TYPE>*)
//      ���� AddTail(CFastList<TYPE, ARG_TYPE>*)
//      ���� SetAt()
//      ���� RemoveAt()
//    7.�޸������º�������ֵ��ʹ��������֧������ڵ㡣
//      ���� RemoveHead()
//      ���� RemoveTail()
//    7.�޸������º�������Խ���Bug��
//      ���� AddHead(CFastList<TYPE, ARG_TYPE>*)
//      ���� InsertBefore()
//      ���� InsertAfter()
//    8.�޸��˲�����������д

//------------------------------------------------------------------------------
// ��֧�ֿ�������

#include "zsr_port.h"
//�궨��ͽṹ����
#include "assert.h"
#ifndef ASSERT
#define ASSERT assert
#endif //ASSERT

//typedef struct{} *POSITION;

#ifndef FASTLIST_MAX_ARRAY_NUM
#define FASTLIST_MAX_ARRAY_NUM   65536 //������Ϊ���ٸ����������ڴ�
#endif //FASTLIST_MAX_ARRAY_NUM

#ifndef FASTLIST_MAX_ARRAY_LEN
#define FASTLIST_MAX_ARRAY_LEN   256   //ÿ������Ľ�����
#endif //FASTLIST_MAX_ARRAY_LEN

#ifndef FASTLIST_MAX_COUNT
#define FASTLIST_MAX_COUNT (FASTLIST_MAX_ARRAY_LEN * FASTLIST_MAX_ARRAY_NUM)
                                        //�����������������
#endif //FASTLIST_MAX_COUNT

//------------------------------------------------------------------------------
//�ඨ��
#ifndef _FastList_
#define _FastList_

template<class TYPE, class ARG_TYPE>
class CFastList
{
protected:
    struct NODE
    {
        TYPE  Data;     //�������
        NODE* pNext;    //��ָ��
        NODE* pPrev;    //ǰָ��
        int   nInnerID; //�����ڽ�����
        int   nOuterID; //�������
    };

public:
    CFastList();
    ~CFastList();

protected:
    //�������������顱
    NODE** m_ppArray;

    //�������ڴ��������Ŀ��Ҳ����һ���������ڴ��������ţ���ʼֵ0
    int m_nArrayCount;  

    //���һ���������ڴ������Ľ����Ŀ��Ҳ�����һ���������ڴ����������һ��
    //������Ľ����ţ���ʼֵFASTLIST_MAX_ARRAY_LEN
    int m_nLastArrayElementCount;

    //��������Ľ������ = ( m_nArrayCount - 1 ) * FASTLIST_MAX_ARRAY_LEN
    //                     + m_nLastArrayElementCount
    //��ʼֵ0
    int m_nCount;

    //ͷָ�룬��ʼֵNULL
    NODE* m_pHead;

    //βָ�룬��ʼֵNULL
    NODE* m_pTail;

public:
//����------------------------------------------------------
    //�����Ŀ
    int GetCount() const; //������������Ŀ
    bool IsEmpty();       //�����Ƿ������

    TYPE&       GetHead();          //����ͷ���      
    const TYPE& GetHead() const;    //����ͷ���
    TYPE&       GetTail();          //����β���
    const TYPE& GetTail() const;    //����β���

//����------------------------------------------------------
    //ɾ��ͷβ������
    TYPE& RemoveHead();    //ɾ��ͷ��㣬����ԭͷ���
    TYPE& RemoveTail();    //ɾ��β��㣬����ԭβ���

    //���ͷβ������
    POSITION AddHead(ARG_TYPE Node);                    //���ͷ��㣬����ͷ���λ�ã�ʧ�ܷ���NULL
    bool     AddHead(CFastList<TYPE, ARG_TYPE>* pList); //ͷ���ǰ��������ɹ�����true��ʧ�ܷ���false
    POSITION AddTail(ARG_TYPE Node);                    //���β��㣬����β���λ�ã�ʧ�ܷ���NULL
    bool     AddTail(CFastList<TYPE, ARG_TYPE>* pList); //β������������ɹ�����true��ʧ�ܷ���false

    //ɾ��ȫ��������
    void RemoveAll();

    //���ڱ�������Ĳ���
    POSITION    GetHeadPosition() const;              //����ͷ���λ�ã�ʧ�ܷ���NULL
    POSITION    GetTailPosition() const;              //����β���λ�ã�ʧ�ܷ���NULL
    TYPE&       GetNext(POSITION& pos);         //�õ�����
    const TYPE& GetNext(POSITION& pos) const;   //�õ�����
    TYPE&       GetPrev(POSITION& pos);         //�õ�ǰ���
    const TYPE& GetPrev(POSITION& pos) const;   //�õ�ǰ���

    //�����ʺ��޸Ĳ���
    TYPE&       GetAt(POSITION pos);               //��ȡ���ֵ
    const TYPE& GetAt(POSITION pos) const;         //��ȡ���ֵ
    TYPE&       GetAt(int nIndex);                 //��ȡ���ֵ
    const TYPE& GetAt(int nIndex) const;           //��ȡ���ֵ
    TYPE&       operator[](int nIndex);            //��ȡ���ֵ
    const TYPE& operator[](int nIndex) const;      //��ȡ���ֵ
    bool        SetAt(POSITION pos, ARG_TYPE Node);//�޸�ָ��λ�õĽ����ֵ
    bool        SetAt(int nIndex, ARG_TYPE Node);  //�޸�ָ��λ�õĽ����ֵ
    bool        RemoveAt(POSITION pos);            //ɾ��ָ��λ�õĽ��
    bool        RemoveAt(int nIndex);              //ɾ��ָ��λ�õĽ��

    //�������
    POSITION InsertBefore(POSITION pos, ARG_TYPE Node); //��posǰ����Node��ʧ�ܷ���NULL
    POSITION InsertBefore(int nIndex  , ARG_TYPE Node); //��nIndexǰ����Node��ʧ�ܷ���NULL
    POSITION InsertAfter (POSITION pos, ARG_TYPE Node); //��pos�����Node��ʧ�ܷ���NULL
    POSITION InsertAfter (int nIndex  , ARG_TYPE Node); //��nIndex�����Node��ʧ�ܷ���NULL

    //���Ҳ���
    POSITION Find(ARG_TYPE Node, POSITION pos); //��pos�����Node��δ�ҵ���ʧ�ܷ���NULL
    POSITION Find(ARG_TYPE Node, int nIndex0);  //��nIndex�����Node��δ�ҵ���ʧ�ܷ���NULL
    POSITION FindIndex(int nIndex);             //�ҵ�nIndex������λ�ã�δ�ҵ���ʧ�ܷ���NULL
};

//------------------------------------------------------------------------------
//��ʵ��
template<class TYPE, class ARG_TYPE>
CFastList<TYPE, ARG_TYPE>::CFastList()
{
    //��ʼ�����
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

    //��ʼ������״̬
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

    //����ͷ���
    TYPE HeadNode = m_ppArray[0][0].Data;    

    //���н����ǰ��
    NODE* p = m_ppArray[0];
    while (p->pNext != NULL)
    {
        p->Data = p->pNext->Data;
        p = p->pNext;
    }

    //�ı�β���ָ��
    if (m_pTail != m_pHead)
    {
        m_pTail = m_pTail->pPrev;
        m_pTail->pNext = NULL;
    }
    else
    {
        //��ɾ��������Ϊ�գ��轫ͷβָ���ÿ�
        m_pHead = NULL;
        m_pTail = NULL;
    }

    //�ı������
    m_nCount--;
    m_nLastArrayElementCount--;
    if (m_nLastArrayElementCount == 0)//������һ������Ϊ��
    {
        m_nArrayCount--;
        m_nLastArrayElementCount = FASTLIST_MAX_ARRAY_LEN;
    }

    //����ͷ���
    return HeadNode;
}

template<class TYPE, class ARG_TYPE>
TYPE& CFastList<TYPE, ARG_TYPE>::RemoveTail()
{
    ASSERT(m_ppArray != NULL && m_ppArray[0] != NULL);

    //����β���ֵ
    TYPE TailNode =
        m_ppArray[m_nArrayCount - 1][m_nLastArrayElementCount - 1].Data;

    //�ı�β���ָ��
    if (m_pTail != m_pHead)
    {
        m_pTail = m_pTail->pPrev;
        m_pTail->pNext = NULL;
    }
    else
    {
        //��ɾ��������Ϊ�գ��轫ͷβָ���ÿ�
        m_pHead = NULL;
        m_pTail = NULL;
    }

    //�ı������
    m_nCount--;
    m_nLastArrayElementCount--;
    if (m_nLastArrayElementCount == 0)//������һ������Ϊ��
    {
        m_nArrayCount--;
        m_nLastArrayElementCount = FASTLIST_MAX_ARRAY_LEN;
    }

    //����β���
    return TailNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CFastList<TYPE, ARG_TYPE>::AddHead(ARG_TYPE Node)
{
    if (m_ppArray == NULL) return NULL;

    //�������Ϊ�գ���Ϊ��һ����㼰�������������ڴ�
    if (m_nCount == 0)
    {
        //Ϊ��һ������������������ڴ�
        if (m_ppArray[0] == NULL)
        {
            //m_ppArray[0] = new NODE[FASTLIST_MAX_ARRAY_LEN];
			m_ppArray[0] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
            if (m_ppArray[0] == NULL) return NULL;
        }

        //Ϊ��һ����㸳ֵ
        m_ppArray[0][0].Data = Node;
        m_ppArray[0][0].pPrev = NULL;
        m_ppArray[0][0].pNext = NULL;
        m_ppArray[0][0].nInnerID = 0;
        m_ppArray[0][0].nOuterID = 0;

        //Ϊ����״̬��ֵ
        m_nArrayCount = 1;
        m_nLastArrayElementCount = 1;
        m_nCount = 1;
        m_pHead = m_ppArray[0];
        m_pTail = m_ppArray[0];

        //����ͷָ��
        return (POSITION)m_pHead;
    }

    //����������ڴ�ռ��������������Ҫ����������
    if (m_nLastArrayElementCount == FASTLIST_MAX_ARRAY_LEN)
    {
        //����������
        if (m_nArrayCount == FASTLIST_MAX_ARRAY_NUM) return NULL;//����������
        if (m_ppArray[m_nArrayCount] == NULL)    //����������ڴ棬��������
        {
            //m_ppArray[m_nArrayCount] = new NODE[FASTLIST_MAX_ARRAY_LEN];
			m_ppArray[0] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
            if (m_ppArray[m_nArrayCount] == NULL) return NULL;
        }

        //�޸�����״̬
        m_nArrayCount++;
        m_nLastArrayElementCount = 0;
    }

    //β�����һ����β���
    {
        //ԭβ���ĺ�ָ�� ָ�� ��β���
        int nLastArrayID = m_nArrayCount - 1;
        m_pTail->pNext = m_ppArray[nLastArrayID] + m_nLastArrayElementCount;

        //��β����ǰָ�� ָ��ԭβ���
        m_ppArray[nLastArrayID][m_nLastArrayElementCount].pPrev = m_pTail;

        //�޸�βָ��
        m_pTail = m_pTail->pNext;

        //�޸���β���
        m_pTail->pNext = NULL;
        m_pTail->nOuterID = nLastArrayID;
        m_pTail->nInnerID = m_nLastArrayElementCount;

        //�޸�����״̬
        m_nLastArrayElementCount++;
        m_nCount++;
    }

    //�����н�����
    NODE* p = m_pTail;
    while(p->pPrev != NULL)
    {
        p->Data = p->pPrev->Data;
        p = p->pPrev;
    }

    //ͷ��㸳ֵ
    m_pHead->Data = Node;

    //����ͷָ��
    return (POSITION)m_pHead;
}

template<class TYPE, class ARG_TYPE>
bool CFastList<TYPE, ARG_TYPE>::AddHead(CFastList<TYPE, ARG_TYPE>* pList)
{
    //�������
    if (m_ppArray == NULL ||
        pList == NULL ||
        pList->m_pHead == NULL ||
        pList->GetCount() <= 0)
    {
        return false;
    }

    //��������
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

    //�������Ϊ�գ���Ϊ��һ����㼰�������������ڴ�
    if (m_nCount == 0)
    {
        //Ϊ��һ������������������ڴ�
        if (m_ppArray[0] == NULL)
        {
            //m_ppArray[0] = new NODE[FASTLIST_MAX_ARRAY_LEN];
			m_ppArray[0] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
            if (m_ppArray[0] == NULL) return NULL;
        }

        //Ϊ��һ����㸳ֵ
        m_ppArray[0][0].Data = Node;
        m_ppArray[0][0].pPrev = NULL;
        m_ppArray[0][0].pNext = NULL;
        m_ppArray[0][0].nInnerID = 0;
        m_ppArray[0][0].nOuterID = 0;

        //Ϊ����״̬��ֵ
        m_nArrayCount = 1;
        m_nLastArrayElementCount = 1;
        m_nCount = 1;
        m_pHead = m_ppArray[0];
        m_pTail = m_ppArray[0];

        //����ͷָ��
        return (POSITION)m_pHead;
    }

    //����������ڴ�ռ��������������Ҫ����������
    if (m_nLastArrayElementCount == FASTLIST_MAX_ARRAY_LEN)
    {
        //����������
        if (m_nArrayCount == FASTLIST_MAX_ARRAY_NUM) return NULL;//����������
        if (m_ppArray[m_nArrayCount] == NULL)    //����������ڴ棬��������
        {
            //m_ppArray[m_nArrayCount] = new NODE[FASTLIST_MAX_ARRAY_LEN];
			//m_ppArray[0] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
			m_ppArray[m_nArrayCount] = (NODE*)GlobalAlloc(GMEM_FIXED, sizeof(NODE)*FASTLIST_MAX_ARRAY_LEN);
           if (m_ppArray[m_nArrayCount] == NULL) return NULL;
        }

        //�޸�����״̬
        m_nArrayCount++;
        m_nLastArrayElementCount = 0;
    }

    //β�����һ����β���
    {
        //ԭβ���ĺ�ָ�� ָ�� ��β���
        int nLastArrayID = m_nArrayCount - 1;
        m_pTail->pNext = m_ppArray[nLastArrayID] + m_nLastArrayElementCount;

        //��β����ǰָ�� ָ��ԭβ���
        m_ppArray[nLastArrayID][m_nLastArrayElementCount].pPrev = m_pTail;

        //�޸�βָ��
        m_pTail = m_pTail->pNext;

        //�޸���β���
        m_pTail->pNext = NULL;
        m_pTail->nOuterID = nLastArrayID;
        m_pTail->nInnerID = m_nLastArrayElementCount;

        //�޸�����״̬
        m_nLastArrayElementCount++;
        m_nCount++;
    }

    //β��㸳ֵ
    m_pTail->Data = Node;

    //����βָ��
    return (POSITION) m_pTail;
}

template<class TYPE, class ARG_TYPE>
bool CFastList<TYPE, ARG_TYPE>::AddTail(CFastList<TYPE, ARG_TYPE>* pList)
{
    //�������
    if (m_ppArray == NULL ||
        pList == NULL ||
        pList->m_pHead == NULL)
    {
        return false;
    }

    //�������
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
    //�ͷŽ��
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

    //��ʼ������״̬
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
