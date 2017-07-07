#include "stdafx.h"
#include "..\include\MetaDataFunction.h"

#include "..\include\TypeTraits.h"
#include "..\include\ExceptionMetaData.h"
#include "..\..\include\ExceptionID.h"
#include <stdarg.h>

//平台相关
#define MD_FUNC_VA_INTSIZEOF(n)   ( ((n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

//变参函数里的参数size.
static int SizeInVarParamFunc(CMetaDataType *pMDType, void *pData, void **pBuff)
{	
	if (!pMDType) return 0;

	if (TypeTraits<char>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			char *pC = new char;
			*pC = *reinterpret_cast<int*>(pData);
			*pBuff = pC;
		}
		return sizeof(int);
	}
	else if (TypeTraits<short>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			short *pS = new short;
			*pS = *reinterpret_cast<int*>(pData);
			*pBuff = pS;
		}
		return sizeof(int);
	}
	else if (TypeTraits<unsigned char>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			unsigned char *pUC = new unsigned char;
			*pUC = *reinterpret_cast<int*>(pData);
			*pBuff = pUC;
		}
		return sizeof(int);
	}
	else if (TypeTraits<unsigned short>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			unsigned short *pUS = new unsigned short;
			*pUS = *reinterpret_cast<int*>(pData);
			*pBuff = pUS;
		}
		return sizeof(int);
	}
	else if (TypeTraits<float>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			float *pF = new float;
			*pF = (float)*reinterpret_cast<double*>(pData);
			*pBuff = pF;
		}
		return sizeof(double);
	}
	else
	{
		if (pBuff) *pBuff = NULL;
		return pMDType->GetSize();
	}
}

CMetaDataFunction::CMetaDataFunction(char *pName, CMetaData *pParent, void *pFunction)
	:CMetaData(pName, pParent, true), m_pFunction(pFunction), m_pParamTable(NULL), m_pReturnInfo(NULL)
{
}


CMetaDataFunction::~CMetaDataFunction(void)
{
	if (m_pParamTable)
	{
		delete m_pParamTable;
		m_pParamTable = NULL;
	}
	if (m_pReturnInfo)
	{
		delete m_pReturnInfo;
		m_pReturnInfo = NULL;
	}
}

void CMetaDataFunction::AddParamInfo(CMetaDataVarBase *pParam)
{
	if (pParam && pParam->GetMDType())
	{
		CParamVector *pParamTable(GetParamTable());
		pParamTable->push_back(pParam);
	}
}

void CMetaDataFunction::SetReturnInfo(CMetaDataVarBase *pRet)
{
	if (m_pReturnInfo)
		delete m_pReturnInfo;
	m_pReturnInfo = pRet;
}

bool CMetaDataFunction::FuncParamsCheck(CParamVector *pParamTypes)
{
	if (!m_pParamTable)
	{
		return (!pParamTypes) || (pParamTypes->size() == 0);
	}
	else if (!pParamTypes)
	{
		return (!m_pParamTable) || (m_pParamTable->size() == 0);
	}

	CParamVector::iterator itr_func;
	CParamVector::iterator itr_in;
	
	for (itr_func = m_pParamTable->begin(), itr_in = pParamTypes->begin();
		itr_func != m_pParamTable->end() && itr_in != pParamTypes->end(); ++itr_func, ++itr_in)
	{
		if ((*itr_func)->GetMDType() != (*itr_in)->GetMDType() || (*itr_func)->GetPtrLevel() != (*itr_in)->GetPtrLevel())
		{
			return false;
		}
	}
	return itr_func == m_pParamTable->end() && itr_in == pParamTypes->end();
}

bool CMetaDataFunction::CallFunction(int param_count, void **pParam, void *pReturn)
{
	if (!m_pFunction) return false;
	SMetaDataCalledFunctionDataPacket Packet = { param_count, pParam, pReturn };
	TpMDCalledFunction pFunc(reinterpret_cast<TpMDCalledFunction>(m_pFunction));
	return pFunc(Packet);
}

