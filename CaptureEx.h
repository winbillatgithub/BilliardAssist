// CaptureEx.h: interface for the CaptureEx class.
//////////////////////////////////////////////////////////////////////
// Author: Golan Shahar 1.1.2006
//////////////////////////////////////////////////////////////////////

#ifndef CAPTUREEX_H
#define CAPTUREEX_H

class CaptureEx  
{
public:
	CaptureEx();
	virtual ~CaptureEx();
	void	SaveBmpToFile(LPTSTR szFileName,int W,int H,int Bps,int* lpBits);
	void	Get24BitBmp ( const int &nWidth, const int &nHeight,const HBITMAP &hBitmap , BYTE *lpDesBits);
	void	CaptureDesktop (double fPreviewRatio,LPTSTR lpszFileName,BOOL bSaveToFile,int nSize);
	void	StretchDIBitsToHwnd( HWND hWnd,double fRatio,int Width,int Height,int Bps,BYTE *lpBits);
	BOOL	CaptureWindow( HWND hWndSrc,double fPreviewRatio ,LPTSTR lpszFileName,BOOL bSaveToFile);
	void	DisplayLastImage(HWND hWnd, double fRatio);
	void	SaveLastCaptured(LPTSTR szFileName);
private:
	BOOL	Capture( HWND hwnd,HDC memDC);
	void	UpdateLastImage( int Width, int Height, int Size,int Bps, BYTE* lpBits);

	BYTE	*m_pLastImage;
	int		m_Width;
	int		m_Height;
	int		m_Bpp;
};
#endif

