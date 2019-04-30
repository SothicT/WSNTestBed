#include "stdafx.h"
#include <math.h>
#include <afxtempl.h>

//********************************************************************
// ��������:ByteToHex
//
// ����˵��:���ֽ�ת��Ϊʮ�������ַ���
//
// ����˵��:
// strHex:ʮ�������ַ���
// bytData:��ת�����ֽ�
//
// ����ֵ:����
//********************************************************************

void ByteToHex(CString& strHex,BYTE bytData)
{
	strHex="";
	strHex.Format("%X",bytData);
	if(strHex.GetLength()%2!=0)
	{
		strHex="0"+strHex;
	}
}

//********************************************************************
// ��������:HexToInt
//
// ����˵��:��ʮ�������ַ���תΪ����
//
// ����˵��:
// strHex:��ת����ʮ�������ַ���
//
// ����ֵ:����
//********************************************************************

int HexToInt(CString strHex)
{
    int nResult=0;
	int nNum=0;
    char Base[]="0123456789abcdef";

	strHex.MakeLower();

    for(int i=0;i<strHex.GetLength();i++)  
    {
		nNum=strchr(Base,strHex[i])-Base;
		if(nNum>=0 && nNum<=15)
		{
			nResult=(nResult<<4)+nNum;
		}
    }

    return nResult;
}

//********************************************************************
// ��������:CRC
//
// ����˵��:�����µ�CRCֵ
//
// ����˵��:
// nCRC:ԭCRCֵ
// bytData:�¼����һ���ֽ�
//
// ����ֵ:�µ�CRCֵ
//********************************************************************
unsigned short CRC(unsigned short nCRC, BYTE bytData)
{
	nCRC = (BYTE)(nCRC >> 8) | (nCRC << 8);
	nCRC ^= bytData;
	nCRC ^= (BYTE)(nCRC & 0xFF) >> 4;
	nCRC ^= nCRC << 12;
	nCRC ^= (nCRC & 0xFF) << 5;
	return nCRC;
}

//********************************************************************
// ��������:GetCurrentIntTime
//
// ����˵��:���㵱ǰʱ��ֵ,��������������
//
// ����˵��:
// ��
//
// ����ֵ:����������ʾ�ĵ�ǰʱ��
//********************************************************************
int GetCurrentIntTime()
{
	CTime dmtTime=CTime::GetCurrentTime();
	return (int)dmtTime.GetTime();
}

//********************************************************************
// ��������:IsNumeric
//
// ����˵��:�ж�һ���ַ����Ƿ�ȫ���������
//
// ����˵��:
// strText:���жϵ��ַ���
//
// ����ֵ:������ַ���ȫΪ�����򷵻�ΪTRUE,���򷵻�FALSE
//********************************************************************
BOOL IsNumeric(CString strText)
{
	BOOL bIsDigit=TRUE;
	int nCount=strText.GetLength();

	for(int i=0;i<nCount;i++)
	{
		if(0==isdigit(strText.GetAt(i)))
		{
			bIsDigit=FALSE;
			break;
		}
	}

	if(bIsDigit)
	{
		return TRUE;
	}
	return FALSE;
} 

//********************************************************************
// ��������:WriteByteToByteArray
//
// ����˵��:���ֽ�д���ֽ���
//
// ����˵��:
// arryBytes:�ֽ���
// bytData:��д����ֽ�
//
// ����ֵ:��
//********************************************************************
void WriteByteToByteArray(CArray<BYTE,BYTE>& arryBytes,BYTE bytData)
{
	arryBytes.Add(bytData);
}

//********************************************************************
// ��������:WriteIntToByteArray
//
// ����˵��:��������д���ֽ���
//
// ����˵��:
// arryBytes:�ֽ���
// nData:��д���������
//
// ����ֵ:��
//********************************************************************
void WriteIntToByteArray(CArray<BYTE,BYTE>& arryBytes,int nData)
{
	arryBytes.Add((BYTE)(nData & 0x000000FF));
	arryBytes.Add((BYTE)((nData & 0x0000FF00)>>8));
	arryBytes.Add((BYTE)((nData & 0x00FF0000)>>16));
	arryBytes.Add((BYTE)((nData & 0xFF000000)>>24));
}

//********************************************************************
// ��������:WriteIntToByteArrayR
//
// ����˵��:��������д���ֽ���,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// nData:��д���������
//
// ����ֵ:��
//********************************************************************
void WriteIntToByteArrayR(CArray<BYTE,BYTE>& arryBytes,int nData)
{
	arryBytes.Add((BYTE)((nData & 0xFF000000)>>24));
	arryBytes.Add((BYTE)((nData & 0x00FF0000)>>16));
	arryBytes.Add((BYTE)((nData & 0x0000FF00)>>8));
	arryBytes.Add((BYTE)(nData & 0x000000FF));
}

