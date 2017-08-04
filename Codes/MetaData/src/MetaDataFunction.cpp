#include "stdafx.h"
#include "..\include\MetaDataFunction.h"

#include "..\include\TypeTraits.h"
#include "..\include\ExceptionMetaData.h"
#include "..\include\ExceptionIDMetaData.h"
#include <stdarg.h>

//平台相关
#define MD_FUNC_VA_INTSIZEOF(n)   ( ((n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

//变参函数里的参数size.
static int SizeInVarParamFunc(const CMetaDataType *pMDType, void *pData, void **pBuff)
{	
	if (!pMDType) return 0;

	if (TypeTraits<char>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			char *pC(new char);
			*pC = *reinterpret_cast<int*>(pData);
			*pBuff = pC;
		}
		return sizeof(int);
	}
	else if (TypeTraits<short>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			short *pS(new short);
			*pS = *reinterpret_cast<int*>(pData);
			*pBuff = pS;
		}
		return sizeof(int);
	}
	else if (TypeTraits<unsigned char>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			unsigned char *pUC(new unsigned char);
			*pUC = *reinterpret_cast<int*>(pData);
			*pBuff = pUC;
		}
		return sizeof(int);
	}
	else if (TypeTraits<unsigned short>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			unsigned short *pUS(new unsigned short);
			*pUS = *reinterpret_cast<int*>(pData);
			*pBuff = pUS;
		}
		return sizeof(int);
	}
	else if (TypeTraits<float>::GetMetaDataType() == pMDType)
	{
		if (pData && pBuff)
		{
			float *pF(new float);
			*pF = static_cast<float>(*reinterpret_cast<double*>(pData));
			*pBuff = pF;
		}
		return sizeof(double);
	}
	else
	{
		if (pBuff) *pBuff = nullptr;
		return pMDType->GetSize();
	}
}

static void SizeInVarParamFuncFree(const CMetaDataType *pMDType, void **pBuff)
{
	if (!pMDType) return;

	if (TypeTraits<char>::GetMetaDataType() == pMDType)
	{
		if (pBuff)
		{
			char *pC(reinterpret_cast<char*>(*pBuff));
			delete pC;
		}
	}
	else if (TypeTraits<short>::GetMetaDataType() == pMDType)
	{
		if (pBuff)
		{
			short *pS(reinterpret_cast<short*>(*pBuff));
			delete pS;
		}
	}
	else if (TypeTraits<unsigned char>::GetMetaDataType() == pMDType)
	{
		if (pBuff)
		{
			unsigned char *pUC(reinterpret_cast<unsigned char*>(*pBuff));
			delete pUC;
		}
	}
	else if (TypeTraits<unsigned short>::GetMetaDataType() == pMDType)
	{
		if (pBuff)
		{
			unsigned short *pUS(reinterpret_cast<unsigned short*>(*pBuff));
			delete pUS;
		}
	}
	else if (TypeTraits<float>::GetMetaDataType() == pMDType)
	{
		if (pBuff)
		{
			float *pF(reinterpret_cast<float*>(*pBuff));
			delete pF;
		}
	}
	else
	{
		//do nothing.
	}
}

CMetaDataFunction::CMetaDataFunction(const char *pName, const CMetaData *pParent, void *pFunction)
	:CMetaData(pName, pParent, true), m_pFunction(pFunction), m_pParamTable(nullptr), m_pReturnInfo(nullptr)
{
}


CMetaDataFunction::~CMetaDataFunction(void)
{
	if (m_pParamTable)
	{
		delete m_pParamTable;
		m_pParamTable = nullptr;
	}
	if (m_pReturnInfo)
	{
		delete m_pReturnInfo;
		m_pReturnInfo = nullptr;
	}
}

void CMetaDataFunction::AddParamInfo(const CMetaDataVarBase *pParam)
{
	if (pParam && pParam->GetMDType())
	{
		CParamVector *pParamTable(GetParamTable());
		pParamTable->push_back(pParam);
	}
}

void CMetaDataFunction::SetReturnInfo(const CMetaDataVarBase *pRet)
{
	if (m_pReturnInfo)
		delete m_pReturnInfo;
	m_pReturnInfo = pRet;
}

bool CMetaDataFunction::FuncParamsCheck(CParamVector *pParamTypes) const
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

bool CMetaDataFunction::CallFunction(int param_count, void **pParam, void *pReturn) const
{
	if (!m_pFunction) return false;
	SMetaDataCalledFunctionDataPacket Packet = { param_count, pParam, pReturn };
	TpMDCalledFunction pFunc(reinterpret_cast<TpMDCalledFunction>(m_pFunction));
	return pFunc(Packet);
}

