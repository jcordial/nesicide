#ifndef CQTMFC_H
#define CQTMFC_H

#include <QApplication>
#include <QAction>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QBitmap>
#include <QFont>
#include <QRegion>
#include <QFrame>
#include <QComboBox>
#include <QClipboard>
#include <QScrollBar>
#include <QEvent>
#include <QList>
#include <QMap>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QObject>
#include <QThread>
#include <QFile>
#include <QMutex>
#include <QByteArray>
#include <QGridLayout>
#include <QMimeData>
#include <QElapsedTimer>
#include <QSharedMemory>
#include <QSettings>
#include <QMutex>
#include <QSemaphore>
#include <QListWidget>
#include <QDialog>
#include <QMenu>
#include <QTableWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFileDialog>

// Releasing pointers
#define SAFE_RELEASE(p) \
        if (p != NULL) { \
                delete p;       \
                p = NULL;       \
        }       \

#define SAFE_RELEASE_ARRAY(p) \
        if (p != NULL) { \
                delete [] p;    \
                p = NULL;       \
        }       \


#if defined(Q_WS_WIN) || defined(Q_WS_WIN32)
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) > (b)) ? (b) : (a))
#endif

// workaround to force ignore ms_abi errors, not needed as long as we don't link with other mfc implementations
#if !defined(Q_WS_WIN) && !defined(Q_WS_WIN32)
#if !__has_attribute(ms_abi)
#define ms_abi
#endif
#endif

#include <windows.h>

#ifdef UNICODE
#define _T(x) L##x
#else
#define _T(x) x
#endif 
#if !defined(TRACE0)
#define TRACE0(x) { QString str; str.sprintf("TRACE0: %s(%d): %s",__FILE__,__LINE__, (x)); qDebug(str.toLatin1().constData()); }
#endif
#if !defined(TRACE)
#define TRACE(x) { QString str; str.sprintf("TRACE0: %s(%d): %s",__FILE__,__LINE__, (x)); qDebug(str.toLatin1().constData()); }
#endif
#if !defined(ATLTRACE2)
#define ATLTRACE2(a,b,str,...)
#endif

#define POSITION int

#define DECLARE_DYNCREATE(x) 
#define DECLARE_MESSAGE_MAP()
#define DECLARE_DYNAMIC(x)
#define IMPLEMENT_DYNAMIC(x,y)

#define RUNTIME_CLASS(x) new x

#define afx_msg

#ifdef QT_NO_DEBUG
#define ASSERT(y)
#define ASSERT_VALID(y)
#else
#define ASSERT(y) { if (!(y)) { QString str; str.sprintf("ASSERT: %s(%d)",__FILE__,__LINE__); qDebug(str.toLatin1().constData()); } }
#define ASSERT_VALID(y) { if (!(y)) { QString str; str.sprintf("ASSERT: %s(%d)",__FILE__,__LINE__); qDebug(str.toLatin1().constData()); } }
#endif

size_t strlen(const wchar_t* str);

int _tstoi(TCHAR* str);

int MulDiv(
  int nNumber,
  int nNumerator,
  int nDenominator
);
DWORD WINAPI GetTickCount(void);
DWORD WINAPI GetSysColor(
  int nIndex
);
int WINAPI GetSystemMetrics(
  int nIndex
);
BOOL WINAPI IsClipboardFormatAvailable(
  UINT format
);
BOOL WINAPI OpenClipboard(
  HWND hWndNewOwner = 0
);
BOOL WINAPI EmptyClipboard(void);
BOOL WINAPI CloseClipboard(void);
HANDLE WINAPI SetClipboardData(
  UINT uFormat,
  HANDLE hMem
);
HANDLE WINAPI GetClipboardData(
  UINT uFormat
);
HGLOBAL WINAPI GlobalAlloc(
  UINT uFlags,
  SIZE_T dwBytes
);
LPVOID WINAPI GlobalLock(
  HGLOBAL hMem
);
BOOL WINAPI GlobalUnlock(
  HGLOBAL hMem
);
SIZE_T WINAPI GlobalSize(
  HGLOBAL hMem
);

class CObject
{
public:
   CObject() {}
   virtual ~CObject() {}
   virtual void DeleteObject() {}
};

class CCriticalSection
{
public:
   BOOL Lock() { return TRUE; }
   BOOL Unlock() { return TRUE; }
};

class CMutex : public QMutex
{
public:
   void Lock() { lock(); }
   void Unlock() { unlock(); }
};

class CSemaphore
{
};

class CString
{
public:
   CString();
   CString(const CString& ref);
   CString(QString str);
   CString(LPCSTR str);
   CString(LPCWSTR str);
   virtual ~CString();

   void UpdateScratch();

   CString& Append(LPCSTR str);
   CString& Append(LPWSTR str);
   void AppendFormat(LPCTSTR fmt, ...);
   void AppendFormatV(LPCTSTR fmt, va_list ap);
   void Format(LPCTSTR fmt, ...);
   void FormatV(LPCTSTR fmt, va_list ap);

   CString& operator=(LPSTR str);
   CString& operator+=(LPSTR str);
   CString& operator=(LPWSTR str);
   CString& operator+=(LPWSTR str);
   CString& operator=(LPCSTR str);
   CString& operator+=(LPCSTR str);
   CString& operator=(LPCWSTR str);
   CString& operator+=(LPCWSTR str);
   CString& operator=(QString str);
   CString& operator+=(QString str);
   CString& operator=(CString str);
   CString& operator+=(CString str);
   bool operator==(const CString& str) const;
   //operator const char*() const;
   operator const QString&() const;
   operator LPCTSTR() const;