//********************************************************************
// ��������:WriteShortToByteArray
//
// ����˵��:����������д���ֽ���
//
// ����˵��:
// arryBytes:�ֽ���
// nData:��д��Ķ�������
//
// ����ֵ:��
//********************************************************************
void WriteShortToByteArray(CArray<BYTE,BYTE>& arryBytes,short nData)
{
	arryBytes.Add((BYTE)(nData & 0x00FF));
	arryBytes.Add((BYTE)((nData & 0xFF00)>>8));
}

//********************************************************************
// ��������:WriteShortToByteArrayR
//
// ����˵��:����������д���ֽ���,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// nData:��д��Ķ�������
//
// ����ֵ:��
//********************************************************************
void WriteShortToByteArrayR(CArray<BYTE,BYTE>& arryBytes,short nData)
{
	arryBytes.Add((BYTE)((nData & 0xFF00)>>8));
	arryBytes.Add((BYTE)(nData & 0x00FF));
}

//********************************************************************
// ��������:WriteStringToByteArray
//
// ����˵��:���ַ�����д���ֽ���
//
// ����˵��:
// arryBytes:�ֽ���
// strData:��д����ַ���
//
// ����ֵ:��
//********************************************************************
void WriteStringToByteArray(CArray<BYTE,BYTE>& arryBytes,CString strData)
{
	int n;
	
	BYTE bytDataLen=(BYTE)strData.GetLength();
	arryBytes.Add(bytDataLen);
	for(n=0;n<bytDataLen;n++)
	{
		arryBytes.Add((BYTE)strData[n]);
	}
}

//********************************************************************
// ��������:WriteIntArrayToByteArray
//
// ����˵��:����������д���ֽ���
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:��д�����������
//
// ����ֵ:��
//********************************************************************
void WriteIntArrayToByteArray(CArray<BYTE,BYTE>& arryBytes,CArray<int,int>& arryDatas)
{
	int n;
	
	int nDatasSize=arryDatas.GetSize();
	WriteIntToByteArray(arryBytes,nDatasSize);
	for(n=0;n<nDatasSize;n++)
	{
		WriteIntToByteArray(arryBytes,arryDatas[n]);
	}
}

//********************************************************************
// ��������:WriteIntArrayToByteArrayR
//
// ����˵��:����������д���ֽ���,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:��д�����������
//
// ����ֵ:��
//********************************************************************
void WriteIntArrayToByteArrayR(CArray<BYTE,BYTE>& arryBytes,CArray<int,int>& arryDatas)
{
	int n;
	
	int nDatasSize=arryDatas.GetSize();
	WriteIntToByteArrayR(arryBytes,nDatasSize);
	for(n=0;n<nDatasSize;n++)
	{
		WriteIntToByteArrayR(arryBytes,arryDatas[n]);
	}
}

//********************************************************************
// ��������:WriteShortArrayToByteArray
//
// ����˵��:������������д���ֽ���
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:��д��Ķ���������
//
// ����ֵ:��
//********************************************************************
void WriteShortArrayToByteArray(CArray<BYTE,BYTE>& arryBytes,CArray<short,short>& arryDatas)
{
	int n;
	
	int nDatasSize=arryDatas.GetSize();
	WriteIntToByteArray(arryBytes,nDatasSize);
	for(n=0;n<nDatasSize;n++)
	{
		WriteShortToByteArray(arryBytes,arryDatas[n]);
	}
}

//********************************************************************
// ��������:WriteShortArrayToByteArrayR
//
// ����˵��:������������д���ֽ���,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:��д��Ķ���������
//
// ����ֵ:��
//********************************************************************
void WriteShortArrayToByteArrayR(CArray<BYTE,BYTE>& arryBytes,CArray<short,short>& arryDatas)
{
	int n;
	
	int nDatasSize=arryDatas.GetSize();
	WriteIntToByteArrayR(arryBytes,nDatasSize);
	for(n=0;n<nDatasSize;n++)
	{
		WriteShortToByteArrayR(arryBytes,arryDatas[n]);
	}
}

