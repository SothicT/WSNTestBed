// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "iplottablex.h"

// Dispatch interfaces referenced by this interface
#include "Font.h"
#include "iplottablecolumnx.h"


/////////////////////////////////////////////////////////////////////////////
// CiPlotTableX properties

/////////////////////////////////////////////////////////////////////////////
// CiPlotTableX operations

double CiPlotTableX::GetMarginLeft()
{
	double result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetMarginLeft(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CiPlotTableX::GetMarginTop()
{
	double result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetMarginTop(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CiPlotTableX::GetMarginRight()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetMarginRight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CiPlotTableX::GetMarginBottom()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetMarginBottom(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CiPlotTableX::GetGridBackGroundColor()
{
	unsigned long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetGridBackGroundColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CiPlotTableX::GetGridBackGroundTransparent()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetGridBackGroundTransparent(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

unsigned long CiPlotTableX::GetGridLinesColor()
{
	unsigned long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetGridLinesColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CiPlotTableX::GetGridLinesShow()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetGridLinesShow(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

COleFont CiPlotTableX::GetDataFont()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return COleFont(pDispatch);
}

void CiPlotTableX::SetDataFont(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CiPlotTableX::GetDataFontColor()
{
	unsigned long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetDataFontColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CiPlotTableX::GetColumnSpacing()
{
	double result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetColumnSpacing(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CiPlotTableX::GetRowSpacing()
{
	double result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetRowSpacing(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CiPlotTableX::GetRowsMax()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetRowsMax(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CiPlotTableX::GetColumnTitlesVisible()
{
	BOOL result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetColumnTitlesVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

COleFont CiPlotTableX::GetColumnTitlesFont()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return COleFont(pDispatch);
}

void CiPlotTableX::SetColumnTitlesFont(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CiPlotTableX::GetColumnTitlesFontColor()
{
	unsigned long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetColumnTitlesFontColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CiPlotTableX::AddColumn(LPCTSTR Title)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Title);
	return result;
}

void CiPlotTableX::RemoveAllColumns()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotTableX::RemoveAllRows()
{
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CiPlotTableX::DeleteColumn(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void CiPlotTableX::DeleteRow(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

long CiPlotTableX::GetRowCount()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CiPlotTableX::GetColumnCount()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CiPlotTableX::GetData(long Col, long Row)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Col, Row);
	return result;
}

void CiPlotTableX::SetData(long Col, long Row, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Col, Row, lpszNewValue);
}

CiPlotTableColumnX CiPlotTableX::GetColumn(long Index)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, parms,
		Index);
	return CiPlotTableColumnX(pDispatch);
}

long CiPlotTableX::AddRow()
{
	long result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CiPlotTableX::GetEnabled()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotTableX::GetPopupEnabled()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetPopupEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CiPlotTableX::GetVisible()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CiPlotTableX::GetName()
{
	CString result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CiPlotTableX::GetLayer()
{
	long result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetLayer(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CiPlotTableX::GetUserSelected()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetUserSelected(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CiPlotTableX::GetZOrder()
{
	long result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetZOrder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double CiPlotTableX::GetStartPercent()
{
	double result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetStartPercent(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CiPlotTableX::GetStopPercent()
{
	double result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CiPlotTableX::SetStopPercent(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}