   void Empty();
   LPCTSTR GetString() const;
   LPCTSTR GetBuffer() const;
   CString Left( int nCount ) const;
   CString Right( int nCount ) const;
   int GetLength() const;
   int CompareNoCase( LPCTSTR lpsz ) const;
   TCHAR GetAt( int nIndex ) const;
   
protected:
   QString _qstr;
   QByteArray _qstrn;
};

class CStringA : public CString
{
public:
   CStringA(CString str) { qDebug("WHAT TO DO WITH CSTRINGA??"); }
};

class CStringArray
{
public:
   CString GetAt(int idx) { return _qlist.at(idx); }
   void SetAt(int idx, CString str) { _qlist.replace(idx,str); }
private:
   QList<CString> _qlist;
};

class CFileException
{
public:
   virtual BOOL GetErrorMessage(
      LPTSTR lpszError,
      UINT nMaxError,
      PUINT pnHelpContext = NULL
   ) const
   {
      lpszError[0] = 0;
      return false;
   }
};

class CFile
{
public:
   enum
   {
      modeCreate = 0x01,
      modeRead = 0x02,
      modeWrite = 0x04,
      shareDenyWrite = 0x08
   };
   CFile();
   CFile(
      LPCTSTR lpszFileName,
      UINT nOpenFlags 
   );
   virtual ~CFile();

   virtual void Write(
      const void* lpBuf,
      UINT nCount
   );
   virtual UINT Read(
      void* lpBuf,
      UINT nCount
   );
   virtual BOOL Open(
      LPCTSTR lpszFileName,
      UINT nOpenFlags,
      CFileException* pError = NULL
   );
   virtual ULONGLONG GetLength( ) const;
   virtual void Close();

private:
   QFile _qfile;
};

class CPoint : public tagPOINT
{
public:
   CPoint()
   {
      x = 0;
      y = 0;
   }
   CPoint(QPoint point)
   {
      x = point.x();
      y = point.y();
   }
   CPoint(int _x, int _y)
   {
      x = _x;
      y = _y;
   }
   void SetPoint(int _x, int _y)
   {
      x = _x;
      y = _y;
   }
   bool operator==(CPoint p)
   {
      return ((p.x == x) && (p.y == y));
   }
};

class CSize : public tagSIZE
{
public:
   CSize( ) { cx = 0; cy = 0; } 
   CSize( 
      int initCX, 
      int initCY  
   ) { cx = initCX; cy = initCY; }
   CSize( 
      SIZE initSize  
   ) { cx = initSize.cx; cy = initSize.cy; }
   CSize( 
      POINT initPt  
   ) { cx = initPt.x; cy = initPt.y; }
   CSize( 
      DWORD dwSize  
   ) { cx = dwSize&0xFFFF; cy = (dwSize>>16); }
};

class CRect : public tagRECT
{
public:
   CRect( ); 
   CRect( 
      int l, 
      int t, 
      int r, 
      int b  
   );
   CRect( 
      const RECT& srcRect  
   );
   CRect( 
      LPCRECT lpSrcRect  
   );
   CRect( 
      POINT point, 
      SIZE size  
   );
   CRect( 
      POINT topLeft, 
      POINT bottomRight  
   );
   int Width() const { return right-left; }
   int Height() const { return bottom-top; }
   void MoveToXY(
      int x,
      int y 
   );
   void MoveToY(
         int y
   );
   void MoveToXY(
      POINT point 
   );   
   void DeflateRect( 
      int x, 
      int y  
   );
   void DeflateRect( 
      SIZE size  
   );
   void DeflateRect( 
      LPCRECT lpRect  
   );
   void DeflateRect( 
      int l, 
      int t, 
      int r, 
      int b  
   );
   operator LPRECT() const
   {
      return (RECT*)this;
   }
   operator LPCRECT() const
   {
      return (const RECT*)this;
   }
   operator QRect() const
   {
      return QRect(left,top,right-left,bottom-top);
   }
};

class CGdiObject : public CObject
{
public:
   CGdiObject() {}
   virtual ~CGdiObject() {}
   operator HGDIOBJ() const
   {
      return (void*)this;
   }
};

class CPen : public CGdiObject
{
public:
   CPen( );
   CPen(
      int nPenStyle,
      int nWidth,
      COLORREF crColor 
   );
   CPen(
      int nPenStyle,
      int nWidth,
      const LOGBRUSH* pLogBrush,
      int nStyleCount = 0,
      const DWORD* lpStyle = NULL 
   );
   virtual ~CPen() {}
   BOOL CreatePen(
      int nPenStyle,
      int nWidth,
      COLORREF crColor 
   );
   operator QPen() const
   {
      return _qpen;
   }
   operator HPEN() const
   {
      return (HPEN)this;
   }

private:
   QPen _qpen;
};

class CBitmap : public CGdiObject
{
public:
   CBitmap() {}
   virtual ~CBitmap() {}
   BOOL LoadBitmap(
      UINT nIDResource 
   );
   operator QBitmap() const
   {
      return _qbitmap;
   }
   operator HBITMAP() const
   {
      return (HBITMAP)this;
   }
private:
   QBitmap _qbitmap;
};