//********************************************************************
// ��������:WriteStringArrayToByteArray
//
// ����˵��:���ַ�������д���ֽ���
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:��д����ַ�������
//
// ����ֵ:��
//********************************************************************
void WriteStringArrayToByteArray(CArray<BYTE,BYTE>& arryBytes,CArray<CString,CString>& arryDatas)
{
	int n;
	
	int nDatasSize=arryDatas.GetSize();
	WriteIntToByteArray(arryBytes,nDatasSize);
	for(n=0;n<nDatasSize;n++)
	{
		WriteStringToByteArray(arryBytes,arryDatas[n]);
	}
}

//********************************************************************
// ��������:WriteStringArrayToByteArrayR
//
// ����˵��:���ַ�������д���ֽ���,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:��д����ַ�������
//
// ����ֵ:��
//********************************************************************
void WriteStringArrayToByteArrayR(CArray<BYTE,BYTE>& arryBytes,CArray<CString,CString>& arryDatas)
{
	int n;
	
	int nDatasSize=arryDatas.GetSize();
	WriteIntToByteArrayR(arryBytes,nDatasSize);
	for(n=0;n<nDatasSize;n++)
	{
		WriteStringToByteArray(arryBytes,arryDatas[n]);
	}
}

//********************************************************************
// ��������:ReadByteFromByteArray
//
// ����˵��:���ֽ����ж�һ���ֽ�
//
// ����˵��:
// arryBytes:�ֽ���
// bytData:�ֽڷ���ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadByteFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,BYTE& bytData)
{
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
// 	if(arryBytes[nOffset]>127)//����
// 	{
// 		bytData=-((arryBytes[nOffset++]-1)^(0xFF));
// 		
// 	}
// 	else
		bytData=arryBytes[nOffset++];
	
	return TRUE;
}

//********************************************************************
// ��������:ReadIntFromByteArray
//
// ����˵��:���ֽ����ж�һ��������
//
// ����˵��:
// arryBytes:�ֽ���
// nData:����������ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadIntFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,int& nData)
{
	if(arryBytes.GetSize()<nOffset+4)
	{
		return FALSE;
	}
	
	nData=(arryBytes[nOffset+3]<<24)|(arryBytes[nOffset+2]<<16)|(arryBytes[nOffset+1]<<8)|arryBytes[nOffset];
	
	nOffset=nOffset+4;
	
	return TRUE;
}

//********************************************************************
// ��������:ReadIntFromByteArrayR
//
// ����˵��:���ֽ����ж�һ��������,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// nData:����������ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadIntFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,int& nData)
{
	if(arryBytes.GetSize()<nOffset+4)
	{
		return FALSE;
	}
	
	nData=(arryBytes[nOffset]<<24)|(arryBytes[nOffset+1]<<16)|(arryBytes[nOffset+2]<<8)|arryBytes[nOffset+3];
	
	nOffset=nOffset+4;
	
	return TRUE;
}

//********************************************************************
// ��������:ReadShortFromByteArray
//
// ����˵��:���ֽ����ж�һ����������
//
// ����˵��:
// arryBytes:�ֽ���
// nData:������������ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadShortFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,short& nData)
{
	if(arryBytes.GetSize()<nOffset+2)
	{
		return FALSE;
	}
	
	nData=(arryBytes[nOffset+1]<<8)|arryBytes[nOffset];
	
	nOffset=nOffset+2;
	
	return TRUE;
}

//********************************************************************
// ��������:ReadShortFromByteArrayR
//
// ����˵��:���ֽ����ж�һ����������,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// nData:������������ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadShortFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,short& nData)
{
	if(arryBytes.GetSize()<nOffset+2)
	{
		return FALSE;
	}
	
	nData=(arryBytes[nOffset]<<8)|arryBytes[nOffset+1];
	
	nOffset=nOffset+2;
	
	return TRUE;
}

//********************************************************************
// ��������:ReadUnsignedShortFromByteArray
//
// ����˵��:���ֽ����ж�һ���޷��Ŷ�������
//
// ����˵��:
// arryBytes:�ֽ���
// nData:�޷��Ŷ�����������ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadUnsignedShortFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,unsigned short& nData)
{
	if(arryBytes.GetSize()<nOffset+2)
	{
		return FALSE;
	}
	
	nData=(arryBytes[nOffset+1]<<8)|arryBytes[nOffset];
	
	nOffset=nOffset+2;
	
	return TRUE;
}

//********************************************************************
// ��������:ReadUnsignedShortFromByteArrayR
//
// ����˵��:���ֽ����ж�һ���޷��Ŷ�������,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// nData:�޷��Ŷ�����������ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadUnsignedShortFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,unsigned short& nData)
{
	if(arryBytes.GetSize()<nOffset+2)
	{
		return FALSE;
	}
	
	nData=(arryBytes[nOffset]<<8)|arryBytes[nOffset+1];
	
	nOffset=nOffset+2;
	
	return TRUE;
}

