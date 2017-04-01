#pragma once

#include "..\include\MetaDataSupport.h"

//#define	__META_DATA_DEMO__

#ifdef __META_DATA_DEMO__
////////////////////////////////////////////////
//                  Demo                      //
////////////////////////////////////////////////

class CClass1
{
public:
	CClass1(void);
	~CClass1(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass1)
MD_CLASS_TYPE_DECLARE_END(CClass1)
};

class CClass1_Derived1 : public CClass1
{
public:
	CClass1_Derived1(void);
	~CClass1_Derived1(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Derived1)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass1_Derived1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1)
MD_CLASS_TYPE_DECLARE_END(CClass1_Derived1)
};

class CClass1_Derived2 : public CClass1
{
public:
	CClass1_Derived2(void);
	~CClass1_Derived2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Derived2)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass1_Derived2)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1)
MD_CLASS_TYPE_DECLARE_END(CClass1_Derived2)
};


class CClass1_Descendant1 : public CClass1_Derived1
{
public:
	CClass1_Descendant1(void);
	~CClass1_Descendant1(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant1)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass1_Descendant1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Derived1)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant1)
};

class CClass1_Descendant2 : public CClass1_Derived2
{
public:
	CClass1_Descendant2(void);
	~CClass1_Descendant2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant2)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass1_Descendant2)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Derived2)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant2)
};

class CClass1_Descendant3 : public CClass1_Derived1, public CClass1_Derived2
{
public:
	CClass1_Descendant3(void);
	~CClass1_Descendant3(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant3)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass1_Descendant3)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Derived1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Derived2)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant3)
};

class CClass1_Descendant4 : public CClass1_Descendant2
{
public:
	CClass1_Descendant4(void);
	~CClass1_Descendant4(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant4)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass1_Descendant4)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Descendant2)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant4)
};

class CClass1_Descendant5 : public CClass1_Descendant3
{
public:
	CClass1_Descendant5(void);
	~CClass1_Descendant5(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant5)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass1_Descendant5)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Descendant3)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant5)
};

class CClass2
{
public:
	CClass2(void);
	virtual ~CClass2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass2)
MD_CLASS_TYPE_DECLARE_END(CClass2)
};

class CClass2_Derived1 : public CClass2
{
public:
	CClass2_Derived1(void);
	virtual ~CClass2_Derived1(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Derived1)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass2_Derived1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Derived1)
};

class CClass2_Derived2 : public CClass2
{
public:
	CClass2_Derived2(void);
	virtual ~CClass2_Derived2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Derived2)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass2_Derived2)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Derived2)
};

class CClass2_Descendant1 : public CClass2_Derived1
{
public:
	CClass2_Descendant1(void);
	virtual ~CClass2_Descendant1(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant1)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass2_Descendant1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Derived1)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant1)
};

class CClass2_Descendant2 : public CClass2_Derived2
{
public:
	CClass2_Descendant2(void);
	virtual ~CClass2_Descendant2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant2)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass2_Descendant2)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Derived2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant2)
};

class CClass2_Descendant3 : public CClass2_Derived1, public CClass2_Derived2
{
public:
	CClass2_Descendant3(void);
	virtual ~CClass2_Descendant3(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant3)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass2_Descendant3)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Derived1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Derived2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant3)
};

class CClass2_Descendant4 : public CClass2_Descendant2
{
public:
	CClass2_Descendant4(void);
	virtual ~CClass2_Descendant4(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant4)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass2_Descendant4)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Descendant2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant4)
};

class CClass2_Descendant5 : public CClass2_Descendant3
{
public:
	CClass2_Descendant5(void);
	virtual ~CClass2_Descendant5(void);
MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant5)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass2_Descendant5)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Descendant3)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant5)
};

