#include "stdafx.h"
#include "..\include\MetaDataFunction.h"

#include "..\include\TypeTraits.h"
#include "..\include\ExceptionMetaData.h"
#include "..\include\ExceptionIDMetaData.h"
#include <stdarg.h>

#ifdef CO_PLATFORM_WIN_X64
typedef __int64			TD_INT_TYPE;
typedef double			TD_FLOAT_TYPE;

#define MD_FUNC_VAR_PARAM_ELE_STANDARD_SIZE		sizeof(__int64)
#else
typedef int				TD_INT_TYPE;
typedef double			TD_FLOAT_TYPE;

#define MD_FUNC_VAR_PARAM_SIZEOF(n)   ( ((n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#endif

//提取变参函数里的参数数据值及其Size.
static inline size_t ExtractDataAndDataSizeInVarParamFunc(const CMetaDataType *pMDType, void *pData, /*out*/void **pParamPtrBuffer)
{	
	if (!pMDType || !pData || !pParamPtrBuffer) return 0;

	if (TypeTraits<char>::GetMetaDataType() == pMDType)
	{
		char *pC(new char);
		*pC = static_cast<char>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pC;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<wchar_t>::GetMetaDataType() == pMDType)
	{
		wchar_t *pWCT(new wchar_t);
		*pWCT = static_cast<wchar_t>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pWCT;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<short>::GetMetaDataType() == pMDType)
	{
		short *pS(new short);
		*pS = static_cast<short>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pS;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<unsigned char>::GetMetaDataType() == pMDType)
	{
		unsigned char *pUC(new unsigned char);
		*pUC = static_cast<unsigned char>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pUC;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<unsigned short>::GetMetaDataType() == pMDType)
	{
		unsigned short *pUS(new unsigned short);
		*pUS = static_cast<unsigned short>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pUS;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<float>::GetMetaDataType() == pMDType)
	{
		float *pF(new float);
		*pF = static_cast<float>(*reinterpret_cast<TD_FLOAT_TYPE*>(pData));
		*pParamPtrBuffer = pF;
		return sizeof(TD_FLOAT_TYPE);
	}
#ifdef CO_PLATFORM_WIN_X64
	else if (TypeTraits<int>::GetMetaDataType() == pMDType)
	{
		int *pI(new int);
		*pI = static_cast<int>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pI;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<unsigned int>::GetMetaDataType() == pMDType)
	{
		unsigned int *pUI(new unsigned int);
		*pUI = static_cast<unsigned int>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pUI;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<long>::GetMetaDataType() == pMDType)
	{
		long *pL(new long);
		*pL = static_cast<long>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pL;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<unsigned long>::GetMetaDataType() == pMDType)
	{
		unsigned long *pUL(new unsigned long);
		*pUL = static_cast<unsigned long>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pUL;
		return sizeof(TD_INT_TYPE);
	}
#endif
	else
	{
#ifdef CO_PLATFORM_WIN_X64
		if (pMDType->GetSize() > MD_FUNC_VAR_PARAM_ELE_STANDARD_SIZE
			|| (pMDType->GetSize() & (pMDType->GetSize() - 1)) != 0)
		{
			*pParamPtrBuffer = *reinterpret_cast<void**>(pData);
		}
		else
		{
			*pParamPtrBuffer = pData;
		}
		return MD_FUNC_VAR_PARAM_ELE_STANDARD_SIZE;
#else
		*pParamPtrBuffer = pData;
		return MD_FUNC_VAR_PARAM_SIZEOF(pMDType->GetSize());
#endif
	}
}

