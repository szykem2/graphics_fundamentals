#include "Anaglyphs.h"
#include "vecmat.h"
#include "Sphere.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <wx/dcbuffer.h>
#include <wx/wfstream.h>
std::vector <double> x_start, x_end, y_start, y_end, z_start, z_end;
std::vector <int> edge_width;
std::vector <Sphere> spheres;
double d = -2.0;
int G = 0;
wxMemoryDC dcs;
wxBitmap bit(1024, 768);

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
BEGIN_EVENT_TABLE(Anaglyphs,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Anaglyphs::OnClose)
	
	EVT_COMMAND_SCROLL(ID_WXSB_CALIBRATE,Anaglyphs::WxSB_Calibrate)
	
	EVT_COMMAND_SCROLL(ID_WXSB_TRANSZ,Anaglyphs::WxSB_TransZScroll)
	
	EVT_COMMAND_SCROLL(ID_WXSB_ROTATEZ,Anaglyphs::WxSB_RotateZScroll)
	
	EVT_COMMAND_SCROLL(ID_WXSB_ROTATEY,Anaglyphs::WxSB_RotateYScroll)
	
	EVT_COMMAND_SCROLL(ID_WXSB_ROTATEX,Anaglyphs::WxSB_RotateXScroll)
	EVT_BUTTON(ID_WXBUTTONSAVE,Anaglyphs::WxButtonSaveClick)
	EVT_BUTTON(ID_WXBUTTONLOAD,Anaglyphs::WxButtonLoadClick)
	
	EVT_UPDATE_UI(ID_WXPANEL,Anaglyphs::WxPanelUpdateUI)
END_EVENT_TABLE()
////Event Table End

