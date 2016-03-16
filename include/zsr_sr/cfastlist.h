#ifndef CFASTLIST_H
#define CFASTLIST_H

#include <afxtempl.h>
#define ZSR_MOCK
#ifdef ZSR_MOCK
#define CFastList CList
#else
//����������һ���Զ���ġ�Ϊ����������ڴ�������ͷ�Ч�ʵġ��������������������ݽṹ��
//�궨��ͽṹ���� 
#define ASSERT assert #define FASTLIST_MAX_ARRAY_NUM 65536 
//������Ϊ���ٸ����������ڴ� 
#define FASTLIST_MAX_ARRAY_LEN 256 
//ÿ������Ľ����� 
#define FASTLIST_MAX_COUNT (FASTLIST_MAX_ARRAY_LEN * FASTLIST_MAX_ARRAY_NUM) 
//����������������� 
template<class TYPE, class ARG_TYPE> 
class CFastList 
{ 
public:
	int GetCount() const; //������������Ŀ 
	bool IsEmpty(); //�����Ƿ������ 
	TYPE& GetHead(); 
	//����ͷ��� 
	const TYPE& GetHead() const; //����ͷ��� 
	TYPE& GetTail(); //����β��� 
	const TYPE& GetTail() const; //����β��� 
	TYPE& RemoveHead(); //ɾ��ͷ��㣬����ԭͷ��� 
	TYPE& RemoveTail(); //ɾ��β��㣬����ԭβ��� 
	POSITION AddHead(ARG_TYPE Node); //���ͷ��㣬����ͷ���λ�ã�ʧ�ܷ���NULL 
	bool AddHead(CFastList<TYPE, ARG_TYPE>* pList); //ͷ���ǰ��������ɹ�����true��ʧ�ܷ���false 
	POSITION AddTail(ARG_TYPE Node); //���β��㣬����β���λ�ã�ʧ�ܷ���NULL 
	bool AddTail(CFastList<TYPE, ARG_TYPE>* pList); //β������������ɹ�����true��ʧ�ܷ���false 
	void RemoveAll();//ɾ��ȫ�������� POSITION GetHeadPosition(); //����ͷ���λ�ã�ʧ�ܷ���NULL 
	POSITION GetTailPosition(); //����β���λ�ã�ʧ�ܷ���NULL TYPE& GetNext(POSITION& pos); //�õ����� 
	const TYPE& GetNext(POSITION& pos) const; //�õ����� TYPE& GetPrev(POSITION& pos); //�õ�ǰ��� 
	const TYPE& GetPrev(POSITION& pos) const; //�õ�ǰ��� TYPE& GetAt(POSITION pos); //��ȡ���ֵ 
	const TYPE& GetAt(POSITION pos) const; //��ȡ���ֵ TYPE& GetAt(int nIndex); //��ȡ���ֵ 
	const TYPE& GetAt(int nIndex) const; //��ȡ���ֵ TYPE& operator[](int nIndex); //��ȡ���ֵ
	const TYPE& operator[](int nIndex) const; //��ȡ���ֵ 
	bool SetAt(POSITION pos, ARG_TYPE Node);//�޸�ָ��λ�õĽ����ֵ 
	bool SetAt(int nIndex, ARG_TYPE Node); //�޸�ָ��λ�õĽ����ֵ 
	bool RemoveAt(POSITION pos); //ɾ��ָ��λ�õĽ�� 
	bool RemoveAt(int nIndex); //ɾ��ָ��λ�õĽ�� 
	POSITION InsertBefore(POSITION pos, ARG_TYPE Node); //��posǰ����Node��ʧ�ܷ���NULL 
	POSITION InsertBefore(int nIndex , ARG_TYPE Node); //��nIndexǰ����Node��ʧ�ܷ���NULL 
	POSITION InsertAfter (POSITION pos, ARG_TYPE Node); //��pos�����Node��ʧ�ܷ���NULL 
	POSITION InsertAfter (int nIndex , ARG_TYPE Node); //��nIndex�����Node��ʧ�ܷ���NULL 
	POSITION Find(ARG_TYPE Node, POSITION pos); //��pos�����Node��δ�ҵ���ʧ�ܷ���NULL 
	POSITION Find(ARG_TYPE Node, int nIndex0); //��nIndex�����Node��δ�ҵ���ʧ�ܷ���NULL
	POSITION FindIndex(int nIndex); // �ҵ�nIndex������λ�ã�δ�ҵ���ʧ�ܷ���NULL

	//missings compared with CList
	POSITION &GetHeadPosition();
};
#endif // ZSR_MORK

#endif // CFASTLIST_H