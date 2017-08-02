#ifndef _TP_PUB_BAS_H
#define _TP_PUB_BAS_H

typedef	short ERR_TYPE;
typedef	short RET_TYPE;

#define	RET_CODE_OK				0				//成功
#define	RET_CODE_FAIL			1				//失败
#define RET_CODE_CANCEL			2				//取消
#define	RET_CODE_NODATA			10				//没取到数据
#define RET_CODE_NOEXIST        11              //不存在

// ********************************************************************************************
// ************************* 常用错误码定义 ***************************************************
// ********************************************************************************************

#define		TPERR_NO_ENOUGH_MEM				501		//没有足够内存
#define     TPERR_CANT_CREATE_COMOBJECT     502     //创建COM对象失败
#define     TPERR_FILE_CANT_OPEN            503     //打开文件失败
#define     TPERR_FILE_CANT_READ            504     //读文件失败

#define		TPERR_DB_CANT_CREATE_SESSION	601		//客户端不能与服务器建立连接
#define		TPERR_DB_SVR_DISC_CLT			602		//服务器断开客户端的连接
#define		TPERR_DB_COMM_FAIL				603		//通讯连接失败
#define		TPERR_DB_PSW_ERR				604		//用户名跟密码出现错误，登陆被拒绝
#define		TPERR_DB_DUPLICATE_KEY			605		//插入的数据存在重复

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

//不等于 RET_CODE_OK 返回 S_OK
#define NOT_OK_RETURNSOK_PTR(pErrProc)				\
	if ((pErrProc)->GetRetCode() != RET_CODE_OK)	\
	return S_OK

#define NOT_OK_RETURNSOK_REF(refErrProc)			\
	if ((refErrProc).GetRetCode() != RET_CODE_OK)	\
	return S_OK


//*****************************************************************
//类名:		CTpErrProc
//说明:		
//责任:		该类负责对错误信息进行处理
//关系:		
//操作:	
//属性:		
//特殊需求:	
//备注:		1. 该类在无参构造函数初始化的时候，并不初始化一个临时的缓冲区
//				是因为可以加快构造的速度
//制作日期:	
//制作人:	
//版本：	1.0
//修改记录
//*****************************************************************

class  CTpErrProc
{
public:
//构造与析构函数
	CTpErrProc();
    CTpErrProc(const CTpErrProc& refVal);
    CTpErrProc(const CTpErrProc * pVal);
							//功能					构造函数
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26

	CTpErrProc(ERR_TYPE ErrCode, LPCSTR ErrStr);
							//功能					构造函数
							//ErrCode		IN		错误代码
							//ErrStr		IN		错误信息串
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26

	virtual ~CTpErrProc();
							//功能					析构函数
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26


public:
//属性设置与获取
	ERR_TYPE			GetErrCode() const;
							//功能					返回错误代码
							//返回值                返回当前的错误代码
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26

	ERR_TYPE			SetErrCode(ERR_TYPE newVal);
							//功能					设置错误代码
							//返回值                返回设置之后的错误代码
							//newVal		IN		需要设置的新值
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26


	HRESULT				GetErrStr(char * pStrBuf, long BufLen) const;
							//功能					返回错误信息串
							//pStrBuf		OUT		保存信息的缓冲区
							//BufLen		IN		保存信息的缓冲区的大小
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26

	HRESULT				SetErrStr(LPCSTR newVal);
							//功能					设置错误信息串
							//newVal		IN		需要设置的新错误信息串
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26


	RET_TYPE			GetRetCode() const;
							//功能					返回返回代码
							//返回值                返回当前的返回代码
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26

	RET_TYPE			SetRetCode(RET_TYPE newVal);
							//功能					设置返回代码
							//返回值                返回设置之后的返回代码
							//newVal		IN		需要设置的新值
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26


	HRESULT				Reset();
							//功能					清除对象的状态
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26

	HRESULT				SetErrInfo(ERR_TYPE ErrCode, LPCSTR ErrStr, RET_TYPE RetCode = RET_CODE_OK);
							//功能					设置错误代码、错误信息串、返回代码
							//ErrCode		IN		错误代码
							//ErrStr		IN		错误信息串
							//RetCode		IN		返回代码
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26



public:
//信息的显示
	UINT				DispErrInfo();
							//功能					显示错误信息
							//返回值				返回 MessageBox() 的返回值
							//前置条件
							//后置条件
							//创建时间				2003-01-26
							//最后修改时间			2003-01-26

private:
//成员变量
	ERR_TYPE			m_nErrCode;		//错误代码
	char			*	m_pErrStr;		//错误信息串
	RET_TYPE			m_nRetCode;		//返回代码

};

//*****************************************************************
//类名:		CStructManager
//说明:		结构管理器
//责任:		结构管理器负责将所有的结构放在一个指针里面，负责管理数据
//关系:		
//操作:		
//属性:		
//特殊需求:	
//备注:
//制作日期:	
//制作人:	杨志刚
//版本：	
//修改记录
//*****************************************************************

