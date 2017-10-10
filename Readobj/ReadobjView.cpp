// ReadobjView.cpp : implementation of the CReadobjView class
//

#include "stdafx.h"
#include "Readobj.h"

#include "ReadobjDoc.h"
#include "ReadobjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadobjView

IMPLEMENT_DYNCREATE(CReadobjView, CView)

BEGIN_MESSAGE_MAP(CReadobjView, CView)
	//{{AFX_MSG_MAP(CReadobjView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadobjView construction/destruction

CReadobjView::CReadobjView()//����
{
   	 m_xRotation=0.0;//m_xRotation���ӵ���x��ĽǶ�
	 m_yRotation=0.0;//m_yRotation���ӵ���y��ĽǶ�
	 m_xTranslation=0.0;
	 m_yTranslation=0.0;//m_yTranslation���ӵ���y��ĽǶ�,opengl��Ĭ��y�����Ϸ���
	 m_Scaling=2.0;//���Ų���Ϊ0����Ȼ��ʼ��ͼ�񿴲���

}

CReadobjView::~CReadobjView()//����
{
}

BOOL CReadobjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CReadobjView drawing

void CReadobjView::OnDraw(CDC* pDC)
{
	CReadobjDoc* pDoc = GetDocument();
	
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawScene(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CReadobjView printing

BOOL CReadobjView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReadobjView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CReadobjView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CReadobjView diagnostics

#ifdef _DEBUG
void CReadobjView::AssertValid() const
{
	CView::AssertValid();
}

void CReadobjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReadobjDoc* CReadobjView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReadobjDoc)));
	return (CReadobjDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReadobjView message handlers

void CReadobjView::OnDestroy() 
{
	HGLRC   hrc;
	hrc = ::wglGetCurrentContext();
	::wglMakeCurrent(NULL,  NULL);
	if (hrc)
	::wglDeleteContext(hrc);
	if (m_pDC)
	delete m_pDC;
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CReadobjView::bSetupPixelFormat()
{
		/*�� �� �� �� �� �� �� ʽ */  
	PIXELFORMATDESCRIPTOR pfd = { 
	sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
	1,                                // �汾�� 
	PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
	PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
	PFD_TYPE_RGBA,                  // RGBA ��ɫģʽ 
	24,                               // 24 λ��ɫ��� 
	0, 0, 0, 0, 0, 0,                 // ������ɫλ 
	0,                                // û�з�͸���Ȼ��� 
	0,                                // ������λλ 
	0,                                // ���ۼӻ��� 
	0, 0, 0, 0,                       // �����ۼ�λ 
	32,                               // 32 λ��Ȼ���     
	0,                                // ��ģ�建�� 
	0,                                // �޸������� 
	PFD_MAIN_PLANE,                   // ���� 
	0,                                // ���� 
	0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ
	};  
	int pixelformat;
	if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )
	{
	MessageBox("ChoosePixelFormat failed");
	return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
	MessageBox("SetPixelFormat failed");
	return FALSE;
	}
	return TRUE;

}

void CReadobjView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int  n;
	HGLRC hrc;
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	if (!bSetupPixelFormat())
	return;
	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);
}

int CReadobjView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	Init();
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CReadobjView::DrawScene(CReadobjDoc *pDoc)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//��ʾҪ�����ɫ�����Լ���Ȼ���
	glPushMatrix();//��ʾ�����о�������ѹ���ջ�У����������ǵڶ�������ı���,glPushMatrix()��glPopMatrix()�����ʹ�ÿ���������һ�εı任�Ա��α任��Ӱ�졣
	//**************************[//��������]**********************
	/*
	glColor3f(0.25,0.36,0.85);
	glutWireSphere(1.0,20,16);
	*/

	//*******************************����
	//angle��ӹ���ɾ�����ת�ĽǶȣ���x,y,z����������Ӧ�ÿ���һ�������ʾһ����������ʾ����Χ������[x,y,z]��ת��
	
	glRotatef(m_xRotation,1.0f,0.0f,0.0f);//��x����ת
	glRotatef(m_yRotation,0.0f,1.0f,0.0f);//��y����ת

	glTranslatef(m_xTranslation,0.0f,0.0f);
    //glTranslation(m_yTranslation,0.0f,1.0f,0.0f);
	
	glScalef(m_Scaling,m_Scaling,m_Scaling);//����
	//��ȡ��
	
	glColor3f(0,0.9,0);
	glBegin(GL_POINTS);
    for (int i=0;i<pDoc->num;i++)
		glVertex3f(pDoc->mpot[i].x,pDoc->mpot[i].y,pDoc->mpot[i].z);
	glEnd();
	glPopMatrix();	
	glFinish();
	SwapBuffers(wglGetCurrentDC());
	
}


void CReadobjView::OnSize(UINT nType, int cx, int cy) 
{

	
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	int w,h;
	w = cx;
	h = cy;
	if(h == 0)//��ֹ�����
	h = 1;
	float ratio = 1.0* w / h;
	//���ܽ���������ͶӰ����������ز�����
	//###############################
	glMatrixMode(GL_PROJECTION); //���޸�ǰ��������ϵ
	glLoadIdentity();//���õ�ǰ�Ĵ���
	//############################
	// Set the viewport�ӿ� to be the entire window
	glViewport(0, 0, w, h); // ����OpenGL�ӿڴ�С
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);//ѡ��ģ�͹۲����
	glLoadIdentity();//����ģ�͹۲����
	gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0, 0.0f,1.0f,0.0f); //���ù۲��
                           //���ù۲�ĵ�    //�������ϵķ���

	
}
//����������
void CReadobjView::OnLButtonUp(UINT nFlags, CPoint point) 
{
		
	CView::OnLButtonUp(nFlags, point);
}
//����������
void CReadobjView::OnLButtonDown(UINT nFlags, CPoint point) 
{	Posl=point;
	CView::OnLButtonDown(nFlags, point);
}
//����Ҽ�����
void CReadobjView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	
	
	CView::OnRButtonUp(nFlags, point);
}
//����Ҽ�������
void CReadobjView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	
		Posl=point;
	CView::OnRButtonDown(nFlags, point);
}
//��������ʱ�򣬷Ŵ���С
BOOL CReadobjView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{	
	m_Scaling=m_Scaling+0.1*zDelta/120;
	InvalidateRect(NULL,FALSE);//ˢ�»�ͼ��true��ʱ�����ñ���ɫ����ѡ���򸲸�һ��Ȼ����ƣ�Ĭ�ϱ���Ϊ��ɫ��
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
//���������µ�ʱ������ƶ�
void CReadobjView::OnMouseMove(UINT nFlags, CPoint point) 
{
		if(nFlags & MK_LBUTTON)
	{
	
		m_xRotation+=(point.y-Posl.y)/3.6;//��ת    ��������ת��
		m_yRotation+=(point.x-Posl.x)/3.6;          //��������ת��
	
		Posl=point;
	}
	else if((nFlags & MK_RBUTTON))
	{
		m_xTranslation=(float)(point.x - Posl.x)*0.01f;//ƽ��
		m_yTranslation=-(float)(point.y - Posl.y)*0.01f;
	}
	
		Invalidate(false);//������������Ϊfalse��ʱ�򲻲�������ֱ�ӻ�ͼ��

		Posl.x=point.x;
		Posl.y=point.y;
	
	//CView::OnMouseMove(nFlags, point);
}

//��ֹ��Ļ����

BOOL CReadobjView::OnEraseBkgnd()
{
	//return CView::OnEraseBkgnd(pDC);
	return true;
}