class CBrush : public CGdiObject
{
public:
   CBrush( );
   CBrush(
      COLORREF crColor 
   );
   CBrush(
      int nIndex,
      COLORREF crColor 
   );
   explicit CBrush(
      CBitmap* pBitmap 
   );
   virtual ~CBrush() {}
   operator QBrush() const
   {
      return _qbrush;
   }
   operator HBRUSH() const
   {
      return (HBRUSH)this;
   }
private:
   QBrush _qbrush;
};

class CFont : public CGdiObject
{
public:
   CFont() {}
   virtual ~CFont() {}
   BOOL CreateFont(
      int nHeight,
      int nWidth,
      int nEscapement,
      int nOrientation,
      int nWeight,
      BYTE bItalic,
      BYTE bUnderline,
      BYTE cStrikeOut,
      BYTE nCharSet,
      BYTE nOutPrecision,
      BYTE nClipPrecision,
      BYTE nQuality,
      BYTE nPitchAndFamily,
      LPCTSTR lpszFacename 
   );
   BOOL CreateFontIndirect(
      const LOGFONT* lpLogFont 
   );
   operator QFont() const
   {
      return _qfont;
   }
   operator HFONT() const
   {
      return (HFONT)this;
   }
private:
   QFont _qfont;
};

class CRgn : public CGdiObject
{
public:
   CRgn() {}
   virtual ~CRgn() {}
   operator QRegion() const
   {
      return _qregion;
   }
   operator HRGN() const
   {
      return (HRGN)this;
   }
private:
   QRegion _qregion;
};

class CDC : public CObject
{
public:
   CDC()
   {
      _qwidget = NULL;
      _qpainter = NULL;
      _pen = NULL;
      _brush = NULL;
      _font = NULL;
      _bitmap = NULL;
      _rgn = NULL;   
      _gdiobject = NULL;
      _object = NULL;
      _lineOrg.x = 0;
      _lineOrg.y = 0;
      _bkColor = QColor(0,0,0);
      _bkMode = 0;
      _textColor = QColor(0,0,0);
      _windowOrg.x = 0;
      _windowOrg.y = 0;
   }
   CDC(QWidget* parent)
   {
      _qwidget = parent;
      _qpainter = NULL;
      _pen = NULL;
      _brush = NULL;
      _font = NULL;
      _bitmap = NULL;
      _rgn = NULL;   
      _gdiobject = NULL;
      _object = NULL;
      _lineOrg.x = 0;
      _lineOrg.y = 0;
      _bkColor = QColor(0,0,0);
      _bkMode = 0;
      _textColor = QColor(0,0,0);
      _windowOrg.x = 0;
      _windowOrg.y = 0;
   }

   void attach()
   {
      _qpainter = new QPainter(_qwidget);
   }
   
   void attach(QWidget* widget)
   {
      _qpainter = new QPainter(widget);
   }
   
   void detach()
   {
      delete _qpainter;
      _qpainter = NULL;
   }
   
   QPainter* painter() { return _qpainter; }
   
   virtual ~CDC();
   BOOL DrawEdge(
      LPRECT lpRect,
      UINT nEdge,
      UINT nFlags 
   );
   BOOL BitBlt(
      int x,
      int y,
      int nWidth,
      int nHeight,
      CDC* pSrcDC,
      int xSrc,
      int ySrc,
      DWORD dwRop 
   );
   COLORREF GetPixel(
      int x,
      int y 
   ) const;
   COLORREF GetPixel(
      POINT point 
   ) const;
   void Draw3dRect( LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight )
   {
      Draw3dRect(lpRect->left,lpRect->top,lpRect->right-lpRect->left,lpRect->bottom-lpRect->top,clrTopLeft,clrBottomRight);
   }
   void Draw3dRect( int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight );
   virtual int DrawText(
      LPCTSTR lpszString,
      int nCount,
      LPRECT lpRect,
      UINT nFormat 
   );
   int DrawText(
      const CString& str,
      LPRECT lpRect,
      UINT nFormat 
   );
   void FillSolidRect(
      LPCRECT lpRect,
      COLORREF clr 
   );
   void FillSolidRect(
      int x,
      int y,
      int cx,
      int cy,
      COLORREF clr 
   );
   int GetDeviceCaps(
      int nIndex 
   ) const
   {
      return 0;
   }
   BOOL GradientFill( 
      TRIVERTEX* pVertices, 
      ULONG nVertices, 
      void* pMesh, 
      ULONG nMeshElements, 
      DWORD dwMode  
   );   
   BOOL LineTo( 
      int x, 
      int y  
   ); 
   BOOL LineTo( 
      POINT point  
   )
   {
      return LineTo(point.x,point.y);
   }

   CPoint MoveTo( 
      int x, 
      int y  
   )
   {
      CPoint old = _lineOrg;
      _lineOrg.x = x;
      _lineOrg.y = y;
      return old;
   }
   CPoint MoveTo( 
      POINT point  
   )
   {
      return MoveTo(point.x,point.y);
   }

   CPoint OffsetWindowOrg( 
      int nWidth, 
      int nHeight  
   )
   {
      CPoint old = _windowOrg;
      _windowOrg.x += nWidth;
      _windowOrg.y += nHeight;
      return old;
   }
   BOOL Polygon(
      LPPOINT lpPoints,
      int nCount 
   );   
   
   HGDIOBJ SelectObject(
      HGDIOBJ obj
   );
   
   CPen* SelectObject(
      CPen* pPen 
   )
   {
      CPen* temp = _pen;
      _pen = pPen;
      if ( _pen )
         _qpainter->setPen((QPen)(*_pen));
      return temp;
   }

