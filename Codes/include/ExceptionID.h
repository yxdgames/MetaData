#pragma once

#define D_E_ID_ERROR								(-1)

//MetaData
#define D_E_ID_ERR_MD_BEGIN							(-2)
#define D_E_ID_ERR_MD								(D_E_ID_ERR_MD_BEGIN - 0)
#define D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC		(D_E_ID_ERR_MD_BEGIN - 1) //函数元数据调用异常

#define D_E_ID_ERR_MD_END							(-100)

//Serialization
#define D_E_ID_ERR_SERIAL_BEGIN						(-100)
#define D_E_ID_ERR_SERIAL							(D_E_ID_ERR_SERIAL_BEGIN - 0)

#define D_E_ID_ERR_SERIAL_END						(-200)