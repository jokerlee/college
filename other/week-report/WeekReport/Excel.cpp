#include "StdAfx.h"
#include "Excel.h"

CExcel::CExcel(void)
{
}

CExcel::~CExcel(void)
{
}


void CExcel::Create()
{
	try
	{
		m_pXL.CreateInstance(L"Excel.Application");

		m_pXL->Visible[0] = VARIANT_TRUE;

		WorkbooksPtr pBooks = m_pXL->Workbooks;
		m_pBook  = pBooks->Add((long)xlWorksheet);

		_WorksheetPtr pSheet = m_pXL->ActiveSheet;

		pSheet->Name = "Market Share!";

		// When using parameterized properties, optional args must be explicitly dealt with.
		pSheet->Range["A2"][vtMissing]->Value2 = "Company A";
		pSheet->Range["B2"][vtMissing]->Value2 = "Company B";
		pSheet->Range["C2"][vtMissing]->Value2 = "Company C";
		pSheet->Range["D2"][vtMissing]->Value2 = "Company D";

		// Of course, you can call a parameterized property as a method and then optional args are implicit.
		pSheet->GetRange("A3")->Value2 = 75.0;
		pSheet->GetRange("B3")->Value2 = 14.0;
		pSheet->GetRange("C3")->Value2 = 7.0;
		pSheet->GetRange("D3")->Value2 = 4.0;

		// Sleep(1000);

		RangePtr pRange = pSheet->Range["A2:D3"][vtMissing];
		_ChartPtr pChart = m_pBook->Charts->Add();

		pChart->ChartWizard((Range*) pRange, (long) xl3DPie, 7L, (long) xlRows,
			1L, 0L, 2L, "Market Share");

		// Sleep(6000);

		// m_pBook->Saved[0] = VARIANT_TRUE;
		m_pBook->Saved[0] = VARIANT_FALSE;
		m_pBook->SaveAs( _T("test") );
		// m_pXL->Quit();
	}
	catch( _com_error & e )
	{
		DumpComError( e );
	}
}

void CExcel::DumpComError( _com_error & e )
{
	_tprintf(_T("Oops - hit an error!\n"));
	_tprintf(_T("\a\tCode = %08lx\n"), e.Error());
	_tprintf(_T("\a\tCode meaning = %s\n"), e.ErrorMessage());
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	_tprintf(_T("\a\tSource = %s\n"), (LPCTSTR) bstrSource);
	_tprintf(_T("\a\tDescription = %s\n"), (LPCTSTR) bstrDescription);
}