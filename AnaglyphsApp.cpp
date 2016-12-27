#define WXUSINGDLL
#include "AnaglyphsApp.h"
#include "Anaglyphs.h"

IMPLEMENT_APP(AnaglyphsApp)

bool AnaglyphsApp::OnInit()
{
	Anaglyphs* dialog = new Anaglyphs(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;
}
 
int AnaglyphsApp::OnExit()
{
	return 0;
}
