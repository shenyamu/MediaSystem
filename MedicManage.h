#pragma once
#include "Globol.h"

class CMedicManage
{
public:
	void SetMedicSet(CMedicSet* theMedicSet);
	void SetMedic(CMedic* theMedic);
	CTime GetOutDateTime();
	BOOL Storage(BOOL bFlag);
	BOOL DelMedicZeroNumber();
	BOOL DelMedicOutDate();
	CMedicManage(void);
	~CMedicManage(void);
private:
	CMedic* m_theMedic;
	CMedicSet* m_theMedicSet;
};
