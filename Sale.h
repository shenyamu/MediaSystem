#pragma once

class CSale
{
public:
	CSale(void);
	~CSale(void);
public:
	CString	m_MedicID;
	CString	m_MedicName;
	float	m_MedicPrice;
	int	m_MedicNumber;
	float	m_TotalMoney;
};