   CBrush* SelectObject(
      CBrush* pBrush 
   )
   {
      CBrush* temp = _brush;
      _brush = pBrush;
      if ( _brush )      
         _qpainter->setBrush((QBrush)(*_brush));
      return temp;
   }
   
   virtual CFont* SelectObject(
      CFont* pFont 
   )
   {
      CFont* temp = _font;
      _font = pFont;
      if ( _font )
         _qpainter->setFont((QFont)(*_font));
      return temp;
   }
   CBitmap* SelectObject(
      CBitmap* pBitmap 
   )
   {
      CBitmap* temp = _bitmap;
      _bitmap = pBitmap;
      return temp;
   }   
   int SelectObject(
      CRgn* pRgn 
   );
   CGdiObject* SelectObject(
      CGdiObject* pObject
   )
   {
      CGdiObject* temp = _gdiobject;
      _gdiobject = pObject;
      return temp;
   }   
   CObject* SelectObject(
      CObject* pObject
   )
   {
      CObject* temp = _object;
      _object = pObject;
      return temp;
   }   
   COLORREF SetBkColor( 
      COLORREF crColor  
   )
   {
      COLORREF old = _bkColor.red()|(_bkColor.green()<<8)|_bkColor.blue()<<16;
      _bkColor = QColor(GetRValue(crColor),GetGValue(crColor),GetBValue(crColor));
      return old;
   }
   int SetBkMode( 
      int nBkMode  
   )
   {
      int old = _bkMode;
      _bkMode = nBkMode;
      return old;
   }
   COLORREF SetPixel( int x, int y, COLORREF crColor );
   COLORREF SetPixel( POINT point, COLORREF crColor )
   {
      return SetPixel(point.x,point.y,crColor);
   }

   COLORREF SetTextColor( 
      COLORREF crColor  
   )
   {
      COLORREF old = _textColor.red()|(_textColor.green()<<8)|_textColor.blue()<<16;
      _textColor = QColor(GetRValue(crColor),GetGValue(crColor),GetBValue(crColor));
      return old;
   }
   CPoint SetWindowOrg(
      int x,
      int y 
   )
   {
      CPoint old = _windowOrg;
      _windowOrg.x = x;
      _windowOrg.y = y;
      return old;
   }
   CPoint SetWindowOrg(
      POINT point 
   )
   {
      return SetWindowOrg(point.x,point.y);
   }

   BOOL TextOut(
      int x,
      int y,
      LPCTSTR lpszString,
      int nCount 
   );
   BOOL TextOut(
      int x,
         int y,
         const CString& str 
   );
   
private:
   CDC(CDC& orig);
   QWidget*    _qwidget;
   QPainter*   _qpainter;
   CPen*       _pen;
   CBrush*     _brush;
   CFont*      _font;
   CBitmap*    _bitmap;
   CRgn*       _rgn;   
   CGdiObject* _gdiobject;
   CObject*    _object;
   CPoint      _lineOrg;
   QColor      _bkColor;
   int         _bkMode;
   QColor      _textColor;
   CPoint      _windowOrg;
};

class CPaintDC : public CDC
{
public:
   CPaintDC(QWidget* parent) : CDC(parent) {}
};

class CDataExchange
{
};

class QtUIElement
{
public:
   virtual void SetDlgItemInt(
      int nID,
      UINT nValue,
      BOOL bSigned = TRUE 
   ) {}
   virtual UINT GetDlgItemInt(
      int nID,
      BOOL* lpTrans = NULL,
      BOOL bSigned = TRUE 
   ) const { return 0; }
   virtual void SetDlgItemText(
      int nID,
      LPCTSTR lpszString 
   ) {}
   virtual int GetDlgItemText(
      int nID,
      CString& rString 
   ) const { return 0; }
   virtual void CheckDlgButton( 
      int nIDButton, 
      UINT nCheck  
   ) {}
};

class CFrameWnd;
class CScrollBar;

class CWnd : public QObject, public QtUIElement
{
   Q_OBJECT
   // MFC interfaces
public:
   CWnd(CWnd* parent=0);
   virtual ~CWnd();

