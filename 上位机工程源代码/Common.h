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

void TransparentBlt2( HDC hdcDest,      // Ŀ��DC
					 int nXOriginDest,   // Ŀ��Xƫ��
					 int nYOriginDest,   // Ŀ��Yƫ��
					 int nWidthDest,     // Ŀ����
					 int nHeightDest,    // Ŀ��߶�
					 HDC hdcSrc,         // ԴDC
					 int nXOriginSrc,    // ԴX���
					 int nYOriginSrc,    // ԴY���
					 int nWidthSrc,      // Դ���
					 int nHeightSrc,     // Դ�߶�
					 UINT crTransparent=RGB(255,255,255)  // ͸��ɫ,COLORREF����
					 );
void ArrowTo(
			 CDC *pDC,               //��ˢ
			 int nX,				//�յ�����X
			 int nY,				//�յ�����Y
			 int nPenStyle,          //����ʽ
			 int nPenWidth,          //�߿��
			 COLORREF color, //��ɫ
			 int nWidth,             //�����εױ߿��
			 float fTheta,           //�����ζ��ǽǶ�
			 bool bFill              //�Ƿ������ɫ
			 );