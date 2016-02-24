#pragma once

#include "MedicSet.h"

class CMedic
{
public:
	static void MedicSearchOutDate();
	static void MedicSearchZeroNumber();
	static void MedicSearchAll();
	static void MedicSearch(CMedicSet *pMedicSet, CString str1, int flag);
	static void RefreshReport(CMedicSet *pMedicSet);
	CMedic(void);
	~CMedic(void);
public:
	CString	m_strMedicID;
	CString	m_strMedicName;
	CString	m_strMedicType;
	CTime	m_strProduceDate;
	int	m_strMedicNumber;
	float	m_strMedicPrice;
	int	m_strGuarantPeriod;
	CString	m_ProduceCompany;
};