   BOOL IsWindowVisible( ) const;
   virtual BOOL CreateEx(
      DWORD dwExStyle,
      LPCTSTR lpszClassName,
      LPCTSTR lpszWindowName,
      DWORD dwStyle,
      const RECT& rect,
      CWnd* pParentWnd,
      UINT nID,
      LPVOID lpParam = NULL
   );
   virtual BOOL PreTranslateMessage(
      MSG* pMsg 
   ) { return FALSE; }
   virtual CScrollBar* GetScrollBarCtrl(
      int nBar 
   ) const;
   BOOL SetScrollInfo(
      int nBar,
      LPSCROLLINFO lpScrollInfo,
      BOOL bRedraw = TRUE 
   );
   void SetScrollRange(
      int nBar,
      int nMinPos,
      int nMaxPos,
      BOOL bRedraw = TRUE 
   );
   int SetScrollPos(
      int nBar,
      int nPos,
      BOOL bRedraw = TRUE 
   );
   virtual afx_msg int OnCreate(
      LPCREATESTRUCT lpCreateStruct 
   );
   void OnMouseMove(UINT,CPoint) {}
   void OnNcMouseMove(UINT nHitTest, CPoint point) {}
   void OnNcLButtonUp(
      UINT nHitTest,
      CPoint point 
   ) {}   
   void OnLButtonDblClk(UINT,CPoint) {}
   void OnLButtonDown(UINT,CPoint) {}
   void OnLButtonUp(UINT,CPoint) {}
   void OnRButtonDown(UINT,CPoint) {}
   void OnRButtonUp(UINT,CPoint) {}
   BOOL OnMouseWheel(UINT,UINT,CPoint) { return TRUE; }
   void OnSize(UINT nType, int cx, int cy) {}
   UINT SetTimer(UINT id, UINT interval, void*);
   void KillTimer(UINT id);
   void OnTimer(UINT timerId) {}
   void OnKeyDown(UINT,UINT,UINT) {}
   void OnSetFocus(CWnd*) {}
   void OnKillFocus(CWnd*) {}
   void OnVScroll(UINT,UINT,CScrollBar*) {}
   void OnHScroll(UINT,UINT,CScrollBar*) {}
   void OnUpdate(CWnd* p=0,UINT hint=0,CObject* o=0) { _qt->update(); }
   void Invalidate(BOOL bErase = TRUE) { /*update();*/ }
   void RedrawWindow(LPCRECT rect=0,CRgn* rgn=0,UINT f=0) { _qt->update(); }
   CWnd* SetFocus() { CWnd* pWnd = focusWnd; _qt->setFocus(); return pWnd; }
   CWnd* GetFocus() { return focusWnd; } 
   void SetCapture(CWnd* p=0) { /* DON'T DO THIS grabMouse(); */ }
   void ReleaseCapture() { /* DON'T DO THIS releaseMouse(); */ }
   CFrameWnd* GetParentFrame( ) const { return m_pFrameWnd; }
   void MoveWindow(
      LPCRECT lpRect,
         BOOL bRepaint = TRUE 
   ) { _qt->setGeometry(lpRect->left,lpRect->top,lpRect->right-lpRect->left,lpRect->bottom-lpRect->top); }
   void MoveWindow(int x,int y,int cx, int cy) { _qt->setGeometry(x,y,cx,cy); }
   CDC* GetDC() { CDC* pDC = new CDC(); pDC->attach(toQWidget()); return pDC; }
   void ReleaseDC(CDC* pDC) { pDC->detach(); delete pDC; }
   void ShowWindow(int code);
   void UpdateWindow( ) { _qt->update(); }
   virtual BOOL PostMessage(
      UINT message,
      WPARAM wParam = 0,
      LPARAM lParam = 0 
   );
   virtual void DoDataExchange(
      CDataExchange* pDX 
   ) {}   
   CWnd* GetParent() { return m_pParentWnd?(CWnd*)m_pParentWnd:(CWnd*)m_pFrameWnd; }
   void SetParent(CWnd* parent) { m_pParentWnd = parent; }
   void GetWindowRect(
      LPRECT lpRect 
   ) const;
   void GetClientRect(
      LPRECT lpRect 
   ) const;
   CWnd* GetDlgItem(
      int nID 
   ) const;
   void SetDlgItemInt(
      int nID,
      UINT nValue,
      BOOL bSigned = TRUE 
   );
   UINT GetDlgItemInt(
      int nID,
      BOOL* lpTrans = NULL,
      BOOL bSigned = TRUE 
   ) const;
   void SetDlgItemText(
      int nID,
      LPCTSTR lpszString 
   );
   int GetDlgItemText(
      int nID,
      CString& rString 
   ) const;
   void CheckDlgButton( 
      int nIDButton, 
      UINT nCheck  
   );
   virtual BOOL DestroyWindow( ) { _qt->close(); return TRUE; }
   virtual void PostNcDestroy( ) {}  
   
   // This method only for Qt glue
   UINT_PTR mfcTimerId(int qtTimerId) { return qtToMfcTimer.value(qtTimerId); }
   // These methods are only to be used in CDocTemplate initialization...
   void privateSetParentFrame(CFrameWnd* pFrameWnd) { m_pFrameWnd = pFrameWnd; }
   
   // MFC-to-Qt conversions
protected:
   QMap<UINT_PTR,int> mfcToQtTimer;
   QMap<int,UINT_PTR> qtToMfcTimer;
   QMap<int,CWnd*> mfcToQtWidget;
   static CFrameWnd* m_pFrameWnd;
   CWnd* m_pParentWnd;
   static CWnd* focusWnd;
   CScrollBar* mfcVerticalScrollBar;
   CScrollBar* mfcHorizontalScrollBar;

   // Qt interfaces
public:
   void setParent(QWidget *parent) { _qt->setParent(parent); }
   void setParent(QWidget *parent, Qt::WindowFlags f) { _qt->setParent(parent,f); }   
   void setGeometry(const QRect & rect) { _qt->setGeometry(rect); }
   void setGeometry(int x, int y, int w, int h) { _qt->setGeometry(x,y,w,h); }
   void setContentsMargins(int left, int top, int right, int bottom) { _qt->setContentsMargins(left,top,right,bottom); }
   void setContentsMargins(const QMargins &margins) { _qt->setContentsMargins(margins); }
   void setFocusPolicy(Qt::FocusPolicy policy) { _qt->setFocusPolicy(policy); }
   void setFixedSize(int w, int h) { _qt->setFixedSize(w,h); }
   virtual void setVisible(bool visible) { _qt->setVisible(visible); }
   QRect rect() const { return _qt->rect(); }
   virtual QWidget* toQWidget() { qDebug("CWnd::operator QWidget()"); return _qt; }
public slots:
   void update() { _qt->update(); }
   void setFocus() { _qt->setFocus(); }
   void setFocus(Qt::FocusReason reason) { _qt->setFocus(reason); }
protected:
   QWidget* _qt;
};