class CClass3
{
public:
	CClass3(void);
	~CClass3(void);
public:
	class CClass3_Inner1
	{
	public:
		CClass3_Inner1(void);
		~CClass3_Inner1(void);
	};
	class CClass3_Inner2
	{
	public:
		CClass3_Inner2(void);
		virtual ~CClass3_Inner2(void);
	};
	class CClass3_Inner3
	{
	public:
		CClass3_Inner3(void);
		~CClass3_Inner3(void);
	public:
		class CClass3_Inner3_Inner1
		{
		public:
			CClass3_Inner3_Inner1(void);
			~CClass3_Inner3_Inner1(void);
		};
	};
	class CClass3_Inner1_Derived1 : public CClass3_Inner1
	{
	public:
		CClass3_Inner1_Derived1(void);
		~CClass3_Inner1_Derived1(void);
	};
	class CClass3_Inner1_Derived2 : public CClass3_Inner1
	{
	public:
		CClass3_Inner1_Derived2(void);
		~CClass3_Inner1_Derived2(void);
	};
	class CClass3_Inner1_Descendant1 : public CClass3_Inner1_Derived1
	{
	public:
		CClass3_Inner1_Descendant1(void);
		~CClass3_Inner1_Descendant1(void);
	};
	class CClass3_Inner1_Descendant2 : public CClass3_Inner1_Derived2
	{
	public:
		CClass3_Inner1_Descendant2(void);
		~CClass3_Inner1_Descendant2(void);
	};
	class CClass3_Inner1_Descendant3 : public CClass3_Inner1_Derived1, public CClass3_Inner1_Derived2
	{
	public:
		CClass3_Inner1_Descendant3(void);
		~CClass3_Inner1_Descendant3(void);
	};
	class CClass3_Inner1_Descendant4 : public CClass3_Inner1_Descendant2
	{
	public:
		CClass3_Inner1_Descendant4(void);
		~CClass3_Inner1_Descendant4(void);
	};
	class CClass3_Inner1_Descendant5 : public CClass3_Inner1_Descendant3
	{
	public:
		CClass3_Inner1_Descendant5(void);
		~CClass3_Inner1_Descendant5(void);
	};

MD_CLASS_TYPE_DECLARE_BEGIN(CClass3)
MD_CLASS_TYPE_DECLARE_DETAIL(CClass3)
MD_CLASS_TYPE_DECLARE_END(CClass3)
};

namespace NameSpace1{
	class NS1_CClass1
	{
	public:
		NS1_CClass1(void);
		~NS1_CClass1(void);
	};

	class NS1_CClass1_Derived1 : public NS1_CClass1
	{
	public:
		NS1_CClass1_Derived1(void);
		~NS1_CClass1_Derived1(void);
	};

	class NS1_CClass1_Derived2 : public NS1_CClass1
	{
	public:
		NS1_CClass1_Derived2(void);
		~NS1_CClass1_Derived2(void);
	};


	class NS1_CClass1_Descendant1 : public NS1_CClass1_Derived1
	{
	public:
		NS1_CClass1_Descendant1(void);
		~NS1_CClass1_Descendant1(void);
	};

	class NS1_CClass1_Descendant2 : public NS1_CClass1_Derived2
	{
	public:
		NS1_CClass1_Descendant2(void);
		~NS1_CClass1_Descendant2(void);
	};

	class NS1_CClass1_Descendant3 : public NS1_CClass1_Derived1, public NS1_CClass1_Derived2
	{
	public:
		NS1_CClass1_Descendant3(void);
		~NS1_CClass1_Descendant3(void);
	};

	class NS1_CClass1_Descendant4 : public NS1_CClass1_Descendant2
	{
	public:
		NS1_CClass1_Descendant4(void);
		~NS1_CClass1_Descendant4(void);
	};

	class NS1_CClass1_Descendant5 : public NS1_CClass1_Descendant3
	{
	public:
		NS1_CClass1_Descendant5(void);
		~NS1_CClass1_Descendant5(void);
	};

	class NS1_CClass2
	{
	public:
		NS1_CClass2(void);
		virtual ~NS1_CClass2(void);
	};

	class NS1_CClass2_Derived1 : public NS1_CClass2
	{
	public:
		NS1_CClass2_Derived1(void);
		virtual ~NS1_CClass2_Derived1(void);
	};

