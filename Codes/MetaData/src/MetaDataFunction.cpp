#include "stdafx.h"
#include "../include/MetaDataFunction.h"
#include "../include/TypeTraits.h"
#include "../include/ExceptionMetaData.h"
#include "../include/ExceptionIDMetaData.h"
#include <stdarg.h>

#if defined(CO_OS_WIN)
#ifdef CO_MACHINE_X64
typedef __int64			TD_INT_TYPE;
typedef double			TD_FLOAT_TYPE;

#define MD_FUNC_VAR_PARAM_ELE_STANDARD_SIZE		sizeof(__int64)
#else // CO_MACHINE_X86
typedef int				TD_INT_TYPE;
typedef double			TD_FLOAT_TYPE;

#define MD_FUNC_VAR_PARAM_SIZEOF(n)   ( ((n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#endif
#elif defined(CO_OS_LINUX)
#ifdef CO_MACHINE_X64
typedef uint64_t		TD_INT_TYPE;
typedef double			TD_FLOAT_TYPE;
#else // CO_MACHINE_X86
// typedef int				TD_INT_TYPE;
// typedef double			TD_FLOAT_TYPE;
#endif
#else
// Unknown
#endif

#if defined(CO_OS_WIN)
//提取变参函数里的参数数据值及其Size.
static inline size_t ExtractDataAndDataSizeInVarParamFunc(const CMetaDataType *pMDType, void *pData, /*out*/void **pParamPtrBuffer)
{	
	if (!pMDType || !pData || !pParamPtrBuffer) return 0;

	if (TypeTraits<char>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<char*>(pData) = static_cast<char>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<wchar_t>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<wchar_t*>(pData) = static_cast<wchar_t>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<short>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<short*>(pData) = static_cast<short>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<unsigned char>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<unsigned char*>(pData) = static_cast<unsigned char>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<unsigned short>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<unsigned short*>(pData) = static_cast<unsigned short>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<float>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<float*>(pData) = static_cast<float>(*reinterpret_cast<TD_FLOAT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_FLOAT_TYPE);
	}
#ifdef CO_MACHINE_X64
	else if (TypeTraits<int>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<int*>(pData) = static_cast<int>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<unsigned int>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<unsigned int*>(pData) = static_cast<unsigned int>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<long>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<long*>(pData) = static_cast<long>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
	else if (TypeTraits<unsigned long>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<unsigned long*>(pData) = static_cast<unsigned long>(*reinterpret_cast<TD_INT_TYPE*>(pData));
		*pParamPtrBuffer = pData;
		return sizeof(TD_INT_TYPE);
	}
#endif
	else
	{
#ifdef CO_MACHINE_X64
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
#elif defined(CO_OS_LINUX)
static inline void AdjustFuncVarParam(const CMetaDataType *pMDType, void *pData)
{
	if (!pMDType || !pData) return;

	if (TypeTraits<char>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<char*>(pData) = static_cast<char>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
	else if (TypeTraits<wchar_t>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<wchar_t*>(pData) = static_cast<wchar_t>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
	else if (TypeTraits<short>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<short*>(pData) = static_cast<short>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
	else if (TypeTraits<int>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<int*>(pData) = static_cast<int>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
	else if (TypeTraits<long>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<long*>(pData) = static_cast<long>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
	else if (TypeTraits<unsigned char>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<unsigned char*>(pData) = static_cast<unsigned char>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
	else if (TypeTraits<unsigned short>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<unsigned short*>(pData) = static_cast<unsigned short>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
	else if (TypeTraits<unsigned int>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<unsigned int*>(pData) = static_cast<unsigned int>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
	else if (TypeTraits<unsigned long>::GetMetaDataType() == pMDType)
	{
		*reinterpret_cast<unsigned long*>(pData) = static_cast<unsigned long>(*reinterpret_cast<TD_INT_TYPE*>(pData));
	}
}
#else
// Unknown
#endif

//CFuncParamMDVector
CFuncParamMDVector::CFuncParamMDVector()
	: m_pMDVarBaseVector(new std::vector<const CMetaDataVarBase*>)
{
}

CFuncParamMDVector::~CFuncParamMDVector(void)
{
	std::vector<const CMetaDataVarBase*>::iterator itr;
	for (itr = this->m_pMDVarBaseVector->begin(); itr != this->m_pMDVarBaseVector->end(); ++itr)
	{
		delete (*itr);
	}
	delete m_pMDVarBaseVector;
}

void CFuncParamMDVector::push_back(const CMetaDataVarBase *value)
{
	m_pMDVarBaseVector->push_back(value);
}

void CFuncParamMDVector::clear(void)
{
	m_pMDVarBaseVector->clear();
}

size_t CFuncParamMDVector::size(void)
{
	return m_pMDVarBaseVector->size();
}

const CMetaDataVarBase *CFuncParamMDVector::at(size_t index)
{
	return m_pMDVarBaseVector->at(index);
}

std::vector<const CMetaDataVarBase*>::iterator CFuncParamMDVector::begin(void)
{
	return m_pMDVarBaseVector->begin();
}

std::vector<const CMetaDataVarBase*>::iterator CFuncParamMDVector::end(void)
{
	return m_pMDVarBaseVector->end();
}

//CMetaDataFunction
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
		CFuncParamMDVector *pParamTable(GetParamTable());
		pParamTable->push_back(pParam);
	}
}

void CMetaDataFunction::SetReturnInfo(const CMetaDataVarBase *pRet)
{
	if (m_pReturnInfo)
		delete m_pReturnInfo;
	m_pReturnInfo = pRet;
}

bool CMetaDataFunction::FuncParamsCheck(CFuncParamMDVector *pParamMDVector) const
{
	if (!m_pParamTable)
	{
		return (!pParamMDVector) || (pParamMDVector->size() == 0);
	}
	else if (!pParamMDVector)
	{
		return (!m_pParamTable) || (m_pParamTable->size() == 0);
	}

	if (m_pParamTable->size() != pParamMDVector->size()) return false;

	for (size_t index = 0; index < m_pParamTable->size(); ++index)
	{
		if (m_pParamTable->at(index)->GetMDType() != pParamMDVector->at(index)->GetMDType()
			|| m_pParamTable->at(index)->GetPtrLevel() != pParamMDVector->at(index)->GetPtrLevel())
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
	return reinterpret_cast<TpMDCalledFunction>(m_pFunction)(Packet);
}

#if defined(CO_OS_WIN)
bool CMetaDataFunction::CallFunction(const size_t param_count, va_list pParamList, void *pReturn) const
{
	return CallFunction(param_count, nullptr, pParamList, pReturn);
}
#elif defined(CO_OS_LINUX)
#ifdef CO_MACHINE_X64
bool CMetaDataFunction::CallFunction(const size_t param_count, uint64_t reg_params[], const int reg_param_num,
	__uint128_t xmm_params[], const int xmm_param_num,
	uint8_t stack_params[], void *pReturn) const
{
	return CallFunction(param_count, static_cast<CFuncParamMDVector*>(nullptr),
		reg_params, reg_param_num,
		xmm_params, xmm_param_num,
		stack_params, pReturn);
}
#else //CO_MACHINE_X86
	// Unknown
#endif
#else
	// Unknown
#endif

bool CMetaDataFunction::CallFunction(const size_t param_count, ...) const
{
	bool ret;
#if defined(CO_OS_WIN)
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
#elif defined(CO_OS_LINUX)
#ifdef CO_MACHINE_X64
	register uint64_t reg_rbp asm("rbp");
	// register uint64_t reg_rdi asm("rdi");
	// register uint64_t reg_rsi asm("rsi");
	register uint64_t reg_rdx asm("rdx");
	register uint64_t reg_rcx asm("rcx");
	register uint64_t reg_r8 asm("r8");
	register uint64_t reg_r9 asm("r9");
	uint64_t reg_params[4] = {
		// reg_rdi, reg_rsi,
		reg_rdx, reg_rcx, reg_r8, reg_r9,
	};
	register __uint128_t reg_xmm0 asm("xmm0");
    register __uint128_t reg_xmm1 asm("xmm1");
    register __uint128_t reg_xmm2 asm("xmm2");
    register __uint128_t reg_xmm3 asm("xmm3");
    register __uint128_t reg_xmm4 asm("xmm4");
    register __uint128_t reg_xmm5 asm("xmm5");
    register __uint128_t reg_xmm6 asm("xmm6");
    register __uint128_t reg_xmm7 asm("xmm7");
	__uint128_t xmm_params[8] = {
		reg_xmm0, reg_xmm1, reg_xmm2, reg_xmm3, reg_xmm4, reg_xmm5, reg_xmm6, reg_xmm7,
	};
	ret = CallFunction(param_count, reg_params, sizeof(reg_params) / sizeof(uint64_t),
		xmm_params, sizeof(xmm_params) / sizeof(__uint128_t),
		reinterpret_cast<uint8_t*>(reg_rbp + sizeof(uintptr_t) * 2), nullptr);
#else //CO_MACHINE_X86
	ret = false;
#endif
#else
	ret = false;
#endif
	return ret;
}

#if defined(CO_OS_WIN)
bool CMetaDataFunction::CallFunction(CFuncParamMDVector *pParamMDVector, va_list pParamList, void *pReturn) const
{
	if (pParamMDVector)
		return CallFunction(pParamMDVector->size(), pParamMDVector, pParamList, pReturn);
	else return CallFunction(static_cast<size_t>(0), nullptr, pParamList, pReturn);
}
#elif defined(CO_OS_LINUX)
#ifdef CO_MACHINE_X64
bool CMetaDataFunction::CallFunction(CFuncParamMDVector *pParamMDVector, uint64_t reg_params[], const int reg_param_num,
	__uint128_t xmm_params[], const int xmm_param_num,
	uint8_t stack_params[], void *pReturn) const
{
	if (pParamMDVector)
		return CallFunction(pParamMDVector->size(), pParamMDVector,
			reg_params, reg_param_num,
			xmm_params, xmm_param_num,
			stack_params, pReturn);
	else return CallFunction(static_cast<size_t>(0), static_cast<CFuncParamMDVector*>(nullptr),
			reg_params, reg_param_num,
			xmm_params, xmm_param_num,
			stack_params, pReturn);
}
#else //CO_MACHINE_X86
	// Unknown
#endif
#else
	// Unknown
#endif

bool CMetaDataFunction::CallFunction(CFuncParamMDVector *pParamMDVector, ...) const
{
	bool ret;
#if defined(CO_OS_WIN)
	va_list pList;
	va_start(pList, pParamMDVector);
	try
	{
		ret = CallFunction(pParamMDVector, pList, nullptr);
	}
	catch(...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);
#elif defined(CO_OS_LINUX)
#ifdef CO_MACHINE_X64
	register uint64_t reg_rbp asm("rbp");
	// register uint64_t reg_rdi asm("rdi");
	// register uint64_t reg_rsi asm("rsi");
	register uint64_t reg_rdx asm("rdx");
	register uint64_t reg_rcx asm("rcx");
	register uint64_t reg_r8 asm("r8");
	register uint64_t reg_r9 asm("r9");
	uint64_t reg_params[4] = {
		// reg_rdi, reg_rsi,
		reg_rdx, reg_rcx, reg_r8, reg_r9,
	};
	register __uint128_t reg_xmm0 asm("xmm0");
    register __uint128_t reg_xmm1 asm("xmm1");
    register __uint128_t reg_xmm2 asm("xmm2");
    register __uint128_t reg_xmm3 asm("xmm3");
    register __uint128_t reg_xmm4 asm("xmm4");
    register __uint128_t reg_xmm5 asm("xmm5");
    register __uint128_t reg_xmm6 asm("xmm6");
    register __uint128_t reg_xmm7 asm("xmm7");
	__uint128_t xmm_params[8] = {
		reg_xmm0, reg_xmm1, reg_xmm2, reg_xmm3, reg_xmm4, reg_xmm5, reg_xmm6, reg_xmm7,
	};
	ret = CallFunction(pParamMDVector, reg_params, sizeof(reg_params) / sizeof(uint64_t),
		xmm_params, sizeof(xmm_params) / sizeof(__uint128_t),
		reinterpret_cast<uint8_t*>(reg_rbp + sizeof(uintptr_t) * 2), nullptr);
#else //CO_MACHINE_X86
	ret = false;
#endif
#else
	ret = false;
#endif
	return ret;
}

#if defined(CO_OS_WIN)
bool CMetaDataFunction::CallFunction(const size_t param_count, CFuncParamMDVector *pParamMDVector,
									 va_list pParamList, void *pReturn) const
{
	if (!m_pFunction
		|| (!m_pParamTable && param_count != 0)
		|| (m_pParamTable && param_count != m_pParamTable->size())) return false;
	if (pParamMDVector && param_count != pParamMDVector->size()) return false;

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
			if (pParamMDVector)
			{
				if (pParamMDVector->at(index)->GetMDType() != m_pParamTable->at(index)->GetMDType()
					|| pParamMDVector->at(index)->GetPtrLevel() != m_pParamTable->at(index)->GetPtrLevel())
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
	catch(...)
	{
		if (pParamPtrBuffer) delete [] pParamPtrBuffer;
		throw;
	}
	if (pParamPtrBuffer) delete [] pParamPtrBuffer;

	return ret;
}
#elif defined(CO_OS_LINUX)
#ifdef CO_MACHINE_X64
bool CMetaDataFunction::CallFunction(const size_t param_count, CFuncParamMDVector *pParamMDVector,
									uint64_t reg_params[], const int reg_param_num,
									__uint128_t xmm_params[], const int xmm_param_num,
									uint8_t stack_params[], void *pReturn) const
{
	if (!m_pFunction
		|| (!m_pParamTable && param_count != 0)
		|| (m_pParamTable && param_count != m_pParamTable->size())) return false;
	if (pParamMDVector && param_count != pParamMDVector->size()) return false;

	bool ret;
	bool bParamsOK(true);
	size_t data_size_in_container;
	uint16_t reg_param_index(0);
	uint16_t xmm_param_index(0);
	void **pParamPtrBuffer = nullptr;
	if (param_count)
	{
		if (!reg_params) throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：参数表缺失！");
		pParamPtrBuffer = new void*[param_count];
		memset(pParamPtrBuffer, 0x00, sizeof(void*) * param_count);
	}
	try
	{
		for (size_t index = 0; index < param_count; ++index)
		{
			if (pParamMDVector)
			{
				if (pParamMDVector->at(index)->GetMDType() != m_pParamTable->at(index)->GetMDType()
					|| pParamMDVector->at(index)->GetPtrLevel() != m_pParamTable->at(index)->GetPtrLevel())
				{
					bParamsOK = false;
					break;
				}
			}
			if (m_pParamTable->at(index)->GetPtrLevel() <= 0)
			{
				if (m_pParamTable->at(index)->GetMDType()->GetTypeID() == D_META_DATA_TYPE_ID_CLASS_TYPE
					|| m_pParamTable->at(index)->GetMDType()->GetTypeID() == D_META_DATA_TYPE_ID_INTERFACE)
				{
					data_size_in_container = sizeof(void*);
					if (reg_param_index < reg_param_num)
						goto segment_reg_params_ptr;
					else goto segment_stack_params_ptr;
				}
				else if (m_pParamTable->at(index)->GetSize() > sizeof(uint64_t) * 2)
				{
					data_size_in_container = (m_pParamTable->at(index)->GetSize() + 7) & (~static_cast<uint64_t>(0x07));
					goto segment_stack_params;
				}
				else if (m_pParamTable->at(index)->GetSize() > sizeof(uint64_t))
				{
					data_size_in_container = sizeof(uint64_t) * 2;
					if (reg_param_index + 1 < reg_param_num)
						goto segment_reg_params;
					else goto segment_stack_params;
				}
				else
				{
					data_size_in_container = sizeof(uint64_t);
					if (TypeTraits<float>::GetMetaDataType() == m_pParamTable->at(index)->GetMDType()
						|| TypeTraits<double>::GetMetaDataType() == m_pParamTable->at(index)->GetMDType())
					{
						if (xmm_param_index < xmm_param_num)
						{
							auto data = xmm_params + xmm_param_index;
							*reinterpret_cast<uint64_t*>(data) = static_cast<uint64_t>(*reinterpret_cast<__uint128_t*>(data));
							if (TypeTraits<float>::GetMetaDataType() == m_pParamTable->at(index)->GetMDType())
								*reinterpret_cast<float*>(data) = static_cast<float>(*reinterpret_cast<double*>(data));
							goto segment_xmm_params;
						}
						else
						{
							if (TypeTraits<float>::GetMetaDataType() == m_pParamTable->at(index)->GetMDType())
								*reinterpret_cast<float*>(stack_params) = static_cast<float>(*reinterpret_cast<double*>(stack_params));
							goto segment_stack_params;
						}
					}
					else
					{
						if (reg_param_index < reg_param_num)
						{
							::AdjustFuncVarParam(m_pParamTable->at(index)->GetMDType(), reg_params + reg_param_index);
							goto segment_reg_params;
						}
						else
						{
							::AdjustFuncVarParam(m_pParamTable->at(index)->GetMDType(), stack_params);
							goto segment_stack_params;
						}
					}
				}
			}
			else
			{
				data_size_in_container = sizeof(void*);
				if (reg_param_index < reg_param_num)
					goto segment_reg_params;
				else goto segment_stack_params;
			}
			segment_reg_params:
				pParamPtrBuffer[index] = reinterpret_cast<void*>(reg_params + reg_param_index);
				reg_param_index += (data_size_in_container >> 3); // sizeof(uint64_t)
				continue;
			segment_reg_params_ptr:
				pParamPtrBuffer[index] = *reinterpret_cast<void**>(reg_params + reg_param_index);
				++reg_param_index;
				continue;
			segment_stack_params:
				pParamPtrBuffer[index] = reinterpret_cast<void*>(stack_params);
				stack_params += data_size_in_container;
				continue;
			segment_stack_params_ptr:
				pParamPtrBuffer[index] = *reinterpret_cast<void**>(stack_params);
				stack_params += data_size_in_container;
				continue;
			segment_xmm_params:
				pParamPtrBuffer[index] = reinterpret_cast<void*>(xmm_params + xmm_param_index);
				++xmm_param_index;
				continue;
		}

		if (bParamsOK)
		{
			SMetaDataCalledFunctionDataPacket Packet;
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
					if (reg_param_index < reg_param_num)
					{
						if (!reg_params) throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：参数表缺失！");
						Packet.pReturn = *reinterpret_cast<void**>(reg_params + reg_param_index);
					}
					else
					{
						if (!stack_params) throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：参数表缺失！");
						Packet.pReturn = *reinterpret_cast<void**>(stack_params);
					}
				}
			}
			else Packet.pReturn = nullptr;

			ret = reinterpret_cast<TpMDCalledFunction>(m_pFunction)(Packet);
		}
		else ret = false;
	}
	catch(...)
	{
		if (pParamPtrBuffer) delete[] pParamPtrBuffer;
		throw;
	}
	if (pParamPtrBuffer) delete[] pParamPtrBuffer;

	return ret;
}
#else //CO_MACHINE_X86
	// Unknown
#endif
#else
	// Unknown
#endif