class CView;
class CDocument;
class CFrameWnd : public CWnd
{
   // Qt interfaces
   
   // MFC interfaces
public:
   CFrameWnd(CWnd* parent = 0);
   virtual ~CFrameWnd();
   virtual void SetMessageText(LPCTSTR fmt,...) { qDebug("SetMessageText"); }
   CView* GetActiveView( ) const { return m_pView; } // Only one view for SDI
   virtual CDocument* GetActiveDocument( ) { return m_pDocument; }   
   
   // These methods are only to be used in CDocTemplate initialization...
   virtual void privateSetActiveView(CView* pView) { m_pView = pView; }
   virtual void privateSetActiveDocument(CDocument* pDocument) { m_pDocument = pDocument; }
   
protected:
   CView* m_pView;
   CDocument* m_pDocument;
};

class CDocTemplate;
class CDocument
{
public:
   CDocument() : m_pDocTemplate(NULL) {}
   virtual BOOL OnNewDocument() { DeleteContents(); return TRUE; }
   virtual BOOL OnSaveDocument(LPCTSTR lpszPathName) { return TRUE; }
   virtual BOOL OnOpenDocument(LPCTSTR lpszPathName) { return TRUE; }
   virtual void OnCloseDocument() {}
   virtual void DeleteContents() {}
   virtual void SetModifiedFlag(BOOL bModified = 1) {}
   virtual void OnFileSave() {}
   virtual POSITION GetFirstViewPosition() const { return (POSITION)-1; }
   virtual CView* GetNextView(POSITION pos) const { return m_pViews.at((int)pos); }
   CDocTemplate* GetDocTemplate() const { return m_pDocTemplate; }

   // These methods are only to be used in CDocTemplate initialization...
   virtual void privateSetDocTemplate(CDocTemplate* pDocTemplate) { m_pDocTemplate = pDocTemplate; }
   virtual void privateAddView(CView* pView) { m_pViews.append(pView); }
   
protected:
   CDocTemplate* m_pDocTemplate;
   QList<CView*> m_pViews;
};

class CView : public CWnd
{
public:
   CView(CWnd* parent);
   virtual ~CView();
   virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {}
   virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {}  
   virtual void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {}
   virtual void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {}  
   CDocument* GetDocument() const { return m_pDocument; }
   
   // These methods are only to be used in CDocTemplate initialization...
   void privateSetDocument(CDocument* pDocument) { m_pDocument = pDocument; }

protected:
   CDocument* m_pDocument;
};

class CMenu : public QMenu
{
public:
   BOOL CreatePopupMenu() { return TRUE; }
   BOOL AppendMenu(
      UINT nFlags,
      UINT_PTR nIDNewItem = 0,
      LPCTSTR lpszNewItem = NULL 
   );
   UINT CheckMenuItem(
      UINT nIDCheckItem,
      UINT nCheck 
   );
   UINT EnableMenuItem(
      UINT nIDEnableItem,
      UINT nEnable 
   );
   BOOL TrackPopupMenu(
      UINT nFlags,
      int x,
      int y,
      CWnd* pWnd,
      LPCRECT lpRect = 0
   );
   BOOL DestroyMenu( );
private:
   QMap<UINT_PTR,QAction*> mfcToQtMenu;
};

class CDialog : public CWnd
{
   // Qt interfaces
public:
   operator QDialog*() { return dynamic_cast<QDialog*>(_qt); }
   
   // MFC interfaces
public:
   CDialog(int dlgID,CWnd* parent);
   virtual ~CDialog();
   virtual BOOL Create(
      UINT nIDTemplate,
      CWnd* pParentWnd = NULL 
         ) { _qt->setParent(pParentWnd->toQWidget()); SetParent(pParentWnd); return TRUE; }
   virtual BOOL OnInitDialog() { return TRUE; }
   int DoModal() { _qt->show(); qDebug("CDialog::DoModal doesn't return right thing yet but it's just for testing anyway..."); return 0; }
   void MapDialogRect( 
      LPRECT lpRect  
   ) const;
};

class CFileDialog : public CWnd
{
   // Qt interfaces
public:
   void setDefaultSuffix(const QString & suffix) { dynamic_cast<QFileDialog*>(_qt)->setDefaultSuffix(suffix); }
   void selectFile(const QString & filename) { dynamic_cast<QFileDialog*>(_qt)->selectFile(filename); }
   void setFilter(const QString& filter) { dynamic_cast<QFileDialog*>(_qt)->setFilter(filter); }
   QStringList selectedFiles() const { return dynamic_cast<QFileDialog*>(_qt)->selectedFiles(); }
   operator QFileDialog*() { return dynamic_cast<QFileDialog*>(_qt); }
   
   // MFC interfaces
public:
   explicit CFileDialog(
      BOOL bOpenFileDialog,
      LPCTSTR lpszDefExt = NULL,
      LPCTSTR lpszFileName = NULL,
      DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
      LPCTSTR lpszFilter = NULL,
      CWnd* pParentWnd = NULL,
      DWORD dwSize = 0
   );
   virtual ~CFileDialog();
   virtual void OnFileNameChange( ) {};
   CString GetFileExt( ) const;
   CString GetPathName( ) const;
};