	class NS1_CClass2_Derived2 : public NS1_CClass2
	{
	public:
		NS1_CClass2_Derived2(void);
		virtual ~NS1_CClass2_Derived2(void);
	};

	class NS1_CClass2_Descendant1 : public NS1_CClass2_Derived1
	{
	public:
		NS1_CClass2_Descendant1(void);
		virtual ~NS1_CClass2_Descendant1(void);
	};

	class NS1_CClass2_Descendant2 : public NS1_CClass2_Derived2
	{
	public:
		NS1_CClass2_Descendant2(void);
		virtual ~NS1_CClass2_Descendant2(void);
	};

	class NS1_CClass2_Descendant3 : public NS1_CClass2_Derived1, public NS1_CClass2_Derived2
	{
	public:
		NS1_CClass2_Descendant3(void);
		virtual ~NS1_CClass2_Descendant3(void);
	};

	class NS1_CClass2_Descendant4 : public NS1_CClass2_Descendant2
	{
	public:
		NS1_CClass2_Descendant4(void);
		virtual ~NS1_CClass2_Descendant4(void);
	};

	class NS1_CClass2_Descendant5 : public NS1_CClass2_Descendant3
	{
	public:
		NS1_CClass2_Descendant5(void);
		virtual ~NS1_CClass2_Descendant5(void);
	};

	class NS1_CClass3
	{
	public:
		NS1_CClass3(void);
		~NS1_CClass3(void);
	public:
		class NS1_CClass3_Inner1
		{
		public:
			NS1_CClass3_Inner1(void);
			~NS1_CClass3_Inner1(void);
		};
		class NS1_CClass3_Inner2
		{
		public:
			NS1_CClass3_Inner2(void);
			virtual ~NS1_CClass3_Inner2(void);
		};
		class NS1_CClass3_Inner3
		{
		public:
			NS1_CClass3_Inner3(void);
			~NS1_CClass3_Inner3(void);
		public:
			class NS1_CClass3_Inner3_Inner1
			{
			public:
				NS1_CClass3_Inner3_Inner1(void);
				~NS1_CClass3_Inner3_Inner1(void);
			};
		};
		class NS1_CClass3_Inner1_Derived1 : public NS1_CClass3_Inner1
		{
		public:
			NS1_CClass3_Inner1_Derived1(void);
			~NS1_CClass3_Inner1_Derived1(void);
		};
		class NS1_CClass3_Inner1_Derived2 : public NS1_CClass3_Inner1
		{
		public:
			NS1_CClass3_Inner1_Derived2(void);
			~NS1_CClass3_Inner1_Derived2(void);
		};
		class NS1_CClass3_Inner1_Descendant1 : public NS1_CClass3_Inner1_Derived1
		{
		public:
			NS1_CClass3_Inner1_Descendant1(void);
			~NS1_CClass3_Inner1_Descendant1(void);
		};
		class NS1_CClass3_Inner1_Descendant2 : public NS1_CClass3_Inner1_Derived2
		{
		public:
			NS1_CClass3_Inner1_Descendant2(void);
			~NS1_CClass3_Inner1_Descendant2(void);
		};
		class NS1_CClass3_Inner1_Descendant3 : public NS1_CClass3_Inner1_Derived1, public NS1_CClass3_Inner1_Derived2
		{
		public:
			NS1_CClass3_Inner1_Descendant3(void);
			~NS1_CClass3_Inner1_Descendant3(void);
		};
		class NS1_CClass3_Inner1_Descendant4 : public NS1_CClass3_Inner1_Descendant2
		{
		public:
			NS1_CClass3_Inner1_Descendant4(void);
			~NS1_CClass3_Inner1_Descendant4(void);
		};
		class NS1_CClass3_Inner1_Descendant5 : public NS1_CClass3_Inner1_Descendant3
		{
		public:
			NS1_CClass3_Inner1_Descendant5(void);
			~NS1_CClass3_Inner1_Descendant5(void);
		};
	};
	namespace NameSpasce1_Sub1
	{
		class NS1_Sub1_CClass1
		{
		public:
			NS1_Sub1_CClass1(void);
			~NS1_Sub1_CClass1(void);
		};

