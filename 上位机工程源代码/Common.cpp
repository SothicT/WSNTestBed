#include "stdafx.h"
#include <math.h>
#include <afxtempl.h>

//********************************************************************
// 方法名称:ByteToHex
//
// 方法说明:将字节转化为十六进制字符串
//
// 参数说明:
// strHex:十六进制字符串
// bytData:待转换的字节
//
// 返回值:整型
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
// 方法名称:HexToInt
//
// 方法说明:将十六进制字符串转为整型
//
// 参数说明:
// strHex:待转换的十六进制字符串
//
// 返回值:整型
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
// 方法名称:CRC
//
// 方法说明:计算新的CRC值
//
// 参数说明:
// nCRC:原CRC值
// bytData:新加入的一个字节
//
// 返回值:新的CRC值
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
// 方法名称:GetCurrentIntTime
//
// 方法说明:计算当前时间值,并以整型数返回
//
// 参数说明:
// 无
//
// 返回值:以整型数表示的当前时间
//********************************************************************
int GetCurrentIntTime()
{
	CTime dmtTime=CTime::GetCurrentTime();
	return (int)dmtTime.GetTime();
}

//********************************************************************
// 方法名称:IsNumeric
//
// 方法说明:判断一个字符串是否全有数字组成
//
// 参数说明:
// strText:待判断的字符串
//
// 返回值:如果该字符串全为数字则返回为TRUE,否则返回FALSE
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
// 方法名称:WriteByteToByteArray
//
// 方法说明:将字节写入字节流
//
// 参数说明:
// arryBytes:字节流
// bytData:待写入的字节
//
// 返回值:无
//********************************************************************
void WriteByteToByteArray(CArray<BYTE,BYTE>& arryBytes,BYTE bytData)
{
	arryBytes.Add(bytData);
}

//********************************************************************
// 方法名称:WriteIntToByteArray
//
// 方法说明:将整型数写入字节流
//
// 参数说明:
// arryBytes:字节流
// nData:待写入的整型数
//
// 返回值:无
//********************************************************************
void WriteIntToByteArray(CArray<BYTE,BYTE>& arryBytes,int nData)
{
	arryBytes.Add((BYTE)(nData & 0x000000FF));
	arryBytes.Add((BYTE)((nData & 0x0000FF00)>>8));
	arryBytes.Add((BYTE)((nData & 0x00FF0000)>>16));
	arryBytes.Add((BYTE)((nData & 0xFF000000)>>24));
}

//********************************************************************
// 方法名称:WriteIntToByteArrayR
//
// 方法说明:将整型数写入字节流,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// nData:待写入的整型数
//
// 返回值:无
//********************************************************************
void WriteIntToByteArrayR(CArray<BYTE,BYTE>& arryBytes,int nData)
{
	arryBytes.Add((BYTE)((nData & 0xFF000000)>>24));
	arryBytes.Add((BYTE)((nData & 0x00FF0000)>>16));
	arryBytes.Add((BYTE)((nData & 0x0000FF00)>>8));
	arryBytes.Add((BYTE)(nData & 0x000000FF));
}

//********************************************************************
// 方法名称:WriteShortToByteArray
//
// 方法说明:将短整型数写入字节流
//
// 参数说明:
// arryBytes:字节流
// nData:待写入的短整型数
//
// 返回值:无
//********************************************************************
void WriteShortToByteArray(CArray<BYTE,BYTE>& arryBytes,short nData)
{
	arryBytes.Add((BYTE)(nData & 0x00FF));
	arryBytes.Add((BYTE)((nData & 0xFF00)>>8));
}

//********************************************************************
// 方法名称:WriteShortToByteArrayR
//
// 方法说明:将短整型数写入字节流,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// nData:待写入的短整型数
//
// 返回值:无
//********************************************************************
void WriteShortToByteArrayR(CArray<BYTE,BYTE>& arryBytes,short nData)
{
	arryBytes.Add((BYTE)((nData & 0xFF00)>>8));
	arryBytes.Add((BYTE)(nData & 0x00FF));
}