bool CMetaDataFunction::CallFunction(const unsigned int param_count, va_list pParamList, void *pReturn) const
{
	return CallFunction(param_count, nullptr, pParamList, pReturn);
}

bool CMetaDataFunction::CallFunction(const unsigned int param_count, ...) const
{
	bool ret;
	va_list pList;
	va_start(pList, param_count);
	try
	{
		ret = CallFunction(param_count, pList, nullptr);
	}
	catch (...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);
	return ret;
}

bool CMetaDataFunction::CallFunction(CParamVector *pParamTypes, va_list pParamList, void *pReturn) const
{
	if (pParamTypes)
		return CallFunction(pParamTypes->size(), pParamTypes, pParamList, pReturn);
	else return CallFunction(0, pParamTypes, pParamList, pReturn);
}

bool CMetaDataFunction::CallFunction(CParamVector *pParamTypes, ...) const
{
	bool ret;
	va_list pList;
	va_start(pList, pParamTypes);
	try
	{
		ret = CallFunction(pParamTypes, pList, nullptr);
	}
	catch(...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);

	return ret;
}

bool CMetaDataFunction::CallFunction(const unsigned int param_count, CParamVector *pParamTypes,
									 va_list pParamList, void *pReturn) const
{
	if (!m_pFunction
		|| (!m_pParamTable && param_count != 0)
		|| (m_pParamTable && param_count != m_pParamTable->size())) return false;
	if (pParamTypes && param_count != pParamTypes->size()) return false;

	bool ret;

	unsigned int param_addr;

	bool *pNeedRelease(nullptr);
	void **pParamPtrBuffer = nullptr;

	size_t index;
	int type_size;
	bool bParamsOK(true);

	SMetaDataCalledFunctionDataPacket Packet;
	TpMDCalledFunction pFunc(reinterpret_cast<TpMDCalledFunction>(m_pFunction));

	param_addr = reinterpret_cast<unsigned int>(pParamList);
	if (param_count)
	{
		if (0 == param_addr) throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：参数表缺失！");
		pNeedRelease = new bool[param_count];
		pParamPtrBuffer = new void*[param_count];
	}
	try
	{
		if (pParamPtrBuffer)
			memset(pParamPtrBuffer, 0x00, sizeof(void*) * param_count);
		for (index = 0; index < param_count; ++index)
		{
			if (pParamTypes)
			{
				if (pParamTypes->at(index)->GetMDType() != m_pParamTable->at(index)->GetMDType()
					|| pParamTypes->at(index)->GetPtrLevel() != m_pParamTable->at(index)->GetPtrLevel())
				{
					bParamsOK = false;
					break;
				}
			}
			if (m_pParamTable->at(index)->GetPtrLevel() <= 0)
				type_size = SizeInVarParamFunc(m_pParamTable->at(index)->GetMDType(), reinterpret_cast<void*>(param_addr), pParamPtrBuffer + index);
			else type_size = sizeof(void*);
			pNeedRelease[index] = pParamPtrBuffer[index] != nullptr;
			if (!pNeedRelease[index])
			{
				pParamPtrBuffer[index] = reinterpret_cast<void*>(param_addr);
			}
			param_addr += MD_FUNC_VA_INTSIZEOF(type_size);
		}

		try
		{
			if (bParamsOK)
			{
				Packet.ParamCount = param_count;
				Packet.pParam = pParamPtrBuffer;
				if (m_pReturnInfo)
				{
					if (pReturn)
					{
						Packet.pReturn = pReturn;
					}
					else
					{
						if (0 == param_addr) throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：参数表缺失！");
						Packet.pReturn = *reinterpret_cast<void**>(param_addr);
					}
				}
				else Packet.pReturn = nullptr;

				ret = pFunc(Packet);
			}
			else ret = false;
		}
		catch (...)
		{
			for (index = 0; index < param_count; ++index)
			{
				if (pNeedRelease[index])
					SizeInVarParamFuncFree(m_pParamTable->at(index)->GetMDType(), pParamPtrBuffer + index);
			}
			throw;
		}
		for (index = 0; index < param_count; ++index)
		{
			if (pNeedRelease[index])
				SizeInVarParamFuncFree(m_pParamTable->at(index)->GetMDType(), pParamPtrBuffer + index);
		}
	}
	catch(...)
	{
		if (pParamPtrBuffer) delete [] pParamPtrBuffer;
		if (pNeedRelease) delete[] pNeedRelease;
		throw;
	}
	if (pParamPtrBuffer) delete [] pParamPtrBuffer;
	if (pNeedRelease) delete[] pNeedRelease;

	return ret;
}