		class NS1_Sub1_CClass1_Derived1 : public NS1_Sub1_CClass1
		{
		public:
			NS1_Sub1_CClass1_Derived1(void);
			~NS1_Sub1_CClass1_Derived1(void);
		};

		class NS1_Sub1_CClass1_Derived2 : public NS1_Sub1_CClass1
		{
		public:
			NS1_Sub1_CClass1_Derived2(void);
			~NS1_Sub1_CClass1_Derived2(void);
		};


		class NS1_Sub1_CClass1_Descendant1 : public NS1_Sub1_CClass1_Derived1
		{
		public:
			NS1_Sub1_CClass1_Descendant1(void);
			~NS1_Sub1_CClass1_Descendant1(void);
		};

		class NS1_Sub1_CClass1_Descendant2 : public NS1_Sub1_CClass1_Derived2
		{
		public:
			NS1_Sub1_CClass1_Descendant2(void);
			~NS1_Sub1_CClass1_Descendant2(void);
		};

		class NS1_Sub1_CClass1_Descendant3 : public NS1_Sub1_CClass1_Derived1, public NS1_Sub1_CClass1_Derived2
		{
		public:
			NS1_Sub1_CClass1_Descendant3(void);
			~NS1_Sub1_CClass1_Descendant3(void);
		};

		class NS1_Sub1_CClass1_Descendant4 : public NS1_Sub1_CClass1_Descendant2
		{
		public:
			NS1_Sub1_CClass1_Descendant4(void);
			~NS1_Sub1_CClass1_Descendant4(void);
		};

		class NS1_Sub1_CClass1_Descendant5 : public NS1_Sub1_CClass1_Descendant3
		{
		public:
			NS1_Sub1_CClass1_Descendant5(void);
			~NS1_Sub1_CClass1_Descendant5(void);
		};

		class NS1_Sub1_CClass2
		{
		public:
			NS1_Sub1_CClass2(void);
			virtual ~NS1_Sub1_CClass2(void);
		};

		class NS1_Sub1_CClass2_Derived1 : public NS1_Sub1_CClass2
		{
		public:
			NS1_Sub1_CClass2_Derived1(void);
			virtual ~NS1_Sub1_CClass2_Derived1(void);
		};

		class NS1_Sub1_CClass2_Derived2 : public NS1_Sub1_CClass2
		{
		public:
			NS1_Sub1_CClass2_Derived2(void);
			virtual ~NS1_Sub1_CClass2_Derived2(void);
		};

		class NS1_Sub1_CClass2_Descendant1 : public NS1_Sub1_CClass2_Derived1
		{
		public:
			NS1_Sub1_CClass2_Descendant1(void);
			virtual ~NS1_Sub1_CClass2_Descendant1(void);
		};

		class NS1_Sub1_CClass2_Descendant2 : public NS1_Sub1_CClass2_Derived2
		{
		public:
			NS1_Sub1_CClass2_Descendant2(void);
			virtual ~NS1_Sub1_CClass2_Descendant2(void);
		};

		class NS1_Sub1_CClass2_Descendant3 : public NS1_Sub1_CClass2_Derived1, public NS1_Sub1_CClass2_Derived2
		{
		public:
			NS1_Sub1_CClass2_Descendant3(void);
			virtual ~NS1_Sub1_CClass2_Descendant3(void);
		};

		class NS1_Sub1_CClass2_Descendant4 : public NS1_Sub1_CClass2_Descendant2
		{
		public:
			NS1_Sub1_CClass2_Descendant4(void);
			virtual ~NS1_Sub1_CClass2_Descendant4(void);
		};

		class NS1_Sub1_CClass2_Descendant5 : public NS1_Sub1_CClass2_Descendant3
		{
		public:
			NS1_Sub1_CClass2_Descendant5(void);
			virtual ~NS1_Sub1_CClass2_Descendant5(void);
		};

