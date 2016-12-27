#ifndef __ANAGLYPHSApp_h__
#define __ANAGLYPHSApp_h__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#else
#include <wx/wxprec.h>
#endif

class AnaglyphsApp : public wxApp
{
public:
	bool OnInit();
	int OnExit();
};

#endif
