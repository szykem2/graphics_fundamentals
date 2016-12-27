#define __WXMSW__
#define WXUSINGDLL
#include "Anaglyphs.h"
#include "vecmat.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wx/dcbuffer.h>

std::vector <double> x_start, x_end, y_start, y_end, z_start, z_end;
std::vector <int> R, G, B, edge_width;
double d = -2.0;

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Anaglyphs
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Anaglyphs, wxDialog)
////Manual Code Start
////Manual Code End

EVT_CLOSE(Anaglyphs::OnClose)
EVT_BUTTON(ID_WXBUTTONLOAD, Anaglyphs::WxButtonLoadClick)

EVT_COMMAND_SCROLL(ID_WXSB_TRANSZ, Anaglyphs::WxSB_TransZScroll)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEZ, Anaglyphs::WxSB_RotateZScroll)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEY, Anaglyphs::WxSB_RotateYScroll)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEX, Anaglyphs::WxSB_RotateXScroll)

EVT_UPDATE_UI(ID_WXPANEL, Anaglyphs::WxPanelUpdateUI)
END_EVENT_TABLE()
////Event Table End

Anaglyphs::Anaglyphs(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
	: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Anaglyphs::~Anaglyphs()
{
}

void Anaglyphs::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxPanel = new wxPanel(this, ID_WXPANEL, wxPoint(290, 5), wxSize(213, 47));
	WxBoxSizer1->Add(WxPanel, 1, wxEXPAND | wxALL, 5);

	WxBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer6 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer6, 0, wxALIGN_CENTER | wxALL, 5);

	WxButtonLoad = new wxButton(this, ID_WXBUTTONLOAD, _("Wczytaj Geometriê"), wxPoint(5, 5), wxSize(124, 25), 0, wxDefaultValidator, _("WxButtonLoad"));
	WxBoxSizer6->Add(WxButtonLoad, 0, wxALIGN_CENTER | wxALL, 5);

	WxButtonSave = new wxButton(this, ID_WXBUTTONSAVE, _("Zapisz obraz"), wxPoint(6, 40), wxSize(122, 25), 0, wxDefaultValidator, _("WxButtonSave"));
	WxBoxSizer6->Add(WxButtonSave, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer3 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer3, 0, wxALIGN_CENTER | wxALL, 5);

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("Obrót X:"), wxPoint(51, 5), wxDefaultSize, 0, _("WxStaticText1"));
	WxBoxSizer3->Add(WxStaticText1, 0, wxALIGN_CENTER | wxALL, 5);

	WxSB_RotateX = new wxScrollBar(this, ID_WXSB_ROTATEX, wxPoint(5, 34), wxSize(140, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxSB_RotateX"));
	WxSB_RotateX->Enable(false);
	WxBoxSizer3->Add(WxSB_RotateX, 0, wxALIGN_CENTER | wxALL, 5);

	WxST_RotateX = new wxStaticText(this, ID_WXST_ROTATEX, _("0  "), wxPoint(67, 62), wxDefaultSize, 0, _("WxST_RotateX"));
	WxBoxSizer3->Add(WxST_RotateX, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer4 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer4, 0, wxALIGN_CENTER | wxALL, 5);

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("Obrót Y:"), wxPoint(51, 5), wxDefaultSize, 0, _("WxStaticText2"));
	WxBoxSizer4->Add(WxStaticText2, 0, wxALIGN_CENTER | wxALL, 5);

	WxSB_RotateY = new wxScrollBar(this, ID_WXSB_ROTATEY, wxPoint(5, 34), wxSize(140, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxSB_RotateY"));
	WxSB_RotateY->Enable(false);
	WxBoxSizer4->Add(WxSB_RotateY, 0, wxALIGN_CENTER | wxALL, 5);

	WxST_RotateY = new wxStaticText(this, ID_WXST_ROTATEY, _("0  "), wxPoint(67, 62), wxDefaultSize, 0, _("WxST_RotateY"));
	WxBoxSizer4->Add(WxST_RotateY, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer5 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer5, 0, wxALIGN_CENTER | wxALL, 5);

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("Obrót Z:"), wxPoint(51, 5), wxDefaultSize, 0, _("WxStaticText3"));
	WxBoxSizer5->Add(WxStaticText3, 0, wxALIGN_CENTER | wxALL, 5);

	WxSB_RotateZ = new wxScrollBar(this, ID_WXSB_ROTATEZ, wxPoint(5, 34), wxSize(140, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxSB_RotateZ"));
	WxSB_RotateZ->Enable(false);
	WxBoxSizer5->Add(WxSB_RotateZ, 0, wxALIGN_CENTER | wxALL, 5);

	WxST_RotateZ = new wxStaticText(this, ID_WXST_ROTATEZ, _("0  "), wxPoint(67, 62), wxDefaultSize, 0, _("WxST_RotateZ"));
	WxBoxSizer5->Add(WxST_RotateZ, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer9 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer9, 0, wxALIGN_CENTER | wxALL, 5);

	WxStaticText7 = new wxStaticText(this, ID_WXSTATICTEXT7, _("Zbli¿enie"), wxPoint(49, 5), wxDefaultSize, 0, _("WxStaticText7"));
	WxBoxSizer9->Add(WxStaticText7, 0, wxALIGN_CENTER | wxALL, 5);

	WxSB_TransZ = new wxScrollBar(this, ID_WXSB_TRANSZ, wxPoint(5, 34), wxSize(139, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxSB_TransZ"));
	WxSB_TransZ->Enable(false);
	WxBoxSizer9->Add(WxSB_TransZ, 0, wxALIGN_CENTER | wxALL, 5);

	WxST_TransZ = new wxStaticText(this, ID_WXST_SCALEX, _("1.0  "), wxPoint(62, 62), wxDefaultSize, 0, _("WxST_TransZ"));
	WxBoxSizer9->Add(WxST_TransZ, 0, wxALIGN_CENTER | wxALL, 5);

	WxOpenFileDialog = new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);

	SetTitle(_("Projekt 3: Anaglify"));
	SetIcon(wxNullIcon);

	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();

	////GUI Items Creation End
	WxOpenFileDialog->SetWildcard("Geometry file (*.geo)|*.geo");

	WxSB_RotateX->SetScrollbar(0, 1, 361, 1, true);
	WxSB_RotateX->Enable(true);
	WxSB_RotateY->SetScrollbar(0, 1, 361, 1, true);
	WxSB_RotateY->Enable(true);
	WxSB_RotateZ->SetScrollbar(0, 1, 361, 1, true);
	WxSB_RotateZ->Enable(true);

	WxSB_TransZ->SetScrollbar(50, 1, 101, 1, true);
	WxSB_TransZ->Enable(true);
}

void Anaglyphs::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}


/*
 * WxButtonLoadClick
 */
void Anaglyphs::WxButtonLoadClick(wxCommandEvent& event)
{
	if (WxOpenFileDialog->ShowModal() == wxID_OK)
	{
		double x1, y1, z1, x2, y2, z2;
		int size;
  
		std::string line;
		std::ifstream in(WxOpenFileDialog->GetPath().ToAscii());
		if (in.is_open())
		{
			x_start.clear();y_start.clear();z_start.clear();
			x_end.clear();y_end.clear();z_end.clear();
			while (!in.eof())
			{
				in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> size;
				x_start.push_back(x1);
				x_end.push_back(x2);
				
				y_start.push_back(y1);
				y_end.push_back(y2);
				
				z_start.push_back(z1);
				z_end.push_back(z2);
				
				edge_width.push_back(size);
			}
			in.close();
		}
	}
}

void Anaglyphs::Repaint()
{
	wxClientDC dc1(WxPanel);
	wxBufferedDC dc(&dc1);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	int w, h;

	WxPanel->GetSize(&w, &h);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	Matrix4 translate_matrix;


	translate_matrix.data[0][3] = 0;
	translate_matrix.data[1][3] = 0;
	translate_matrix.data[2][3] = (WxSB_TransZ->GetThumbPosition() - 50.) / 30.;
	translate_matrix.data[0][0] = translate_matrix.data[1][1] = translate_matrix.data[2][2] = 1.;

	Matrix4 rotate_matrix_x, rotate_matrix_y, rotate_matrix_z;
	Matrix4 rotate_matrix;


	double rotate_over_x = (WxSB_RotateX->GetThumbPosition());
	double rotate_over_y = (WxSB_RotateY->GetThumbPosition());
	double rotate_over_z = (WxSB_RotateZ->GetThumbPosition());

	rotate_matrix_x.data[0][0] = rotate_matrix.data[3][3] = 1.;
	rotate_matrix_x.data[1][1] = rotate_matrix_x.data[2][2] = cos((rotate_over_x*M_PI) / 180);
	rotate_matrix_x.data[1][2] = -sin((rotate_over_x*M_PI) / 180);
	rotate_matrix_x.data[2][1] = sin((rotate_over_x*M_PI) / 180);

	rotate_matrix_y.data[1][1] = rotate_matrix_y.data[3][3] = 1.;
	rotate_matrix_y.data[0][0] = rotate_matrix_y.data[2][2] = cos((rotate_over_y*M_PI) / 180);
	rotate_matrix_y.data[0][2] = sin((rotate_over_y*M_PI) / 180);
	rotate_matrix_y.data[2][0] = -sin((rotate_over_y*M_PI) / 180);

	rotate_matrix_z.data[2][2] = rotate_matrix_z.data[3][3] = 1.;
	rotate_matrix_z.data[0][0] = rotate_matrix_z.data[1][1] = cos((rotate_over_z*M_PI) / 180);
	rotate_matrix_z.data[0][1] = -sin((rotate_over_z*M_PI) / 180);
	rotate_matrix_z.data[1][0] = sin((rotate_over_z*M_PI) / 180);

	rotate_matrix = rotate_matrix_x * rotate_matrix_y * rotate_matrix_z;

	Matrix4 final_matrix;
	final_matrix = translate_matrix * rotate_matrix;

	Vector4 start_vector, end_vector;
	Vector4 start_vector1, end_vector1;

	wxPen pen = dc.GetPen();

	for (unsigned i = 0; i < x_start.size(); i++)
	{
		pen.SetColour(255, 0, 0);
		pen.SetWidth(edge_width[i]);
		dc.SetPen(pen);

		start_vector.Set(x_start[i], y_start[i], z_start[i]);
		end_vector.Set(x_end[i], y_end[i], z_end[i]);

		start_vector = final_matrix * start_vector;
		end_vector = final_matrix * end_vector;

		start_vector.Set((start_vector.GetX() / (-1 + start_vector.GetZ() / d)) * w / 2 + w / 2, (start_vector.GetY() / (-1 + start_vector.GetZ() / d)) * h / 2 + h / 2, z_end[i]);
		end_vector.Set((end_vector.GetX() / (-1 + end_vector.GetZ() / d)) * w / 2 + w / 2, (end_vector.GetY() / (-1 + end_vector.GetZ() / d)) * h / 2 + h / 2, z_end[i]);

		dc.DrawLine(start_vector.GetX(), start_vector.GetY(), end_vector.GetX(), end_vector.GetY());
	}

	translate_matrix.data[0][3] += 0.02;
	final_matrix = translate_matrix * rotate_matrix;
	for (unsigned i = 0; i < x_start.size(); i++)
	{
		pen.SetColour(0, 0, 255);
		pen.SetWidth(edge_width[i]);
		dc.SetPen(pen);

		start_vector1.Set(x_start[i], y_start[i], z_start[i]);
		end_vector1.Set(x_end[i], y_end[i], z_end[i]);

		start_vector1 = final_matrix * start_vector1;
		end_vector1 = final_matrix * end_vector1;

		start_vector1.Set((start_vector1.GetX() / (-1 + start_vector1.GetZ() / d)) * w / 2 + w / 2, (start_vector1.GetY() / (-1 + start_vector1.GetZ() / d)) * h / 2 + h / 2, z_end[i]);
		end_vector1.Set((end_vector1.GetX() / (-1 + end_vector1.GetZ() / d)) * w / 2 + w / 2, (end_vector1.GetY() / (-1 + end_vector1.GetZ() / d)) * h / 2 + h / 2, z_end[i]);

		dc.DrawLine(start_vector1.GetX(), start_vector1.GetY(), end_vector1.GetX(), end_vector1.GetY());
	}
}

/*
 * WxPanelUpdateUI
 */
void Anaglyphs::WxPanelUpdateUI(wxUpdateUIEvent& event)
{
 Repaint();
}


/*
 * WxSB_RotateXScroll
 */
void Anaglyphs::WxSB_RotateXScroll(wxScrollEvent& event)
{
 wxString str;
 str << (WxSB_RotateX->GetThumbPosition());
 WxST_RotateX->SetLabel(str);
 Repaint();
}

/*
 * WxSB_RotateYScroll
 */
void Anaglyphs::WxSB_RotateYScroll(wxScrollEvent& event)
{
 wxString str;
 str << (WxSB_RotateY->GetThumbPosition());
 WxST_RotateY->SetLabel(str);
 Repaint();
}

/*
 * WxSB_RotateZScroll
 */
void Anaglyphs::WxSB_RotateZScroll(wxScrollEvent& event)
{
 wxString str;
 str << (WxSB_RotateZ->GetThumbPosition());
 WxST_RotateZ->SetLabel(str);
 Repaint();
}

/*
 * WxSB_ScaleXScroll
 */
void Anaglyphs::WxSB_TransZScroll(wxScrollEvent& event)
{
	wxString str;
	str << (WxSB_TransZ->GetThumbPosition() - 50) / 30.0;
	WxST_TransZ->SetLabel(str);
	Repaint();	
}
