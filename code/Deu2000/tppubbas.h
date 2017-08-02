#ifndef _TP_PUB_BAS_H
#define _TP_PUB_BAS_H

typedef	short ERR_TYPE;
typedef	short RET_TYPE;

#define	RET_CODE_OK				0				//�ɹ�
#define	RET_CODE_FAIL			1				//ʧ��
#define RET_CODE_CANCEL			2				//ȡ��
#define	RET_CODE_NODATA			10				//ûȡ������
#define RET_CODE_NOEXIST        11              //������

// ********************************************************************************************
// ************************* ���ô����붨�� ***************************************************
// ********************************************************************************************

#define		TPERR_NO_ENOUGH_MEM				501		//û���㹻�ڴ�
#define     TPERR_CANT_CREATE_COMOBJECT     502     //����COM����ʧ��
#define     TPERR_FILE_CANT_OPEN            503     //���ļ�ʧ��
#define     TPERR_FILE_CANT_READ            504     //���ļ�ʧ��

#define		TPERR_DB_CANT_CREATE_SESSION	601		//�ͻ��˲������������������
#define		TPERR_DB_SVR_DISC_CLT			602		//�������Ͽ��ͻ��˵�����
#define		TPERR_DB_COMM_FAIL				603		//ͨѶ����ʧ��
#define		TPERR_DB_PSW_ERR				604		//�û�����������ִ��󣬵�½���ܾ�
#define		TPERR_DB_DUPLICATE_KEY			605		//��������ݴ����ظ�

#define     ERR_CODE_NOERR                  0
#define     ERR_CODE_COMM                   0

typedef struct tagControlPoint {
	char       res_x[32];
	char       res_y[32];
	char       res_z[32];
	char       des_x[32];
	char       des_y[32];
	char       des_z[32];
} ControlPoint;

//������ RET_CODE_OK ���� S_OK
#define NOT_OK_RETURNSOK_PTR(pErrProc)				\
	if ((pErrProc)->GetRetCode() != RET_CODE_OK)	\
	return S_OK

#define NOT_OK_RETURNSOK_REF(refErrProc)			\
	if ((refErrProc).GetRetCode() != RET_CODE_OK)	\
	return S_OK


//*****************************************************************
//����:		CTpErrProc
//˵��:		
//����:		���ฺ��Դ�����Ϣ���д���
//��ϵ:		
//����:	
//����:		
//��������:	
//��ע:		1. �������޲ι��캯����ʼ����ʱ�򣬲�����ʼ��һ����ʱ�Ļ�����
//				����Ϊ���Լӿ칹����ٶ�
//��������:	
//������:	
//�汾��	1.0
//�޸ļ�¼
//*****************************************************************

class  CTpErrProc
{
public:
//��������������
	CTpErrProc();
    CTpErrProc(const CTpErrProc& refVal);
    CTpErrProc(const CTpErrProc * pVal);
							//����					���캯��
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26

	CTpErrProc(ERR_TYPE ErrCode, LPCSTR ErrStr);
							//����					���캯��
							//ErrCode		IN		�������
							//ErrStr		IN		������Ϣ��
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26

	virtual ~CTpErrProc();
							//����					��������
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26


public:
//�����������ȡ
	ERR_TYPE			GetErrCode() const;
							//����					���ش������
							//����ֵ                ���ص�ǰ�Ĵ������
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26

	ERR_TYPE			SetErrCode(ERR_TYPE newVal);
							//����					���ô������
							//����ֵ                ��������֮��Ĵ������
							//newVal		IN		��Ҫ���õ���ֵ
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26


	HRESULT				GetErrStr(char * pStrBuf, long BufLen) const;
							//����					���ش�����Ϣ��
							//pStrBuf		OUT		������Ϣ�Ļ�����
							//BufLen		IN		������Ϣ�Ļ������Ĵ�С
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26

