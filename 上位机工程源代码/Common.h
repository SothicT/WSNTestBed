void ByteToHex(CString& strHex,BYTE bytData);
int HexToInt(CString strHex);
unsigned short CRC(unsigned short nCRC,BYTE bytData);
int GetCurrentIntTime();

void WriteByteToByteArray(CArray<BYTE,BYTE>& arryBytes,BYTE bytData);
void WriteIntToByteArray(CArray<BYTE,BYTE>& arryBytes,int nData);
void WriteIntToByteArrayR(CArray<BYTE,BYTE>& arryBytes,int nData);
void WriteShortToByteArray(CArray<BYTE,BYTE>& arryBytes,short nData);
void WriteShortToByteArrayR(CArray<BYTE,BYTE>& arryBytes,short nData);
void WriteStringToByteArray(CArray<BYTE,BYTE>& arryBytes,CString strData);
void WriteIntArrayToByteArray(CArray<BYTE,BYTE>& arryBytes,CArray<int,int>& arryDatas);
void WriteIntArrayToByteArrayR(CArray<BYTE,BYTE>& arryBytes,CArray<int,int>& arryDatas);
void WriteShortArrayToByteArray(CArray<BYTE,BYTE>& arryBytes,CArray<short,short>& arryDatas);
void WriteShortArrayToByteArrayR(CArray<BYTE,BYTE>& arryBytes,CArray<short,short>& arryDatas);
void WriteStringArrayToByteArray(CArray<BYTE,BYTE>& arryBytes,CArray<CString,CString>& arryDatas);
void WriteStringArrayToByteArrayR(CArray<BYTE,BYTE>& arryBytes,CArray<CString,CString>& arryDatas);
BOOL ReadByteFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,BYTE& bytData);
BOOL ReadIntFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,int& nData);
BOOL ReadIntFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,int& nData);
BOOL ReadShortFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,short& nData);
BOOL ReadShortFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,short& nData);
BOOL ReadUnsignedShortFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,unsigned short& nData);
BOOL ReadUnsignedShortFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,unsigned short& nData);
BOOL ReadStringFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CString& strData);
BOOL ReadIntArrayFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<int,int>& arryDatas);
BOOL ReadIntArrayFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<int,int>& arryDatas);
BOOL ReadShortArrayFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<short,short>& arryDatas);
BOOL ReadShortArrayFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<short,short>& arryDatas);
BOOL ReadStringArrayFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<CString,CString>& arryDatas);
BOOL ReadStringArrayFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<CString,CString>& arryDatas);

void TransparentBlt2( HDC hdcDest,      // 目标DC
					 int nXOriginDest,   // 目标X偏移
					 int nYOriginDest,   // 目标Y偏移
					 int nWidthDest,     // 目标宽度
					 int nHeightDest,    // 目标高度
					 HDC hdcSrc,         // 源DC
					 int nXOriginSrc,    // 源X起点
					 int nYOriginSrc,    // 源Y起点
					 int nWidthSrc,      // 源宽度
					 int nHeightSrc,     // 源高度
					 UINT crTransparent=RGB(255,255,255)  // 透明色,COLORREF类型
					 );
void ArrowTo(
			 CDC *pDC,               //画刷
			 int nX,				//终点坐标X
			 int nY,				//终点坐标Y
			 int nPenStyle,          //线样式
			 int nPenWidth,          //线宽度
			 COLORREF color, //颜色
			 int nWidth,             //三角形底边宽度
			 float fTheta,           //三角形顶角角度
			 bool bFill              //是否填充颜色
			 );