class CScrollBar : public CWnd
{
   Q_OBJECT
   // Qt interfaces
public:
   int sliderPosition() const { return dynamic_cast<QScrollBar*>(_qt)->sliderPosition(); }
   void setMinimum(int minimum) { dynamic_cast<QScrollBar*>(_qt)->setMinimum(minimum); }
   void setMaximum(int maximum) { dynamic_cast<QScrollBar*>(_qt)->setMaximum(maximum); }
   void setValue(int value) { dynamic_cast<QScrollBar*>(_qt)->setValue(value); }
   void setPageStep(int pageStep) { dynamic_cast<QScrollBar*>(_qt)->setPageStep(pageStep); }
   operator QScrollBar*() { return dynamic_cast<QScrollBar*>(_qt); }
signals:
   
   // MFC interfaces
public:
   CScrollBar(CWnd* parent = 0);
   CScrollBar(Qt::Orientation o,CWnd* parent = 0);
   virtual ~CScrollBar();
   BOOL SetScrollInfo(
      LPSCROLLINFO lpScrollInfo,
      BOOL bRedraw = TRUE 
   );
   virtual BOOL Create(
      DWORD dwStyle,
      const RECT& rect,
      CWnd* pParentWnd,
      UINT nID 
   );
   int SetScrollPos(
      int nPos,
      BOOL bRedraw = TRUE 
   );
   void SetScrollRange(
      int nMinPos,
      int nMaxPos,
      BOOL bRedraw = TRUE 
   );
   void ShowScrollBar(
      BOOL bShow = TRUE 
   );
   BOOL EnableScrollBar(
      UINT nArrowFlags = ESB_ENABLE_BOTH 
   );
};

class CEdit : public CWnd
{
   Q_OBJECT
   // Qt interfaces
public:
   operator QLineEdit*() { return dynamic_cast<QLineEdit*>(_qt); }
signals:
   void textChanged(QString);
   
   // MFC interfaces
public:
   CEdit(CWnd* parent = 0);
   virtual ~CEdit();
   void SetDlgItemInt(
      int nID,
      UINT nValue,
      BOOL bSigned = TRUE 
   );
   UINT GetDlgItemInt(
      int nID,
      BOOL* lpTrans = NULL,
      BOOL bSigned = TRUE 
   ) const;
   void SetDlgItemText(
      int nID,
      LPCTSTR lpszString 
   );
   int GetDlgItemText(
      int nID,
      CString& rString 
   ) const;
};

class CButton : public CWnd
{
   Q_OBJECT
   // Qt interfaces
public:
   operator QPushButton*() { return dynamic_cast<QPushButton*>(_qt); }
   void setText(const QString & text) { dynamic_cast<QPushButton*>(_qt)->setText(text); }
   void setDefault(bool def) { dynamic_cast<QPushButton*>(_qt)->setDefault(def); }
   void setCheckable(bool checkable) { dynamic_cast<QPushButton*>(_qt)->setCheckable(checkable); }
signals:
   void clicked();

   // MFC interfaces
public:
   CButton(CWnd* parent = 0);
   virtual ~CButton();
   void SetDlgItemInt(
      int nID,
      UINT nValue,
      BOOL bSigned = TRUE 
   );
   UINT GetDlgItemInt(
      int nID,
      BOOL* lpTrans = NULL,
      BOOL bSigned = TRUE 
   ) const;
   void SetDlgItemText(
      int nID,
      LPCTSTR lpszString 
   );
   int GetDlgItemText(
      int nID,
      CString& rString 
   ) const;
   void CheckDlgButton( 
      int nIDButton, 
      UINT nCheck  
   );
};

class CSpinButtonCtrl : public CWnd
{
   Q_OBJECT
   // Qt interfaces
public:
   operator QSpinBox*() { return dynamic_cast<QSpinBox*>(_qt); }   
signals:
   void valueChanged(int);
   
   // MFC interfaces
public:
   CSpinButtonCtrl(CWnd* parent = 0);
   virtual ~CSpinButtonCtrl();
   void SetRange(
      short nLower,
      short nUpper 
   );   
};

class CComboBox : public CWnd
{
   Q_OBJECT
   // Qt interfaces
public:
   operator QComboBox*() { return dynamic_cast<QComboBox*>(_qt); }   
signals:
   
   // MFC interfaces
public:
   CComboBox(CWnd* parent = 0);
   virtual ~CComboBox();
   void ResetContent();
   int AddString(
      LPCTSTR lpszString 
   );
   void SetCurSel(int sel);
};

class CStatic : public CWnd
{
   // Qt interfaces
public:
   operator QLabel*() { return dynamic_cast<QLabel*>(_qt); }   
   void setText(const QString & text) { dynamic_cast<QLabel*>(_qt)->setText(text); }

   // MFC interfaces
public:
   CStatic(CWnd* parent = 0);
   virtual ~CStatic();
};

class CGroupBox : public CWnd
{
   // Qt interfaces
public:
   operator QGroupBox*() { return dynamic_cast<QGroupBox*>(_qt); }   
   void setTitle(const QString & title) { dynamic_cast<QGroupBox*>(_qt)->setTitle(title); }

   // MFC interfaces
public:
   CGroupBox(CWnd* parent = 0);
   virtual ~CGroupBox();
};

class QTabWidget_exposed : public QTabWidget
{
public:
   QTabWidget_exposed(QWidget* parent = 0) : QTabWidget(parent) {}
   QTabBar* tabBar() const { return QTabWidget::tabBar(); }
};

class CTabCtrl : public CWnd
{  
   Q_OBJECT
   // Qt interfaces
public:
   operator QTabWidget_exposed*() { return dynamic_cast<QTabWidget_exposed*>(_qt); }      
signals:
   void currentChanged(int);
   