Anaglyphs::Anaglyphs(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
	: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	wxImage::AddHandler(new wxJPEGHandler);
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

	WxPanel = new wxPanel(this, ID_WXPANEL, wxPoint(369, 5), wxSize(213, 47));
	WxBoxSizer1->Add(WxPanel, 1, wxEXPAND | wxALL, 5);

	WxBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer6 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer6, 0, wxALIGN_CENTER | wxALL, 5);

	WxButtonLoad = new wxButton(this, ID_WXBUTTONLOAD, _("Wczytaj Geometriê"), wxPoint(5, 5), wxSize(124, 25), 0, wxDefaultValidator, _("WxButtonLoad"));
	WxBoxSizer6->Add(WxButtonLoad, 0, wxALIGN_CENTER | wxALL, 5);

	WxButtonSave = new wxButton(this, ID_WXBUTTONSAVE, _("Zapisz obraz"), wxPoint(6, 40), wxSize(122, 25), 0, wxDefaultValidator, _("WxButtonSave"));
	WxBoxSizer6->Add(WxButtonSave, 0, wxALIGN_CENTER | wxALL, 5);

	WxStaticText4 = new wxStaticText(this, ID_WXSTATICTEXT4, _("Rozdzielczoœæ:"), wxPoint(27, 75), wxDefaultSize, 0, _("WxStaticText4"));
	WxBoxSizer6->Add(WxStaticText4, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer6->Add(WxBoxSizer7, 0, wxALIGN_CENTER | wxALL, 5);

	XResolutionInput = new wxTextCtrl(this, ID_XRESOLUTIONINPUT, _("800"), wxPoint(5, 5), wxSize(35, 19), 0, wxDefaultValidator, _("XResolutionInput"));
	WxBoxSizer7->Add(XResolutionInput, 0, wxALIGN_CENTER | wxALL, 5);

	YResolutioninput = new wxTextCtrl(this, ID_YRESOLUTIONINPUT, _("600"), wxPoint(50, 5), wxSize(35, 19), 0, wxDefaultValidator, _("YResolutioninput"));
	WxBoxSizer7->Add(YResolutioninput, 0, wxALIGN_CENTER | wxALL, 5);

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

	WxST_TransZ = new wxStaticText(this, ID_WXST_TRANSZ, _("1.0  "), wxPoint(62, 62), wxDefaultSize, 0, _("WxST_TransZ"));
	WxBoxSizer9->Add(WxST_TransZ, 0, wxALIGN_CENTER | wxALL, 5);

	WxBoxSizer8 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer2->Add(WxBoxSizer8, 0, wxALIGN_CENTER | wxALL, 5);

	Kalib = new wxStaticText(this, ID_WXSTATICTEXT7, _("Kalibracja:"), wxPoint(45, 5), wxDefaultSize, 0, _("Kalib"));
	WxBoxSizer8->Add(Kalib, 0, wxALIGN_CENTER | wxALL, 5);

	Calibration = new wxScrollBar(this, ID_WXSB_CALIBRATE, wxPoint(5, 34), wxSize(139, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("Calibration"));
	Calibration->Enable(false);
	WxBoxSizer8->Add(Calibration, 0, wxALIGN_CENTER | wxALL, 5);

	Calibration_label = new wxStaticText(this, ID_WXST_CALIBRATE, _("1.0  "), wxPoint(62, 62), wxDefaultSize, 0, _("Calibration_label"));
	WxBoxSizer8->Add(Calibration_label, 0, wxALIGN_CENTER | wxALL, 5);

	WxOpenFileDialog =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);

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

	WxSB_TransZ->SetScrollbar(0, 1, 101, 1, true);
	WxSB_TransZ->Enable(true);
	Calibration->SetScrollbar(0, 1, 255, 1, true);
	Calibration->Enable(true);
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
		std::string line;
		std::ifstream in(WxOpenFileDialog->GetPath().ToAscii());
		if (in.is_open())
		{
            int size;
            in >> size;
			x_start.clear();
			y_start.clear();
			z_start.clear();

			x_end.clear();
			y_end.clear();
			z_end.clear();

			edge_width.clear();
			spheres.clear();
			int it = 0;
			while (std::getline(in, line) && it <= size)
			{
				std::vector<std::string> vec;
				
				split(line, vec, ' ');
				if (vec[0] == "1") {
                    std::istringstream iss(vec[1]);
                    double val;
                    iss >> val;
					x_start.push_back(val);
					
					std::istringstream iss1(vec[4]);
                    iss1 >> val;
					x_end.push_back(val);

                    std::istringstream iss2(vec[2]);
                    iss2 >> val;
					y_start.push_back(val);
					
					std::istringstream iss3(vec[5]);
                    iss3 >> val;
					y_end.push_back(val);

                    std::istringstream iss4(vec[3]);
                    iss4 >> val;
					z_start.push_back(val);
					
					std::istringstream iss5(vec[6]);
                    iss5 >> val;
					z_end.push_back(val);
					
                    edge_width.push_back(atoi(vec[7].c_str()));
				}
				if (vec[0] == "2") {
                    double x, y, z, r;
                    std::istringstream iss(vec[1]);
                    double val;
                    iss >> x;
					
					std::istringstream iss1(vec[2]);
                    iss1 >> y;

                    std::istringstream iss2(vec[3]);
                    iss2 >> z;

					std::istringstream iss3(vec[4]);
                    iss3 >> r;

					spheres.push_back(Sphere(Point(x, y, z), r / 2.));
				}
				it++;
			}
			in.close();
		}
	}
}