		class NS1_Sub1_CClass3
		{
		public:
			NS1_Sub1_CClass3(void);
			~NS1_Sub1_CClass3(void);
		public:
			class NS1_Sub1_CClass3_Inner1
			{
			public:
				NS1_Sub1_CClass3_Inner1(void);
				~NS1_Sub1_CClass3_Inner1(void);
			};
			class NS1_Sub1_CClass3_Inner2
			{
			public:
				NS1_Sub1_CClass3_Inner2(void);
				virtual ~NS1_Sub1_CClass3_Inner2(void);
			};
			class NS1_Sub1_CClass3_Inner3
			{
			public:
				NS1_Sub1_CClass3_Inner3(void);
				~NS1_Sub1_CClass3_Inner3(void);
			public:
				class NS1_Sub1_CClass3_Inner3_Inner1
				{
				public:
					NS1_Sub1_CClass3_Inner3_Inner1(void);
					~NS1_Sub1_CClass3_Inner3_Inner1(void);
				};
			};
			class NS1_Sub1_CClass3_Inner1_Derived1 : public NS1_Sub1_CClass3_Inner1
			{
			public:
				NS1_Sub1_CClass3_Inner1_Derived1(void);
				~NS1_Sub1_CClass3_Inner1_Derived1(void);
			};
			class NS1_Sub1_CClass3_Inner1_Derived2 : public NS1_Sub1_CClass3_Inner1
			{
			public:
				NS1_Sub1_CClass3_Inner1_Derived2(void);
				~NS1_Sub1_CClass3_Inner1_Derived2(void);
			};
			class NS1_Sub1_CClass3_Inner1_Descendant1 : public NS1_Sub1_CClass3_Inner1_Derived1
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant1(void);
				~NS1_Sub1_CClass3_Inner1_Descendant1(void);
			};
			class NS1_Sub1_CClass3_Inner1_Descendant2 : public NS1_Sub1_CClass3_Inner1_Derived2
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant2(void);
				~NS1_Sub1_CClass3_Inner1_Descendant2(void);
			};
			class NS1_Sub1_CClass3_Inner1_Descendant3 : public NS1_Sub1_CClass3_Inner1_Derived1, public NS1_Sub1_CClass3_Inner1_Derived2
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant3(void);
				~NS1_Sub1_CClass3_Inner1_Descendant3(void);
			};
			class NS1_Sub1_CClass3_Inner1_Descendant4 : public NS1_Sub1_CClass3_Inner1_Descendant2
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant4(void);
				~NS1_Sub1_CClass3_Inner1_Descendant4(void);
			};
			class NS1_Sub1_CClass3_Inner1_Descendant5 : public NS1_Sub1_CClass3_Inner1_Descendant3
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant5(void);
				~NS1_Sub1_CClass3_Inner1_Descendant5(void);
			};
		};

		namespace NameSpasce1_Sub1_Sub1
		{
			class NS1_Sub1_Sub1_CClass1
			{
			public:
				NS1_Sub1_Sub1_CClass1(void);
				~NS1_Sub1_Sub1_CClass1(void);
			};

			class NS1_Sub1_Sub1_CClass1_Derived1 : public NS1_Sub1_Sub1_CClass1
			{
			public:
				NS1_Sub1_Sub1_CClass1_Derived1(void);
				~NS1_Sub1_Sub1_CClass1_Derived1(void);
			};

			class NS1_Sub1_Sub1_CClass1_Derived2 : public NS1_Sub1_Sub1_CClass1
			{
			public:
				NS1_Sub1_Sub1_CClass1_Derived2(void);
				~NS1_Sub1_Sub1_CClass1_Derived2(void);
			};


			class NS1_Sub1_Sub1_CClass1_Descendant1 : public NS1_Sub1_Sub1_CClass1_Derived1
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant1(void);
				~NS1_Sub1_Sub1_CClass1_Descendant1(void);
			};

			class NS1_Sub1_Sub1_CClass1_Descendant2 : public NS1_Sub1_Sub1_CClass1_Derived2
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant2(void);
				~NS1_Sub1_Sub1_CClass1_Descendant2(void);
			};

			class NS1_Sub1_Sub1_CClass1_Descendant3 : public NS1_Sub1_Sub1_CClass1_Derived1, public NS1_Sub1_Sub1_CClass1_Derived2
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant3(void);
				~NS1_Sub1_Sub1_CClass1_Descendant3(void);
			};

			class NS1_Sub1_Sub1_CClass1_Descendant4 : public NS1_Sub1_Sub1_CClass1_Descendant2
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant4(void);
				~NS1_Sub1_Sub1_CClass1_Descendant4(void);
			};

			class NS1_Sub1_Sub1_CClass1_Descendant5 : public NS1_Sub1_Sub1_CClass1_Descendant3
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant5(void);
				~NS1_Sub1_Sub1_CClass1_Descendant5(void);
			};

			class NS1_Sub1_Sub1_CClass2
			{
			public:
				NS1_Sub1_Sub1_CClass2(void);
				virtual ~NS1_Sub1_Sub1_CClass2(void);
			};

			class NS1_Sub1_Sub1_CClass2_Derived1 : public NS1_Sub1_Sub1_CClass2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Derived1(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Derived1(void);
			};

			class NS1_Sub1_Sub1_CClass2_Derived2 : public NS1_Sub1_Sub1_CClass2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Derived2(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Derived2(void);
			};

			class NS1_Sub1_Sub1_CClass2_Descendant1 : public NS1_Sub1_Sub1_CClass2_Derived1
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant1(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant1(void);
			};

			class NS1_Sub1_Sub1_CClass2_Descendant2 : public NS1_Sub1_Sub1_CClass2_Derived2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant2(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant2(void);
			};

			class NS1_Sub1_Sub1_CClass2_Descendant3 : public NS1_Sub1_Sub1_CClass2_Derived1, public NS1_Sub1_Sub1_CClass2_Derived2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant3(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant3(void);
			};

			class NS1_Sub1_Sub1_CClass2_Descendant4 : public NS1_Sub1_Sub1_CClass2_Descendant2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant4(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant4(void);
			};

			class NS1_Sub1_Sub1_CClass2_Descendant5 : public NS1_Sub1_Sub1_CClass2_Descendant3
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant5(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant5(void);
			};

			class NS1_Sub1_Sub1_CClass3
			{
			public:
				NS1_Sub1_Sub1_CClass3(void);
				~NS1_Sub1_Sub1_CClass3(void);
			public:
				class NS1_Sub1_Sub1_CClass3_Inner1
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1(void);
					~NS1_Sub1_Sub1_CClass3_Inner1(void);
				};
				class NS1_Sub1_Sub1_CClass3_Inner2
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner2(void);
					virtual ~NS1_Sub1_Sub1_CClass3_Inner2(void);
				};
				class NS1_Sub1_Sub1_CClass3_Inner3
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner3(void);
					~NS1_Sub1_Sub1_CClass3_Inner3(void);
				public:
					class NS1_Sub1_Sub1_CClass3_Inner3_Inner1
					{
					public:
						NS1_Sub1_Sub1_CClass3_Inner3_Inner1(void);
						~NS1_Sub1_Sub1_CClass3_Inner3_Inner1(void);
					};
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Derived1 : public NS1_Sub1_Sub1_CClass3_Inner1
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Derived1(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Derived1(void);
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Derived2 : public NS1_Sub1_Sub1_CClass3_Inner1
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Derived2(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Derived2(void);
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant1 : public NS1_Sub1_Sub1_CClass3_Inner1_Derived1
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant1(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant1(void);
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant2 : public NS1_Sub1_Sub1_CClass3_Inner1_Derived2
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant2(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant2(void);
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant3 : public NS1_Sub1_Sub1_CClass3_Inner1_Derived1, public NS1_Sub1_Sub1_CClass3_Inner1_Derived2
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant3(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant3(void);
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant4 : public NS1_Sub1_Sub1_CClass3_Inner1_Descendant2
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant4(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant4(void);
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant5 : public NS1_Sub1_Sub1_CClass3_Inner1_Descendant3
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant5(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant5(void);
				};
			};
		} //NameSpasce1_Sub1_Sub1
	} //NameSpasce1_Sub1
} //NameSpasce1

#endif //__META_DATA_DEMO__