	HRESULT				SetErrStr(LPCSTR newVal);
							//����					���ô�����Ϣ��
							//newVal		IN		��Ҫ���õ��´�����Ϣ��
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26


	RET_TYPE			GetRetCode() const;
							//����					���ط��ش���
							//����ֵ                ���ص�ǰ�ķ��ش���
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26

	RET_TYPE			SetRetCode(RET_TYPE newVal);
							//����					���÷��ش���
							//����ֵ                ��������֮��ķ��ش���
							//newVal		IN		��Ҫ���õ���ֵ
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26


	HRESULT				Reset();
							//����					��������״̬
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26

	HRESULT				SetErrInfo(ERR_TYPE ErrCode, LPCSTR ErrStr, RET_TYPE RetCode = RET_CODE_OK);
							//����					���ô�����롢������Ϣ�������ش���
							//ErrCode		IN		�������
							//ErrStr		IN		������Ϣ��
							//RetCode		IN		���ش���
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26



public:
//��Ϣ����ʾ
	UINT				DispErrInfo();
							//����					��ʾ������Ϣ
							//����ֵ				���� MessageBox() �ķ���ֵ
							//ǰ������
							//��������
							//����ʱ��				2003-01-26
							//����޸�ʱ��			2003-01-26

private:
//��Ա����
	ERR_TYPE			m_nErrCode;		//�������
	char			*	m_pErrStr;		//������Ϣ��
	RET_TYPE			m_nRetCode;		//���ش���

};

//*****************************************************************
//����:		CStructManager
//˵��:		�ṹ������
//����:		�ṹ�������������еĽṹ����һ��ָ�����棬�����������
//��ϵ:		
//����:		
//����:		
//��������:	
//��ע:
//��������:	
//������:	��־��
//�汾��	
//�޸ļ�¼
//*****************************************************************