//********************************************************************
// 方法名称:WriteStringToByteArray
//
// 方法说明:将字符串数写入字节流
//
// 参数说明:
// arryBytes:字节流
// strData:待写入的字符串
//
// 返回值:无
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
// 方法名称:WriteIntArrayToByteArray
//
// 方法说明:将整型数组写入字节流
//
// 参数说明:
// arryBytes:字节流
// arryDatas:待写入的整型数组
//
// 返回值:无
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
// 方法名称:WriteIntArrayToByteArrayR
//
// 方法说明:将整型数组写入字节流,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// arryDatas:待写入的整型数组
//
// 返回值:无
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
// 方法名称:WriteShortArrayToByteArray
//
// 方法说明:将短整型数组写入字节流
//
// 参数说明:
// arryBytes:字节流
// arryDatas:待写入的短整型数组
//
// 返回值:无
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
// 方法名称:WriteShortArrayToByteArrayR
//
// 方法说明:将短整型数组写入字节流,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// arryDatas:待写入的短整型数组
//
// 返回值:无
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
// 方法名称:WriteStringArrayToByteArray
//
// 方法说明:将字符串数组写入字节流
//
// 参数说明:
// arryBytes:字节流
// arryDatas:待写入的字符串数组
//
// 返回值:无
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
// 方法名称:WriteStringArrayToByteArrayR
//
// 方法说明:将字符串数组写入字节流,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// arryDatas:待写入的字符串数组
//
// 返回值:无
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
// 方法名称:ReadByteFromByteArray
//
// 方法说明:从字节流中读一个字节
//
// 参数说明:
// arryBytes:字节流
// bytData:字节返回值
//
// 返回值:成功TRUE，失败FALSE
//********************************************************************
BOOL ReadByteFromByteArray(CArray<BYTE,BYTE>& arryBytes,int& nOffset,BYTE& bytData)
{
	if(arryBytes.GetSize()<nOffset+1)
	{
		return FALSE;
	}
// 	if(arryBytes[nOffset]>127)//负数
// 	{
// 		bytData=-((arryBytes[nOffset++]-1)^(0xFF));
// 		
// 	}
// 	else
		bytData=arryBytes[nOffset++];
	
	return TRUE;
}

//********************************************************************
// 方法名称:ReadIntFromByteArray
//
// 方法说明:从字节流中读一个整型数
//
// 参数说明:
// arryBytes:字节流
// nData:整型数返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadIntFromByteArrayR
//
// 方法说明:从字节流中读一个整型数,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// nData:整型数返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadShortFromByteArray
//
// 方法说明:从字节流中读一个短整型数
//
// 参数说明:
// arryBytes:字节流
// nData:短整型数返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadShortFromByteArrayR
//
// 方法说明:从字节流中读一个短整型数,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// nData:短整型数返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadUnsignedShortFromByteArray
//
// 方法说明:从字节流中读一个无符号短整型数
//
// 参数说明:
// arryBytes:字节流
// nData:无符号短整型数返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadUnsignedShortFromByteArrayR
//
// 方法说明:从字节流中读一个无符号短整型数,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// nData:无符号短整型数返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadStringFromByteArray
//
// 方法说明:从字节流中读一个字符串
//
// 参数说明:
// arryBytes:字节流
// nData:字符串返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadIntArrayFromByteArray
//
// 方法说明:从字节流中读一个整型数组
//
// 参数说明:
// arryBytes:字节流
// arryDatas:整型数组返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadIntArrayFromByteArrayR
//
// 方法说明:从字节流中读一个整型数组,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// arryDatas:整型数组返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadShortArrayFromByteArray
//
// 方法说明:从字节流中读一个短整型数组
//
// 参数说明:
// arryBytes:字节流
// arryDatas:短整型数组返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadShortArrayFromByteArrayR
//
// 方法说明:从字节流中读一个短整型数组,其顺序为网络字节顺序
//
// 参数说明:
// arryBytes:字节流
// arryDatas:短整型数组返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadStringArrayFromByteArray
//
// 方法说明:从字节流中读一个字符串数组
//
// 参数说明:
// arryBytes:字节流
// arryDatas:字符串数组返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:ReadStringArrayFromByteArrayR
//
// 方法说明:从字节流中读一个字符串数组
//
// 参数说明:
// arryBytes:字节流
// arryDatas:字符串数组返回值
//
// 返回值:成功TRUE，失败FALSE
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
// 方法名称:TransparentBlt2
//
// 方法说明:绘制透明位图
//
// 参数说明:
// hdcDest:目标DC
// nXOriginDest:目标X偏移
// nYOriginDest:目标Y偏移
// nWidthDest:目标宽度
// nHeightDest:目标高度
// hdcSrc:源DC
// nXOriginSrc:源X起点
// nYOriginSrc:源Y起点
// nWidthSrc:源宽度
// nHeightSrc:源高度
// crTransparent:透明色,COLORREF类型
//
// 返回值:无
//********************************************************************
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
					 UINT crTransparent  // 透明色,COLORREF类型
					 )
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
	
	// 将源DC中的位图拷贝到临时DC中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	
	// 设置透明色
	SetBkColor(hImageDC, crTransparent);
	
	// 生成透明区域为白色，其它区域为黑色的掩码位图
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	
	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	
	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	
	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);
	
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
	
}

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
