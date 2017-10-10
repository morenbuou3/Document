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

CReadobjView::CReadobjView()//构造
{
   	 m_xRotation=0.0;//m_xRotation是视点绕x轴的角度
	 m_yRotation=0.0;//m_yRotation是视点绕y轴的角度
	 m_xTranslation=0.0;
	 m_yTranslation=0.0;//m_yTranslation是视点绕y轴的角度,opengl里默认y轴是上方向
	 m_Scaling=2.0;//缩放不能为0，不然开始的图像看不见

}

CReadobjView::~CReadobjView()//析构
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
		/*定 义 像 素 存 储 格 式 */  
	PIXELFORMATDESCRIPTOR pfd = { 
	sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	1,                                // 版本号 
	PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
	PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
	PFD_TYPE_RGBA,                  // RGBA 颜色模式 
	24,                               // 24 位颜色深度 
	0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
	0,                                // 没有非透明度缓存 
	0,                                // 忽略移位位 
	0,                                // 无累加缓存 
	0, 0, 0, 0,                       // 忽略累加位 
	32,                               // 32 位深度缓存     
	0,                                // 无模板缓存 
	0,                                // 无辅助缓存 
	PFD_MAIN_PLANE,                   // 主层 
	0,                                // 保留 
	0, 0, 0                           // 忽略层,可见性和损毁掩模
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//表示要清除颜色缓冲以及深度缓冲
	glPushMatrix();//表示将所有矩阵依次压入堆栈中，顶部矩阵是第二个矩阵的备份,glPushMatrix()和glPopMatrix()的配对使用可以消除上一次的变换对本次变换的影响。
	//**************************[//绘制球体]**********************
	/*
	glColor3f(0.25,0.36,0.85);
	glutWireSphere(1.0,20,16);
	*/

	//*******************************画点
	//angle毋庸置疑就是旋转的角度，而x,y,z三个参数则应该看成一个整体表示一个向量，表示物体围绕向量[x,y,z]旋转。
	
	glRotatef(m_xRotation,1.0f,0.0f,0.0f);//绕x轴旋转
	glRotatef(m_yRotation,0.0f,1.0f,0.0f);//绕y轴旋转

	glTranslatef(m_xTranslation,0.0f,0.0f);
    //glTranslation(m_yTranslation,0.0f,1.0f,0.0f);
	
	glScalef(m_Scaling,m_Scaling,m_Scaling);//缩放
	//读取点
	
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
	if(h == 0)//防止被雾除
	h = 1;
	float ratio = 1.0* w / h;
	//不管进行哪两种投影，下面两句必不可少
	//###############################
	glMatrixMode(GL_PROJECTION); //在修改前重设坐标系
	glLoadIdentity();//重置当前的窗口
	//############################
	// Set the viewport视口 to be the entire window
	glViewport(0, 0, w, h); // 设置OpenGL视口大小
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);//选择模型观察矩阵
	glLoadIdentity();//重置模型观察矩阵
	gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0, 0.0f,1.0f,0.0f); //设置观察点
                           //设置观察的点    //设置向上的方向

	
}
//鼠标左键弹起
void CReadobjView::OnLButtonUp(UINT nFlags, CPoint point) 
{
		
	CView::OnLButtonUp(nFlags, point);
}
//鼠标左键按下
void CReadobjView::OnLButtonDown(UINT nFlags, CPoint point) 
{	Posl=point;
	CView::OnLButtonDown(nFlags, point);
}
//鼠标右键弹起
void CReadobjView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	
	
	CView::OnRButtonUp(nFlags, point);
}
//鼠标右键弹按下
void CReadobjView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	
		Posl=point;
	CView::OnRButtonDown(nFlags, point);
}
//鼠标滚动的时候，放大缩小
BOOL CReadobjView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{	
	m_Scaling=m_Scaling+0.1*zDelta/120;
	InvalidateRect(NULL,FALSE);//刷新绘图【true的时候是用背景色将所选区域覆盖一次然后绘制，默认背景为白色】
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
//鼠标左键按下的时候进行移动
void CReadobjView::OnMouseMove(UINT nFlags, CPoint point) 
{
		if(nFlags & MK_LBUTTON)
	{
	
		m_xRotation+=(point.y-Posl.y)/3.6;//旋转    （左右旋转）
		m_yRotation+=(point.x-Posl.x)/3.6;          //（上下旋转）
	
		Posl=point;
	}
	else if((nFlags & MK_RBUTTON))
	{
		m_xTranslation=(float)(point.x - Posl.x)*0.01f;//平移
		m_yTranslation=-(float)(point.y - Posl.y)*0.01f;
	}
	
		Invalidate(false);//擦除背景【当为false的时候不擦除背景直接画图】

		Posl.x=point.x;
		Posl.y=point.y;
	
	//CView::OnMouseMove(nFlags, point);
}

//防止屏幕闪动

BOOL CReadobjView::OnEraseBkgnd()
{
	//return CView::OnEraseBkgnd(pDC);
	return true;
}
