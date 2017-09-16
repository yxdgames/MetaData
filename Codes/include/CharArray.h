#pragma once

class CCharArray
{
public:
	CCharArray(unsigned int size);
	virtual ~CCharArray(void);
public:
	char *char_array(void) { return m_pCharArray; }
private:
	char *m_pCharArray;
};