void Anaglyphs::WxButtonSaveClick(wxCommandEvent& event)
{
	int x, y;
	try {
		if (XResolutionInput->GetLineLength(0) > 0)
			x = atoi(XResolutionInput->GetLineText(0).ToStdString().c_str());
		else
			x = 800;
		if (YResolutioninput->GetLineLength(0) > 0)
			y = atoi(YResolutioninput->GetLineText(0).ToStdString().c_str());
		else
			y = 600;
	}
	catch (...) {
		x = 800;
		y = 600;
	}
	wxImage img = bit.ConvertToImage();
	wxFileDialog
		saveFileDialog(this, _("Save file"), "", "",
			"JPG files (*.jpg)|*.jpg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxFileOutputStream output_stream(saveFileDialog.GetPath());
	if (!output_stream.IsOk())
	{
		wxLogError("Nie mo¿na zapisaæ obrazu w '%s'.", saveFileDialog.GetPath());
		return;
	}
	img = img.Rescale(x, y);
	img.SaveFile(output_stream, "image/jpeg");
}

void Anaglyphs::Repaint()
{
	bit = wxBitmap(WxPanel->GetSize().GetWidth(), WxPanel->GetSize().GetHeight()); 
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
	translate_matrix.data[2][3] = -(WxSB_TransZ->GetThumbPosition() - 50.) / 30.;
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

    pen.SetColour(255, 0, 0);

	for (unsigned i = 0; i < x_start.size(); i++)
	{
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

	translate_matrix.data[0][3] += 0.01;
	final_matrix = translate_matrix * rotate_matrix;
	for (unsigned i = 0; i < x_start.size(); i++)
	{
		pen.SetColour(0, G, 255);
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

	translate_matrix.data[0][3] -= 0.01;
	for (unsigned j = 0; j < spheres.size(); j++)
	{
		wxPen pen = dc.GetPen();
		pen.SetWidth(1);
		std::vector<Point> pointss = spheres[j].getStartPoints();
		std::vector<Point> pointse = spheres[j].getEndPoints();
		for (unsigned i = 0; i < pointss.size(); i++)
		{
				pen.SetColour(255, 0, 0);
				dc.SetPen(pen);

				start_vector.Set(pointss[i].x, pointss[i].y, pointss[i].z);
				end_vector.Set(pointse[i].x, pointse[i].y, pointse[i].z);

				start_vector = final_matrix * start_vector;
				end_vector = final_matrix * end_vector;

				start_vector.Set((start_vector.GetX() / (-1 + start_vector.GetZ() / d)) * w / 2 + w / 2, (start_vector.GetY() / (-1 + start_vector.GetZ() / d)) * h / 2 + h / 2, pointse[i].z);
				end_vector.Set((end_vector.GetX() / (-1 + end_vector.GetZ() / d)) * w / 2 + w / 2, (end_vector.GetY() / (-1 + end_vector.GetZ() / d)) * h / 2 + h / 2, pointse[i].z);

				dc.DrawLine(start_vector.GetX(), start_vector.GetY(), end_vector.GetX(), end_vector.GetY());
		}

		translate_matrix.data[0][3] += 0.02;
		final_matrix = translate_matrix * rotate_matrix;
		for (unsigned i = 0; i < pointse.size(); i++)
		{
				pen.SetColour(0, G, 255);
				dc.SetPen(pen);

				start_vector.Set(pointss[i].x, pointss[i].y, pointss[i].z);
				end_vector.Set(pointse[i].x, pointse[i].y, pointse[i].z);

				start_vector = final_matrix * start_vector;
				end_vector = final_matrix * end_vector;

				start_vector.Set((start_vector.GetX() / (-1 + start_vector.GetZ() / d)) * w / 2 + w / 2, (start_vector.GetY() / (-1 + start_vector.GetZ() / d)) * h / 2 + h / 2, pointse[i].z);
				end_vector.Set((end_vector.GetX() / (-1 + end_vector.GetZ() / d)) * w / 2 + w / 2, (end_vector.GetY() / (-1 + end_vector.GetZ() / d)) * h / 2 + h / 2, pointse[i].z);

				dc.DrawLine(start_vector.GetX(), start_vector.GetY(), end_vector.GetX(), end_vector.GetY());
		}
	}


	dcs.SelectObject(bit);
	dcs.Blit(wxCoord(0), wxCoord(0), wxCoord(WxPanel->GetSize().GetWidth()), wxCoord(WxPanel->GetSize().GetHeight()), &dc, wxCoord(0), wxCoord(0));
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

void Anaglyphs::WxSB_RotateZScroll(wxScrollEvent& event)
{
	wxString str;
	str << (WxSB_RotateZ->GetThumbPosition());
	WxST_RotateZ->SetLabel(str);
	Repaint();
}

void Anaglyphs::WxSB_TransZScroll(wxScrollEvent& event)
{
	wxString str;
	double f = (WxSB_TransZ->GetThumbPosition() - 50) / 30.0;
	f += 1.666666666666666;
	f *= 3./3.333333333333333;
	str << std::pow(2, f);
	WxST_TransZ->SetLabel(str);
	Repaint();	
}

void Anaglyphs::WxSB_Calibrate(wxScrollEvent& event) {
	wxString str;
	str << (Calibration->GetThumbPosition());
	Calibration_label->SetLabel(str);
	G = atoi(str.ToStdString().c_str());
	Repaint();
}


void split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos));
}