   // MFC interfaces
public:
   CTabCtrl(CWnd* parent = 0);
   virtual ~CTabCtrl();
   LONG InsertItem(
     int nItem,
     LPCTSTR lpszItem 
   );
   BOOL DeleteAllItems( );
   int SetCurSel(
     int nItem 
   );
   int GetCurSel( ) const;
};

#define LVCFMT_LEFT 100

#define LVIS_SELECTED 1
#define LVIS_FOCUSED  2

// CP: No idea...need to find these in the windows headers.
#define LVIF_STATE 100 
#define LVNI_SELECTED 200

typedef struct tagNMLISTVIEW {
  NMHDR  hdr;
  int    iItem;
  int    iSubItem;
  UINT   uNewState;
  UINT   uOldState;
  UINT   uChanged;
  POINT  ptAction;
  LPARAM lParam;
} NMLISTVIEW, *LPNMLISTVIEW;

class CListCtrl : public CWnd
{
   Q_OBJECT
   // Qt interfaces
public:
   operator QTableWidget*() { return dynamic_cast<QTableWidget*>(_qt); }   
   void setSelectionMode(QAbstractItemView::SelectionMode mode) { dynamic_cast<QTableWidget*>(_qt)->setSelectionMode(mode); }
   void setSelectionBehavior(QAbstractItemView::SelectionBehavior behavior) { dynamic_cast<QTableWidget*>(_qt)->setSelectionBehavior(behavior); }
   QScrollBar* verticalScrollBar() const { return dynamic_cast<QTableWidget*>(_qt)->verticalScrollBar(); }
   QScrollBar* horizontalScrollBar() const { return dynamic_cast<QTableWidget*>(_qt)->horizontalScrollBar(); }
   QModelIndex currentIndex () const { return dynamic_cast<QTableWidget*>(_qt)->currentIndex(); }
signals:
   void itemSelectionChanged();
   
   // MFC interfaces
public:
   CListCtrl(CWnd* parent = 0);
   virtual ~CListCtrl();
   BOOL DeleteAllItems( );
   int InsertColumn(
      int nCol,
      LPCTSTR lpszColumnHeading,
      int nFormat = LVCFMT_LEFT,
      int nWidth = -1,
      int nSubItem = -1 
   );
   int GetSelectionMark( );
   int GetItemText(
      int nItem,
      int nSubItem,
      LPTSTR lpszText,
      int nLen 
   ) const;
   int InsertItem(
      int nItem,
      LPCTSTR lpszItem,
      int nImage 
   );
   int InsertItem(
      int nItem,
      LPCTSTR lpszItem 
   );
   int SetSelectionMark(
      int iIndex 
   );
   BOOL SetCheck(
      int nItem,
      BOOL fCheck = TRUE 
   );
   BOOL SetItemText(
      int nItem,
      int nSubItem,
      LPCTSTR lpszText 
   );
   BOOL SetItemText(
      int nItem,
      int nSubItem,
      char* lpszText 
   );
   BOOL SetItemState(
      int nItem,
      UINT nState,
      UINT nMask 
   );
};

class CWinThread : public QThread
{
   Q_OBJECT
public:
   CWinThread();
   virtual ~CWinThread();
   BOOL CreateThread(
      DWORD dwCreateFlags = 0,
      UINT nStackSize = 0,
      LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL 
   );
   BOOL PostThreadMessage(
      UINT message ,
      WPARAM wParam,
      LPARAM lParam 
         );
   virtual BOOL InitInstance() { return FALSE; }
   virtual BOOL ExitInstance() { return FALSE; }
signals:
   void postThreadMessage(unsigned int m,unsigned int w,unsigned int l);
public slots:
   void recvThreadMessage(unsigned int m,unsigned int w,unsigned int l) { qDebug("CWinThread::recvThreadMessage"); }
};

class CDocTemplate
{
public:
   CDocTemplate(UINT f,CDocument* pDoc,CFrameWnd* pFrameWnd,CView* pView);
   virtual CDocument* OpenDocumentFile(
      LPCTSTR lpszPathName,
      BOOL bMakeVisible = TRUE 
   ) = 0;
   CDocument* m_pDoc;
   CView*     m_pView;
   CFrameWnd* m_pFrameWnd;
};

class CSingleDocTemplate : public CDocTemplate
{
public:
   CSingleDocTemplate(UINT f,CDocument* pDoc,CFrameWnd* pFrameWnd,CView* pView);
   virtual CDocument* OpenDocumentFile(
      LPCTSTR lpszPathName,
      BOOL bMakeVisible = TRUE 
   );
};

class CWinApp : public CWinThread
{
public:
   CWinApp() : m_pMainWnd(NULL), m_pDocTemplate(NULL) {}
   void AddDocTemplate(CDocTemplate* pDocTemplate) { m_pDocTemplate = pDocTemplate; }
   CDocTemplate* GetDocTemplate() const { return m_pDocTemplate; }
   virtual BOOL InitInstance();
   CFrameWnd* m_pMainWnd;
   
protected:
   CDocTemplate* m_pDocTemplate;
};

int StretchDIBits(
  CDC& dc,
  int XDest,
  int YDest,
  int nDestWidth,
  int nDestHeight,
  int XSrc,
  int YSrc,
  int nSrcWidth,
  int nSrcHeight,
  const VOID *lpBits,
  const BITMAPINFO *lpBitsInfo,
  UINT iUsage,
  DWORD dwRop
);

#endif // CQTMFC_H