template <class T> class CStructManager
{
public:
					CStructManager(long Increment)
							//Increment-����������
						: m_nIncrement((Increment > 0) ? Increment : 1)
						, m_nAllocBufNum(0)
						, m_nStructNum(0)
						, m_pStructList(NULL)
						{
							m_pStructList = new T[m_nIncrement];
							if (m_pStructList != NULL)
							{
								m_nAllocBufNum = m_nIncrement;
								memset(m_pStructList, '\0', m_nAllocBufNum * sizeof(T));
							}
						}

					CStructManager()
						: m_nIncrement(2)
						, m_nAllocBufNum(0)
						, m_nStructNum(0)
						, m_pStructList(NULL)
						{
							m_pStructList = new T[m_nIncrement];
							if (m_pStructList != NULL)
							{
								m_nAllocBufNum = m_nIncrement;
								memset(m_pStructList, '\0', m_nAllocBufNum * sizeof(T));
							}
						}

					virtual ~CStructManager()
						{
							FreeAllStruct();
						}

	long			GetStructNum() const
							//ȡ�ýṹ�������ж������Ŀ
						{
							return m_nStructNum;
						}

	HRESULT			Reset()
							//StructNum=0
						{
							m_nStructNum = 0;
							return S_OK;
						}

    HRESULT         ResetBufSize(CTpErrProc * pErrProc)
                        //�������û������Ĵ�С��Ĭ�ϵ�������С�����ⲻ��Ҫ���ڴ��˷�
                        //�ú���ִ��ǰ���ڴ��б���������ĿΪ0
                        {
							T		*	TempPtr;

							pErrProc->Reset();

                            if (m_nStructNum > 0)
                            {
                                return S_OK;
                            }
                            if (m_nAllocBufNum <= m_nIncrement)
                            {
                                return S_OK;
                            }
							TempPtr = new T[m_nIncrement];
							if (TempPtr == NULL)
							{
								pErrProc->SetErrCode(TPERR_NO_ENOUGH_MEM);
								return S_OK;
							}
                            //�ͷ�������
							FreeAllStruct();
							m_nAllocBufNum = m_nIncrement;

                            //����
							m_pStructList = TempPtr;
							memset(m_pStructList, '\0', m_nAllocBufNum * sizeof(T));

							return S_OK;
                        }

	HRESULT			FreeAllStruct()
							//�ͷ����еĽṹ
						{
							if (m_pStructList != NULL)
							{
								delete [] m_pStructList;
								m_pStructList = NULL;
							}
							m_nAllocBufNum = 0;
							m_nStructNum = 0;
							return S_OK;
						}

	virtual HRESULT	Append(const T * pStruct, CTpErrProc * pErrProc)
							//���һ���ṹ
							//pStruct-�ṹ������ָ��
						{
							return AppendStruct(pStruct, 1, pErrProc);
						}

	virtual	HRESULT	Append(T Cell, CTpErrProc * pErrProc)
							//���һ���ṹ
							//Cell-�ṹ
						{
							return AppendStruct(&Cell, 1, pErrProc);
						}

	virtual HRESULT	AppendN(const T * pStruct, long StructNum, CTpErrProc * pErrProc)
							//���num���ṹ
							//pStruct-�ṹ������ָ��,StructNum-�ṹ����
						{
							return AppendStruct(pStruct, StructNum, pErrProc);
						}

	virtual HRESULT	Append(const CStructManager& List, CTpErrProc * pErrProc)
							//��һ�������������
							//List-���õĶ���
						{
							return AppendStruct(List.GetStructPtr(), List.GetStructNum(), pErrProc);
						}

	virtual HRESULT	Append(const CStructManager * pList, CTpErrProc * pErrProc)
							//��һ�������������
							//pList-�ṹ������ָ��
						{
							return AppendStruct(pList->GetStructPtr(), pList->GetStructNum(), pErrProc);
						}

	virtual HRESULT	InsertBefore(long Item, const T * pStruct, CTpErrProc * pErrProc)
							//�ڵ�n��Ԫ��ǰ�����һ��Ԫ��
							//Item-��Ŀ,pStruct-�ṹ������ָ��
						{
                            long            i;
                            
							pErrProc->Reset();

							Item = (Item < 0) ? 0 : Item;
							if (Item >= m_nStructNum)
							{
								return AppendStruct(pStruct, 0, pErrProc);
							}
							ReMallocMemory(1, pErrProc);
							NOT_OK_RETURNSOK_PTR(pErrProc);
							//���������ƶ�...
							for (i = m_nStructNum - 1; i >= Item; i--)
                            {
								memcpy(m_pStructList + i + 1, m_pStructList + i, sizeof(T));
                            }
							//��������...
							memcpy(m_pStructList + Item, pStruct, sizeof(T));
							m_nStructNum++;

							return S_OK;
						}

	HRESULT			Peek(long Item, T * pStruct) const
							//ȡ������Ϊ n �Ľṹ
							//Item-��Ŀ,pStruct-�ṹ������ָ��
						{
							if (Item >= 0 && Item < m_nStructNum)
							{
								memcpy(pStruct, m_pStructList + Item, sizeof(T));
							}
							return S_OK;
						}

	T			*	GetAt(long Item) const
							//ȡ����Item��ṹ��ָ�� ���n��Чreturn NULL
							//Item-��Ŀ
						{
							if (Item >= 0 && Item < m_nStructNum)
							{
								return m_pStructList + Item;
							}
							return NULL;
						}

	HRESULT			Delete(long Item)
							//ɾ����Item��
							//Item-��Ŀ
						{
							long			i;

							if (Item < 0 || Item >= m_nStructNum)
							{
								return S_OK;
							}
							if (Item == (m_nStructNum - 1))	//���һ��
							{
								m_nStructNum--;
								return S_OK;
							}
							for (i = Item + 1; i < m_nStructNum; i++)
							{
								memcpy(m_pStructList + (i - 1), m_pStructList + i, sizeof(T));
							}
							m_nStructNum--;
							return S_OK;
						}

	HRESULT			Update(long Item, const T * pStruct)
							//��������Ϊ Item �Ľṹ
							//Item-��Ŀ,pStruct-�ṹ������ָ��
						{
							if (Item < 0 || Item >= m_nStructNum)
							{
								return S_OK;
							}
							memcpy(m_pStructList + Item, pStruct, sizeof(T));
							return S_OK;
						}

	HRESULT			Update(long Item, T Cell)
							//��������Ϊ Item �Ľṹ
							//Item-��Ŀ,Cell-�ṹ
						{
							return Update(Item, &Cell);
						}

	HRESULT			SetStructNum(long StructNum)
							//���ýṹ����Ŀ
						{
							if (StructNum < 0)
								StructNum = 0;
							if (StructNum <= m_nAllocBufNum)
							{
								m_nStructNum = StructNum;
							}
							return S_OK;
						}

	HRESULT			SubStructNum()
							//�ṹ��Ŀ-1
						{
							if (m_nStructNum > 0)
							{
								m_nStructNum--;
							}
							return S_OK;
						}

	T			*	GetStructPtr() const
							//���ؽṹ��ָ��
						{
							return m_pStructList;
						}

	HRESULT			CopyStruct(T * pStruct) const
							//�����������ݵ�������
							//pStruct-�ṹ������ָ��
						{
							if (m_nStructNum > 0)
							{
								memcpy(pStruct, m_pStructList, m_nStructNum * sizeof(T));
							}
							return S_OK;
						}

	HRESULT			ReMallocMemory(long StructNum, CTpErrProc * pErrProc)
							//���·�����󻺳�����С
							//StructNum-�ṹ��Ŀ
						{
							T			*	TempPtr;
							long			TotalNum;
							long			n;

							pErrProc->Reset();

							if (StructNum < 1)
							{
								return S_OK;
							}
							StructNum = (StructNum > 0) ? StructNum : 1;
							if ((m_nStructNum + StructNum) <= m_nAllocBufNum)
                            {
								return S_OK;
                            }
							if (m_nIncrement < 1)
							{
                                m_nIncrement = 1;
							}
							//�ж���Ҫ������������
							n = StructNum / m_nIncrement;
                            TotalNum = (n + 1) * m_nIncrement;
                            if (TotalNum < m_nAllocBufNum)
                            {
                                TotalNum = m_nAllocBufNum;
                            }
							TotalNum += m_nAllocBufNum;

							TempPtr = new T[TotalNum];
							if (TempPtr == NULL)
							{
								pErrProc->SetErrCode(TPERR_NO_ENOUGH_MEM);
								return S_OK;
							}
							m_nAllocBufNum = TotalNum;
							if (m_pStructList != NULL)
							{
								if (m_nStructNum > 0)
								{
									memcpy(TempPtr, m_pStructList, m_nStructNum * sizeof(T));
								}
								delete [] m_pStructList;
								m_pStructList = NULL;
							}
							m_pStructList = TempPtr;
							return S_OK;
						}

	HRESULT			AppendStruct(const T * pStruct, long StructNum, CTpErrProc * pErrProc)
						{
							pErrProc->Reset();

							if (StructNum < 1)
							{
								return S_OK;
							}
							ReMallocMemory(StructNum, pErrProc);
							NOT_OK_RETURNSOK_PTR(pErrProc);
							memcpy(m_pStructList + m_nStructNum, pStruct, StructNum * sizeof(T));
							m_nStructNum += StructNum;
							return S_OK;
						}

private:
	long			m_nIncrement;		//�ṹ����������
	long			m_nAllocBufNum;		//�ṹ��������С
	long			m_nStructNum;		//�ṹ�������нṹ����Ŀ
	T			*	m_pStructList;		//�ṹ������
};

#endif