#ifndef __ANAGLYPHS_h__
#define __ANAGLYPHS_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/filedlg.h>
#include <wx/scrolbar.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>
////Header Include End
#include <vector>
void split(const std::string &txt, std::vector<std::string> &strs, char ch);

////Dialog Style Start
#undef Anaglyphs_STYLE
#define Anaglyphs_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class Anaglyphs : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		Anaglyphs(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Lab05"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = Anaglyphs_STYLE);
		virtual ~Anaglyphs();
		void WxButton1Click(wxCommandEvent& event);
		void WxButtonLoadClick(wxCommandEvent& event);
		void WxButtonSaveClick(wxCommandEvent& event);
		void AnaglyphsPaint(wxPaintEvent& event);
		void Repaint();
		void WxPanelUpdateUI(wxUpdateUIEvent& event);
		void WxSB_RotateXScroll(wxScrollEvent& event);
		void WxSB_RotateYScroll(wxScrollEvent& event);
		void WxSB_RotateZScroll(wxScrollEvent& event);
		void WxSB_TransZScroll(wxScrollEvent& event);
		void WxSB_Calibrate(wxScrollEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxFileDialog *WxOpenFileDialog;
		wxStaticText *Calibration_label;
		wxScrollBar *Calibration;
		wxStaticText *Kalib;
		wxBoxSizer *WxBoxSizer8;
		wxStaticText *WxST_TransZ;
		wxScrollBar *WxSB_TransZ;
		wxStaticText *WxStaticText7;
		wxBoxSizer *WxBoxSizer9;
		wxStaticText *WxST_RotateZ;
		wxScrollBar *WxSB_RotateZ;
		wxStaticText *WxStaticText3;
		wxBoxSizer *WxBoxSizer5;
		wxStaticText *WxST_RotateY;
		wxScrollBar *WxSB_RotateY;
		wxStaticText *WxStaticText2;
		wxBoxSizer *WxBoxSizer4;
		wxStaticText *WxST_RotateX;
		wxScrollBar *WxSB_RotateX;
		wxStaticText *WxStaticText1;
		wxBoxSizer *WxBoxSizer3;
		wxTextCtrl *YResolutioninput;
		wxTextCtrl *XResolutionInput;
		wxBoxSizer *WxBoxSizer7;
		wxStaticText *WxStaticText4;
		wxButton *WxButtonSave;
		wxButton *WxButtonLoad;
		wxBoxSizer *WxBoxSizer6;
		wxBoxSizer *WxBoxSizer2;
		wxPanel *WxPanel;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXST_CALIBRATE = 1042,
			ID_WXSB_CALIBRATE = 1039,
			ID_WXST_TRANSZ = 1042,
			ID_WXSB_TRANSZ = 1040,
			ID_WXSTATICTEXT7 = 1036,
			ID_WXST_ROTATEZ = 1032,
			ID_WXSB_ROTATEZ = 1015,
			ID_WXSTATICTEXT3 = 1013,
			ID_WXST_ROTATEY = 1031,
			ID_WXSB_ROTATEY = 1014,
			ID_WXSTATICTEXT2 = 1012,
			ID_WXST_ROTATEX = 1030,
			ID_WXSB_ROTATEX = 1009,
			ID_WXSTATICTEXT1 = 1008,
			ID_YRESOLUTIONINPUT = 1059,
			ID_XRESOLUTIONINPUT = 1058,
			ID_WXSTATICTEXT4 = 1062,
			ID_WXBUTTONSAVE = 1050,
			ID_WXBUTTONLOAD = 1049,
			ID_WXPANEL = 1002,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