bool CMetaDataFunction::CallFunction(int param_count, va_list pParamList)
{
	if (!m_pFunction || (!m_pParamTable && param_count != 0) || (m_pParamTable && param_count != m_pParamTable->size())) return false;

	bool ret;

	unsigned int param_addr;
	bool *pNeedRelease;

	CParamVector::iterator itr;
	int type_size;
	void **pParamPtrBuffer;
	int index;

	SMetaDataCalledFunctionDataPacket Packet;
	TpMDCalledFunction pFunc(reinterpret_cast<TpMDCalledFunction>(m_pFunction));

	pNeedRelease = new bool[param_count];
	try
	{
		param_addr = reinterpret_cast<unsigned int>(pParamList);
		if (m_pParamTable)
		{
			pParamPtrBuffer = new void*[param_count];
			try
			{
				memset(pParamPtrBuffer, 0x00, sizeof(void*) * param_count);
				index = 0;
				for (itr = m_pParamTable->begin(); itr != m_pParamTable->end(); ++itr)
				{
					if ((*itr)->GetPtrLevel() <= 0)
						type_size = SizeInVarParamFunc((*itr)->GetMDType(), reinterpret_cast<void*>(param_addr), pParamPtrBuffer + index);
					else type_size = sizeof(void*);
					pNeedRelease[index] = pParamPtrBuffer[index] != NULL;
					if (!pNeedRelease[index])
					{
						pParamPtrBuffer[index] = reinterpret_cast<void*>(param_addr);
					}
					++index;
					param_addr += MD_FUNC_VA_INTSIZEOF(type_size);
				}

				Packet.ParamCount = param_count;
				Packet.pParam = pParamPtrBuffer;
				if (m_pReturnInfo)
				{
					Packet.pReturn = *reinterpret_cast<void**>(param_addr);
				}
				else Packet.pReturn = NULL;

				ret = pFunc(Packet);

				for (index = 0; index < param_count; ++index)
				{
					if (pNeedRelease[index])
						delete pParamPtrBuffer[index];
				}
			}
			catch (...)
			{
				delete[] pParamPtrBuffer;
				throw;
			}
			delete[] pParamPtrBuffer;
		}
		else
		{
			Packet.ParamCount = 0;
			Packet.pParam = NULL;
			if (m_pReturnInfo)
			{
				Packet.pReturn = *reinterpret_cast<void**>(param_addr);
			}
			else Packet.pReturn = NULL;

			ret = pFunc(Packet);
		}
	}
	catch (...)
	{
		delete[] pNeedRelease;
		throw;
	}
	delete[] pNeedRelease;

	return ret;
}

bool CMetaDataFunction::CallFunction(int param_count, ...)
{
	bool ret;
	va_list pList;
	va_start(pList, param_count);
	try
	{
		ret = CallFunction(param_count, pList);
	}
	catch (...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);
	return ret;
}

