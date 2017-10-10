// ReadobjDoc.cpp : implementation of the CReadobjDoc class
//
//#include <iostream>
//using namespace std;

#include "stdafx.h"
#include<iostream> 
#include "Readobj.h"

 //#include "fstream.h"

#include "ReadobjDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int MaxCount=256;
 char *buf=new char[MaxCount];
//FILE * fp;


/////////////////////////////////////////////////////////////////////////////
// CReadobjDoc

IMPLEMENT_DYNCREATE(CReadobjDoc, CDocument)

BEGIN_MESSAGE_MAP(CReadobjDoc, CDocument)
	//{{AFX_MSG_MAP(CReadobjDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadobjDoc construction/destruction

CReadobjDoc::CReadobjDoc()
{
	// TODO: add one-time construction code here

}

CReadobjDoc::~CReadobjDoc()
{
}

BOOL CReadobjDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CReadobjDoc serialization

void CReadobjDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CReadobjDoc diagnostics

#ifdef _DEBUG
void CReadobjDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReadobjDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReadobjDoc commands

void CReadobjDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	CString OBJfilename;
    CFileDialog dlg(TRUE, _T("OBJ"),_T("*.OBJ"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("objFile(*.OBJ)|*.OBJ|"));
 	if( IDOK==dlg.DoModal() )
 	{
		OBJfilename.Format("%s",dlg.GetPathName());
 	    getNum (LPCTSTR(OBJfilename));
 	    if(num==0&&f_num==0)
		{
 	 	   AfxMessageBox("have no this file of file format error! ");
 	  	   return ;
		}
        Readobjfile(LPCTSTR(OBJfilename));
	}	
 /*	else
		return;*/
//	Invalidate(TRUE);	
}

//读取文件
int CReadobjDoc::Readobjfile(const char  *OBJFileName)
{

//	FILE *fp; 

	int i=0;
	int j=0;
	int k=0;
	fstream file1;
	char *strTp=new char[50];//为50个char类型的数组分配空间，并将地址保存在strTp中
	mpot=new PTNODE[num];
	fpot=new FNODE[f_num];
	npot=new PTNODE[N_num];
	file1.open( OBJFileName, ios::in);//以输入方式打开文件

	if(!file1)
	{
		cout<<"can not read this file:\n<======"<<OBJFileName<<endl;
		return 0;
	}
	while( (i<num || j<f_num||k<N_num )&& !file1.eof() )
	{       
			file1>>strTp;
			if( strcmp( strTp, "v" ) == 0 )//判断点
			{
				file1>>mpot[i].x>>mpot[i].y>>mpot[i].z;
				i++;
			}
	    	else if(strcmp( strTp, "f" ) == 0)
			{
				file1>>fpot[j].vx>>fpot[j].vy>>fpot[j].vz;
				j++;
			}
			else if(strcmp( strTp, "vn" ) == 0)
			{
				file1>>npot[k].x>>npot[k].y>>npot[k].z;
				k++;
 			}
	}
    file1.close();
	delete []strTp;
	return 1;
}

//获得点数
void CReadobjDoc::getNum(const char  *OBJFileName)
{

	fstream file1;
	int i=0;
	int j=0;
	int k=0;
	char *strTp1=new char[50];//定义指针数组
    file1.open( OBJFileName, ios::in);//以输入方式打开文件
	if(!file1)
	{
		cout<<"can not read this file:\n<======"<<OBJFileName<<endl;
	}
	while( !file1.eof() )//检查是否达到文件尾部，若达到尾部返回非0数值，否则是0
	{
		file1>>strTp1;//输入strTp1
		if( strcmp( strTp1, "v" ) == 0 )
		{
			i++;

		}else if ( strcmp( strTp1, "f" ) == 0 )
		{
			j++;
		}else if ( strcmp( strTp1, "vn" ) == 0 )
		{
			k++;
		}
		//fgets(buf,MaxCount,fp);
	//getline(OBJFileName,MaxCount,'\n');  
	}
	f_num=j;
	num=i;
	N_num=k;
	file1.close();//关闭文件
	delete []strTp1;
//	delete fp;
}