template <class T> class CStructManager
{
public:
					CStructManager(long Increment)
							//Increment-缓冲区增量
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
							//取得结构缓冲区中对象的数目
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
                        //重新设置缓冲区的大小到默认的增量大小，避免不必要的内存浪费
                        //该函数执行前，内存中必须对象的数目为0
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
                            //释放老数据
							FreeAllStruct();
							m_nAllocBufNum = m_nIncrement;

                            //清零
							m_pStructList = TempPtr;
							memset(m_pStructList, '\0', m_nAllocBufNum * sizeof(T));

							return S_OK;
                        }

	HRESULT			FreeAllStruct()
							//释放所有的结构
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
							//添加一个结构
							//pStruct-结构缓冲区指针
						{
							return AppendStruct(pStruct, 1, pErrProc);
						}

	virtual	HRESULT	Append(T Cell, CTpErrProc * pErrProc)
							//添加一个结构
							//Cell-结构
						{
							return AppendStruct(&Cell, 1, pErrProc);
						}

	virtual HRESULT	AppendN(const T * pStruct, long StructNum, CTpErrProc * pErrProc)
							//添加num个结构
							//pStruct-结构缓冲区指针,StructNum-结构数量
						{
							return AppendStruct(pStruct, StructNum, pErrProc);
						}

	virtual HRESULT	Append(const CStructManager& List, CTpErrProc * pErrProc)
							//从一个对象添加数据
							//List-引用的对象
						{
							return AppendStruct(List.GetStructPtr(), List.GetStructNum(), pErrProc);
						}

	virtual HRESULT	Append(const CStructManager * pList, CTpErrProc * pErrProc)
							//从一个对象添加数据
							//pList-结构管理器指针
						{
							return AppendStruct(pList->GetStructPtr(), pList->GetStructNum(), pErrProc);
						}

	virtual HRESULT	InsertBefore(long Item, const T * pStruct, CTpErrProc * pErrProc)
							//在第n个元素前面插入一个元素
							//Item-项目,pStruct-结构缓冲区指针
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
							//从上往下移动...
							for (i = m_nStructNum - 1; i >= Item; i--)
                            {
								memcpy(m_pStructList + i + 1, m_pStructList + i, sizeof(T));
                            }
							//拷贝数据...
							memcpy(m_pStructList + Item, pStruct, sizeof(T));
							m_nStructNum++;

							return S_OK;
						}

	HRESULT			Peek(long Item, T * pStruct) const
							//取出索引为 n 的结构
							//Item-项目,pStruct-结构缓冲区指针
						{
							if (Item >= 0 && Item < m_nStructNum)
							{
								memcpy(pStruct, m_pStructList + Item, sizeof(T));
							}
							return S_OK;
						}

	T			*	GetAt(long Item) const
							//取出第Item项结构的指针 如果n无效return NULL
							//Item-项目
						{
							if (Item >= 0 && Item < m_nStructNum)
							{
								return m_pStructList + Item;
							}
							return NULL;
						}

	HRESULT			Delete(long Item)
							//删除第Item项
							//Item-项目
						{
							long			i;

							if (Item < 0 || Item >= m_nStructNum)
							{
								return S_OK;
							}
							if (Item == (m_nStructNum - 1))	//最后一个
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
							//更新索引为 Item 的结构
							//Item-项目,pStruct-结构缓冲区指针
						{
							if (Item < 0 || Item >= m_nStructNum)
							{
								return S_OK;
							}
							memcpy(m_pStructList + Item, pStruct, sizeof(T));
							return S_OK;
						}

	HRESULT			Update(long Item, T Cell)
							//更新索引为 Item 的结构
							//Item-项目,Cell-结构
						{
							return Update(Item, &Cell);
						}

	HRESULT			SetStructNum(long StructNum)
							//设置结构的数目
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
							//结构数目-1
						{
							if (m_nStructNum > 0)
							{
								m_nStructNum--;
							}
							return S_OK;
						}

	T			*	GetStructPtr() const
							//返回结构的指针
						{
							return m_pStructList;
						}

	HRESULT			CopyStruct(T * pStruct) const
							//拷贝所有数据到缓冲区
							//pStruct-结构缓冲区指针
						{
							if (m_nStructNum > 0)
							{
								memcpy(pStruct, m_pStructList, m_nStructNum * sizeof(T));
							}
							return S_OK;
						}

	HRESULT			ReMallocMemory(long StructNum, CTpErrProc * pErrProc)
							//重新分配对象缓冲区大小
							//StructNum-结构数目
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
							//判断需要几份增量数据
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
	long			m_nIncrement;		//结构缓冲区增量
	long			m_nAllocBufNum;		//结构缓冲区大小
	long			m_nStructNum;		//结构缓冲区中结构的数目
	T			*	m_pStructList;		//结构缓冲区
};

#endif