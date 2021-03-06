///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 19 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DIALOG_GLOBAL_FOOTPRINTS_FIELDS_EDITION_BASE_H__
#define __DIALOG_GLOBAL_FOOTPRINTS_FIELDS_EDITION_BASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include "dialog_shim.h"
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DIALOG_GLOBAL_FOOTPRINTS_FIELDS_EDITION_BASE
///////////////////////////////////////////////////////////////////////////////
class DIALOG_GLOBAL_FOOTPRINTS_FIELDS_EDITION_BASE : public DIALOG_SHIM
{
	private:
	
	protected:
		wxCheckBox* m_ReferenceOpt;
		wxCheckBox* m_ValueOpt;
		wxCheckBox* m_OtherFields;
		wxStaticText* m_staticTextFilter;
		wxTextCtrl* m_ModuleFilter;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_SizeX_Value;
		wxStaticText* m_SizeXunit;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_SizeY_Value;
		wxStaticText* m_SizeYunit;
		wxStaticText* m_staticText9;
		wxTextCtrl* m_ThicknessValue;
		wxStaticText* m_ThicknessUnit;
		wxStaticLine* m_staticline;
		wxStdDialogButtonSizer* m_sdbSizerButtons;
		wxButton* m_sdbSizerButtonsOK;
		wxButton* m_sdbSizerButtonsCancel;
	
	public:
		
		DIALOG_GLOBAL_FOOTPRINTS_FIELDS_EDITION_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Set Text Size"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~DIALOG_GLOBAL_FOOTPRINTS_FIELDS_EDITION_BASE();
	
};

#endif //__DIALOG_GLOBAL_FOOTPRINTS_FIELDS_EDITION_BASE_H__