//********************************************************************
// ��������:ReadStringFromByteArray
//
// ����˵��:���ֽ����ж�һ���ַ���
//
// ����˵��:
// arryBytes:�ֽ���
// nData:�ַ�������ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadStringFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CString& strData)
{
	int n;
	
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
	
	BYTE bytDataLen=(BYTE)arryBytes[nOffset++];
	
	if(bytDataLen<0 || arryBytes.GetSize()<nOffset+bytDataLen)
	{
		return FALSE;
	}
	
	char *lpszData=new char[bytDataLen+1];
	if(lpszData==NULL)
	{
		return FALSE;
	}
	
	for(n=0;n<bytDataLen;n++)
	{
		lpszData[n]=(char)arryBytes[nOffset++];
	}
	lpszData[bytDataLen]='\0';
	
	strData=lpszData;
	
	delete lpszData;
	
	return TRUE;
}

//********************************************************************
// ��������:ReadIntArrayFromByteArray
//
// ����˵��:���ֽ����ж�һ����������
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:�������鷵��ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadIntArrayFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<int,int>& arryDatas)
{
	int n;
	
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
	
	int nDatasSize;
	if(!ReadIntFromByteArray(arryBytes,nOffset,nDatasSize))
	{
		return FALSE;
	}
	
	for(n=0;n<nDatasSize;n++)
	{
		int nData;
		if(!ReadIntFromByteArray(arryBytes,nOffset,nData))
		{
			return FALSE;
		}
		arryDatas.Add(nData);
	}

	return TRUE;
}

//********************************************************************
// ��������:ReadIntArrayFromByteArrayR
//
// ����˵��:���ֽ����ж�һ����������,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:�������鷵��ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadIntArrayFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<int,int>& arryDatas)
{
	int n;
	
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
	
	int nDatasSize;
	if(!ReadIntFromByteArrayR(arryBytes,nOffset,nDatasSize))
	{
		return FALSE;
	}
	
	for(n=0;n<nDatasSize;n++)
	{
		int nData;
		if(!ReadIntFromByteArrayR(arryBytes,nOffset,nData))
		{
			return FALSE;
		}
		arryDatas.Add(nData);
	}

	return TRUE;
}


//********************************************************************
// ��������:ReadShortArrayFromByteArray
//
// ����˵��:���ֽ����ж�һ������������
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:���������鷵��ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadShortArrayFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<short,short>& arryDatas)
{
	int n;
	
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
	
	int nDatasSize;
	if(!ReadIntFromByteArray(arryBytes,nOffset,nDatasSize))
	{
		return FALSE;
	}
	
	for(n=0;n<nDatasSize;n++)
	{
		short nData;
		if(!ReadShortFromByteArray(arryBytes,nOffset,nData))
		{
			return FALSE;
		}
		arryDatas.Add(nData);
	}

	return TRUE;
}

//********************************************************************
// ��������:ReadShortArrayFromByteArrayR
//
// ����˵��:���ֽ����ж�һ������������,��˳��Ϊ�����ֽ�˳��
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:���������鷵��ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadShortArrayFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<short,short>& arryDatas)
{
	int n;
	
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
	
	int nDatasSize;
	if(!ReadIntFromByteArrayR(arryBytes,nOffset,nDatasSize))
	{
		return FALSE;
	}
	
	for(n=0;n<nDatasSize;n++)
	{
		short nData;
		if(!ReadShortFromByteArrayR(arryBytes,nOffset,nData))
		{
			return FALSE;
		}
		arryDatas.Add(nData);
	}

	return TRUE;
}


//********************************************************************
// ��������:ReadStringArrayFromByteArray
//
// ����˵��:���ֽ����ж�һ���ַ�������
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:�ַ������鷵��ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadStringArrayFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<CString,CString>& arryDatas)
{
	int n;
	
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
	
	int nDatasSize;
	if(!ReadIntFromByteArray(arryBytes,nOffset,nDatasSize))
	{
		return FALSE;
	}
	
	for(n=0;n<nDatasSize;n++)
	{
		CString strData;
		if(!ReadStringFromByteArray(arryBytes,nOffset,strData))
		{
			return FALSE;
		}
		arryDatas.Add(strData);
	}
	
	return TRUE;
}