bool CMetaDataFunction::CallFunction(CParamVector *pParamTypes, va_list pParamList, void *pReturn)
{
	if (!m_pFunction || (!m_pParamTable && (pParamTypes) && pParamTypes->size()!= 0)
		|| (m_pParamTable && pParamTypes && m_pParamTable->size() != pParamTypes->size())
		|| (m_pParamTable && !pParamTypes && m_pParamTable->size() != 0)) return false;

	bool ret;

	unsigned int param_addr;
	int arr_size;
	bool *pNeedRelease;
	void **pParamPtrBuffer;

	CParamVector::iterator itr_in;
	CParamVector::iterator itr_func;
	int type_size;
	int index;
	bool bParamsOK(true);

	SMetaDataCalledFunctionDataPacket Packet;
	TpMDCalledFunction pFunc(reinterpret_cast<TpMDCalledFunction>(m_pFunction));

	if (m_pParamTable)
		arr_size = m_pParamTable->size();
	else arr_size = 0;

	pNeedRelease = new bool [arr_size];
	try
	{
		memset(pNeedRelease, 0x00, sizeof(bool) * arr_size);
		param_addr = reinterpret_cast<unsigned int>(pParamList);
		if (arr_size > 0)
		{
			if (param_addr == 0)
			{
				throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "错误：调用参数表缺失！");
			}
			pParamPtrBuffer = new void* [arr_size];
			try
			{
				memset(pParamPtrBuffer, 0x00, sizeof(void*) * arr_size);
				index = 0;
				for (itr_func = m_pParamTable->begin(), itr_in = pParamTypes->begin();
					itr_func != m_pParamTable->end() && itr_in != pParamTypes->end(); ++itr_func, ++itr_in)
				{
					if ((*itr_func)->GetMDType() == (*itr_in)->GetMDType() && (*itr_func)->GetPtrLevel() == (*itr_in)->GetPtrLevel())
					{
						if ((*itr_func)->GetPtrLevel() <= 0)
							type_size = SizeInVarParamFunc((*itr_func)->GetMDType(), reinterpret_cast<void*>(param_addr), pParamPtrBuffer + index);
						else type_size = sizeof(void*);
						pNeedRelease[index] = pParamPtrBuffer[index] != NULL;
						if (!pNeedRelease[index])
						{
							pParamPtrBuffer[index] = reinterpret_cast<void*>(param_addr);
						}
						++index;
						param_addr += MD_FUNC_VA_INTSIZEOF(type_size);
					}
					else
					{
						bParamsOK = false;
						break;
					}
				}
				if (bParamsOK) bParamsOK = itr_func == m_pParamTable->end() && itr_in == pParamTypes->end();

				if (bParamsOK)
				{
					Packet.ParamCount = arr_size;
					Packet.pParam = pParamPtrBuffer;
					if (m_pReturnInfo)
					{
						Packet.pReturn = pReturn;
					}
					else Packet.pReturn = NULL;

					ret = pFunc(Packet);
				}
				else ret = false;

				for (index = 0; index < arr_size; ++index)
				{
					if (pNeedRelease[index])
						delete pParamPtrBuffer[index];
				}
			}
			catch(...)
			{
				delete [] pParamPtrBuffer;
				throw;
			}
			delete [] pParamPtrBuffer;
		}
		else
		{
			Packet.ParamCount = 0;
			Packet.pParam = NULL;
			if (m_pReturnInfo)
			{
				Packet.pReturn = pReturn;
			}
			else Packet.pReturn = NULL;

			ret = pFunc(Packet);
		}
	}
	catch(...)
	{
		delete [] pNeedRelease;
		throw;
	}
	delete [] pNeedRelease;

	return ret;
}

bool CMetaDataFunction::CallFunction(CParamVector *pParamTypes, ...)
{
	bool ret;
	va_list pList;
	unsigned int param_addr;
	int size;
	unsigned int Ret_Offset;
	void *pReturn;
	CParamVector::iterator itr;

	va_start(pList, pParamTypes);
	try
	{
		if (m_pReturnInfo)
		{
			param_addr = reinterpret_cast<unsigned int>(pList);
			Ret_Offset = 0;
			if (m_pParamTable)
			{
				for (itr = m_pParamTable->begin(); itr != m_pParamTable->end(); ++itr)
				{
					if ((*itr)->GetPtrLevel() <= 0)
						size = SizeInVarParamFunc((*itr)->GetMDType(), NULL, NULL);
					else size = sizeof(void*);
					Ret_Offset += size;
				}
			}
			pReturn = *reinterpret_cast<void**>(param_addr + Ret_Offset);
		}
		else
		{
			pReturn = NULL;
		}

		ret = CallFunction(pParamTypes, pList, pReturn);
	}
	catch(...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);

	return ret;
}