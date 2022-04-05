#include "wx/print.h"
#include "wx/printdlg.h"
#include "wx/dcprint.h"
#include "wx/log.h"



class QuickPrint : public wxPrintout
{
	wxPageSetupDialogData m_page_setup;

	wxPaperSize m_paper_type;

	int m_orient;
	int m_page_amount;
	int m_margin_left, m_margin_right, m_margin_top, m_margin_bottom;

	float m_units_per_cm;

	int m_coord_system_width, m_coord_system_height;

public:

	QuickPrint(int page_amount, wxString title, float units_per_cm) : wxPrintout(title)
	{
		m_page_amount = page_amount;
		m_orient = wxPORTRAIT;
		m_paper_type = wxPAPER_A4;
		m_margin_left = 5;
		m_margin_right = 5;
		m_margin_bottom = 10;
		m_margin_top = 10;
		m_units_per_cm = units_per_cm;

	}

	bool performPageSetup(const bool showPageSetupDialog)
	{
		wxPrintData printdata;
		printdata.SetPrintMode(wxPRINT_MODE_PRINTER);
		printdata.SetOrientation(wxPORTRAIT);
		printdata.SetNoCopies(1);
		printdata.SetPaperId(m_paper_type);
		printdata.SetColour(false);

		m_page_setup = wxPageSetupData(printdata);
		m_page_setup.SetMarginTopLeft(wxPoint(m_margin_left, m_margin_top));
		m_page_setup.SetMarginBottomRight(wxPoint(m_margin_right, m_margin_bottom));

		if (showPageSetupDialog)
		{
			wxPageSetupDialog dialog(NULL, &m_page_setup);

			if (dialog.ShowModal() == wxID_OK)
			{
				m_page_setup = dialog.GetPageSetupData();
				m_orient = m_page_setup.GetPrintData().GetOrientation();
				m_paper_type = m_page_setup.GetPrintData().GetPaperId();

				wxPoint marginTopLeft = m_page_setup.GetMarginTopLeft();
				wxPoint marginBottomRight = m_page_setup.GetMarginBottomRight();
				m_margin_left = marginTopLeft.x;
				m_margin_right = marginBottomRight.x;
				m_margin_top = marginTopLeft.y;
				m_margin_bottom = marginBottomRight.y;
			}

			else
			{
				wxLogMessage("user canceled at first dialog");
				return false;
			}

		}

		return true;

	}

	void OnBeginPrinting()
	{

		wxSize papersize = m_page_setup.GetPaperSize();

		float large_side = std::max(papersize.GetWidth(), papersize.GetHeight());
		float small_side = std::min(papersize.GetWidth(), papersize.GetHeight());

		float large_side_cm = large_side / 10.0f;
		float small_side_cm = small_side / 10.0f;

		if (m_orient == wxPORTRAIT)

		{

			float ratio = float(large_side - m_margin_top - m_margin_bottom) / float(small_side - m_margin_left - m_margin_right);
			m_coord_system_width = (int)((small_side_cm - m_margin_left / 10.0f - m_margin_right / 10.0f) *m_units_per_cm);
			m_coord_system_height = m_coord_system_width * ratio;

		}

		else
		{
			float ratio = float(large_side - m_margin_left - m_margin_right) / float(small_side - m_margin_top - m_margin_bottom);

			m_coord_system_height = (int)((small_side_cm - m_margin_top / 10.0f - m_margin_bottom / 10.0f) *m_units_per_cm);
			m_coord_system_width = m_coord_system_height * ratio;
		}
	}

	wxPrintData getPrintData()
	{
		return m_page_setup.GetPrintData();
	}

	bool OnBeginDocument(int startPage, int endPage)
	{
		return wxPrintout::OnBeginDocument(startPage, endPage);
	}

	void GetPageInfo(int *minPage, int *maxPage, int *pageSelFrom, int *pageSelTo)
	{
		*minPage = 1;
		*maxPage = m_page_amount;

		*pageSelFrom = 1;
		*pageSelTo = m_page_amount;
	}

	bool HasPage(int pageNum)
	{
		return pageNum >= 1 && pageNum <= m_page_amount;
	}

	bool OnPrintPage(int pageNum)

	{
		FitThisSizeToPageMargins(wxSize(m_coord_system_width, m_coord_system_height), m_page_setup);

		wxRect fitRect = GetLogicalPageMarginsRect(m_page_setup);

		wxCoord xoff = (fitRect.width - m_coord_system_width) / 2;
		wxCoord yoff = (fitRect.height - m_coord_system_height) / 2;
		OffsetLogicalOrigin(xoff, yoff);

		wxDC* ptr = GetDC();

		if (ptr == NULL || !ptr->IsOk())
		{
			return false;
		}

		wxDC& dc = *ptr;

		const int x0 = 0;
		const int y0 = 0;
		const int width = m_coord_system_width;
		const int height = m_coord_system_height;
		const int x1 = x0 + width;
		const int y1 = y0 + height;

		const int center_x = x0 + width / 2;
		const int center_y = y0 + height / 2;

		dc.Clear();
		wxBitmap bmp("screenshot1.png", wxBITMAP_TYPE_PNG);
		dc.DrawBitmap(bmp, 0, 0);
		return true;
	}

};