static inline void FreeMemAllocatedByExtractingData(const CMetaDataType *pMDType, void **pParamPtrBuffer)
{
	if (!pMDType || !pParamPtrBuffer) return;

	if (TypeTraits<char>::GetMetaDataType() == pMDType)
	{
		delete reinterpret_cast<char*>(*pParamPtrBuffer);
	}
	else if (TypeTraits<wchar_t>::GetMetaDataType() == pMDType)
	{
		delete reinterpret_cast<wchar_t*>(*pParamPtrBuffer);
	}
	else if (TypeTraits<short>::GetMetaDataType() == pMDType)
	{
		delete reinterpret_cast<short*>(*pParamPtrBuffer);
	}
	else if (TypeTraits<unsigned char>::GetMetaDataType() == pMDType)
	{
		delete reinterpret_cast<unsigned char*>(*pParamPtrBuffer);
	}
	else if (TypeTraits<unsigned short>::GetMetaDataType() == pMDType)
	{
		delete reinterpret_cast<unsigned short*>(*pParamPtrBuffer);
	}
	else if (TypeTraits<float>::GetMetaDataType() == pMDType)
	{
		delete reinterpret_cast<float*>(*pParamPtrBuffer);
	}
#ifdef CO_PLATFORM_WIN_X64
	else if (TypeTraits<long>::GetMetaDataType() == pMDType)
	{
		delete reinterpret_cast<long*>(*pParamPtrBuffer);
	}
	else if (TypeTraits<unsigned long>::GetMetaDataType() == pMDType)
	{
		delete reinterpret_cast<unsigned long*>(*pParamPtrBuffer);
	}
#endif
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

	if (m_pParamTable->size() != pParamTypes->size()) return false;

	for (size_t index = 0; index < m_pParamTable->size(); ++index)
	{
		if (m_pParamTable->at(index)->GetMDType() != pParamTypes->at(index)->GetMDType()
			|| m_pParamTable->at(index)->GetPtrLevel() != pParamTypes->at(index)->GetPtrLevel())
		{
			return false;
		}
	}
	return true;
}

bool CMetaDataFunction::CallFunction(int param_count, void **pParam, void *pReturn) const
{
	if (!m_pFunction) return false;
	SMetaDataCalledFunctionDataPacket Packet = { param_count, pParam, pReturn };
	TpMDCalledFunction pFunc(reinterpret_cast<TpMDCalledFunction>(m_pFunction));
	return pFunc(Packet);
}

bool CMetaDataFunction::CallFunction(const size_t param_count, va_list pParamList, void *pReturn) const
{
	return CallFunction(param_count, nullptr, pParamList, pReturn);
}

bool CMetaDataFunction::CallFunction(const size_t param_count, ...) const
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

bool CMetaDataFunction::CallFunction(const size_t param_count, CParamVector *pParamTypes,
									 va_list pParamList, void *pReturn) const
{
	if (!m_pFunction
		|| (!m_pParamTable && param_count != 0)
		|| (m_pParamTable && param_count != m_pParamTable->size())) return false;
	if (pParamTypes && param_count != pParamTypes->size()) return false;

	bool ret;

	TDUIntPtr param_addr;

	void **pParamPtrBuffer = nullptr;

	size_t index;
	size_t data_size_in_container;
	bool bParamsOK(true);

	SMetaDataCalledFunctionDataPacket Packet;
	TpMDCalledFunction pFunc(reinterpret_cast<TpMDCalledFunction>(m_pFunction));

	param_addr = reinterpret_cast<TDUIntPtr>(pParamList);
	if (param_count)
	{
		if (0 == param_addr) throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：参数表缺失！");
		pParamPtrBuffer = new void*[param_count];
		memset(pParamPtrBuffer, 0x00, sizeof(void*) * param_count);
	}
	try
	{
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
			{
				data_size_in_container = ExtractDataAndDataSizeInVarParamFunc(
					m_pParamTable->at(index)->GetMDType(),
					reinterpret_cast<void*>(param_addr),
					pParamPtrBuffer + index);
			}
			else
			{
				pParamPtrBuffer[index] = reinterpret_cast<void*>(param_addr);
				data_size_in_container = sizeof(void*);
			}
			param_addr += data_size_in_container;
		}

		try
		{
			if (bParamsOK)
			{
				Packet.ParamCount = static_cast<int>(param_count);
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
				if (m_pParamTable->at(index)->GetPtrLevel() <= 0)
					FreeMemAllocatedByExtractingData(m_pParamTable->at(index)->GetMDType(), pParamPtrBuffer + index);
			}
			throw;
		}
		for (index = 0; index < param_count; ++index)
		{
			if (m_pParamTable->at(index)->GetPtrLevel() <= 0)
				FreeMemAllocatedByExtractingData(m_pParamTable->at(index)->GetMDType(), pParamPtrBuffer + index);
		}
	}
	catch(...)
	{
		if (pParamPtrBuffer) delete [] pParamPtrBuffer;
		throw;
	}
	if (pParamPtrBuffer) delete [] pParamPtrBuffer;

	return ret;
}