//********************************************************************
// ��������:ReadStringArrayFromByteArrayR
//
// ����˵��:���ֽ����ж�һ���ַ�������
//
// ����˵��:
// arryBytes:�ֽ���
// arryDatas:�ַ������鷵��ֵ
//
// ����ֵ:�ɹ�TRUE��ʧ��FALSE
//********************************************************************
BOOL ReadStringArrayFromByteArrayR(CArray<BYTE,BYTE>& arryBytes,int& nOffset,CArray<CString,CString>& arryDatas)
{
	int n;
	
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
	
	int nDatasSize;
	if(!ReadIntFromByteArrayR(arryBytes,nOffset,nDatasSize))
	{
		return FALSE;
	}
	
	for(n=0;n<nDatasSize;n++)
	{
		CString strData;
		if(!ReadStringFromByteArray(arryBytes,nOffset,strData))
		{
			return FALSE;
		}
		arryDatas.Add(strData);
	}
	
	return TRUE;
}

//********************************************************************
// ��������:TransparentBlt2
//
// ����˵��:����͸��λͼ
//
// ����˵��:
// hdcDest:Ŀ��DC
// nXOriginDest:Ŀ��Xƫ��
// nYOriginDest:Ŀ��Yƫ��
// nWidthDest:Ŀ����
// nHeightDest:Ŀ��߶�
// hdcSrc:ԴDC
// nXOriginSrc:ԴX���
// nYOriginSrc:ԴY���
// nWidthSrc:Դ���
// nHeightSrc:Դ�߶�
// crTransparent:͸��ɫ,COLORREF����
//
// ����ֵ:��
//********************************************************************
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
					 UINT crTransparent  // ͸��ɫ,COLORREF����
					 )
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// ��������λͼ
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// ������ɫ����λͼ
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
	
	// ��ԴDC�е�λͼ��������ʱDC��
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	
	// ����͸��ɫ
	SetBkColor(hImageDC, crTransparent);
	
	// ����͸������Ϊ��ɫ����������Ϊ��ɫ������λͼ
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	
	// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	
	// ͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	
	// "��"����,��������Ч��
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);
	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
	
}

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
			 )
{
	CPen* pOldPen;
	CPen pen(nPenStyle,nPenWidth,color);
	pOldPen = pDC->SelectObject(&pen);
	
	CBrush br,*pbrOld;
	br.CreateSolidBrush(color);
	pbrOld = pDC->SelectObject(&br);
	
	POINT pFrom;
	POINT pBase;
	POINT aptPoly[3];
	float vecLine[2];
	float vecLeft[2];
	float fLength;
	float th;
	float ta;
	
	// get from point
	MoveToEx(pDC->GetSafeHdc(),0,0,&pFrom);
	
	// set to point
	aptPoly[0].x=nX;
	aptPoly[0].y=nY;
	
	// build the line vector
	vecLine[0]=(float)aptPoly[0].x-pFrom.x;
	vecLine[1]=(float)aptPoly[0].y-pFrom.y;
	
	// build the arrow base vector - normal to the line
	vecLeft[0]=-vecLine[1];
	vecLeft[1]=vecLine[0];
	
	// setup length parameters
	fLength=(float)sqrt(vecLine[0]*vecLine[0]+vecLine[1]*vecLine[1]);
	th=nWidth/(2.0f*fLength);
	ta=nWidth/(2.0f*(tanf(fTheta)/2.0f)*fLength);
	
	// find the base of the arrow
	pBase.x=(int)(aptPoly[0].x+-ta*vecLine[0]);
	pBase.y=(int)(aptPoly[0].y+-ta*vecLine[1]);
	
	// build the points on the sides of the arrow
	aptPoly[1].x=(int)(pBase.x+th*vecLeft[0]);
	aptPoly[1].y=(int)(pBase.y+th*vecLeft[1]);
	aptPoly[2].x=(int)(pBase.x+-th*vecLeft[0]);
	aptPoly[2].y=(int)(pBase.y+-th*vecLeft[1]);
	
	MoveToEx(pDC->GetSafeHdc(),pFrom.x,pFrom.y,NULL);
	
	if(bFill) 
	{
		pDC->LineTo(aptPoly[0].x,aptPoly[0].y);
		pDC->Polygon(aptPoly,3);
	}
	else
	{
		pDC->LineTo(pBase.x,pBase.y);
		pDC->LineTo(aptPoly[1].x,aptPoly[1].y);
		pDC->LineTo(aptPoly[0].x,aptPoly[0].y);
		pDC->LineTo(aptPoly[2].x,aptPoly[2].y);
		pDC->LineTo(pBase.x,pBase.y);
		MoveToEx(pDC->GetSafeHdc(),aptPoly[0].x,aptPoly[0].y,NULL);
	}
	
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pbrOld);
}
