///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 30 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx_html_report_panel.h"

#include "dialog_netlist_base.h"

///////////////////////////////////////////////////////////////////////////

DIALOG_NETLIST_BASE::DIALOG_NETLIST_BASE( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : DIALOG_SHIM( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bMainSizer;
	bMainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bUpperSizer;
	bUpperSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bleftSizer;
	bleftSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bnetlistOptSizer;
	bnetlistOptSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bmodulesOptSizer;
	bmodulesOptSizer = new wxBoxSizer( wxVERTICAL );
	
	wxString m_Select_By_TimestampChoices[] = { _("Reference"), _("Timestamp") };
	int m_Select_By_TimestampNChoices = sizeof( m_Select_By_TimestampChoices ) / sizeof( wxString );
	m_Select_By_Timestamp = new wxRadioBox( this, wxID_ANY, _("Footprint Selection:"), wxDefaultPosition, wxDefaultSize, m_Select_By_TimestampNChoices, m_Select_By_TimestampChoices, 1, wxRA_SPECIFY_COLS );
	m_Select_By_Timestamp->SetSelection( 0 );
	m_Select_By_Timestamp->SetToolTip( _("Select how footprints are recognized:\nby their reference (U1, R3...) (normal setting)\nor their time stamp (special setting after a full schematic reannotation)") );
	
	bmodulesOptSizer->Add( m_Select_By_Timestamp, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_ChangeExistingFootprintCtrlChoices[] = { _("Keep"), _("Change") };
	int m_ChangeExistingFootprintCtrlNChoices = sizeof( m_ChangeExistingFootprintCtrlChoices ) / sizeof( wxString );
	m_ChangeExistingFootprintCtrl = new wxRadioBox( this, wxID_ANY, _("Exchange Footprint:"), wxDefaultPosition, wxDefaultSize, m_ChangeExistingFootprintCtrlNChoices, m_ChangeExistingFootprintCtrlChoices, 1, wxRA_SPECIFY_COLS );
	m_ChangeExistingFootprintCtrl->SetSelection( 0 );
	m_ChangeExistingFootprintCtrl->SetToolTip( _("Keep or change an existing footprint when the netlist gives a different footprint") );
	
	bmodulesOptSizer->Add( m_ChangeExistingFootprintCtrl, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	bnetlistOptSizer->Add( bmodulesOptSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bTracksSizer;
	bTracksSizer = new wxBoxSizer( wxVERTICAL );
	
	wxString m_DeleteBadTracksChoices[] = { _("Keep"), _("Delete") };
	int m_DeleteBadTracksNChoices = sizeof( m_DeleteBadTracksChoices ) / sizeof( wxString );
	m_DeleteBadTracks = new wxRadioBox( this, wxID_ANY, _("Tracks Joining Multiple Nets:"), wxDefaultPosition, wxDefaultSize, m_DeleteBadTracksNChoices, m_DeleteBadTracksChoices, 1, wxRA_SPECIFY_COLS );
	m_DeleteBadTracks->SetSelection( 0 );
	m_DeleteBadTracks->SetToolTip( _("Keep or delete tracks creating a short circuit between two nets after a netlist change") );
	
	bTracksSizer->Add( m_DeleteBadTracks, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_RemoveExtraFootprintsCtrlChoices[] = { _("Keep"), _("Delete") };
	int m_RemoveExtraFootprintsCtrlNChoices = sizeof( m_RemoveExtraFootprintsCtrlChoices ) / sizeof( wxString );
	m_RemoveExtraFootprintsCtrl = new wxRadioBox( this, wxID_ANY, _("Extra Footprints:"), wxDefaultPosition, wxDefaultSize, m_RemoveExtraFootprintsCtrlNChoices, m_RemoveExtraFootprintsCtrlChoices, 1, wxRA_SPECIFY_COLS );
	m_RemoveExtraFootprintsCtrl->SetSelection( 0 );
	m_RemoveExtraFootprintsCtrl->SetToolTip( _("Remove footprints found on the Board but not in netlist\nNote: only not locked footprints will be removed") );
	
	bTracksSizer->Add( m_RemoveExtraFootprintsCtrl, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxString m_rbSingleNetsChoices[] = { _("Keep"), _("Delete") };
	int m_rbSingleNetsNChoices = sizeof( m_rbSingleNetsChoices ) / sizeof( wxString );
	m_rbSingleNets = new wxRadioBox( this, wxID_ANY, _("Single Pad Nets:"), wxDefaultPosition, wxDefaultSize, m_rbSingleNetsNChoices, m_rbSingleNetsChoices, 1, wxRA_SPECIFY_COLS );
	m_rbSingleNets->SetSelection( 0 );
	bTracksSizer->Add( m_rbSingleNets, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	bnetlistOptSizer->Add( bTracksSizer, 1, wxEXPAND, 5 );
	
	
	bleftSizer->Add( bnetlistOptSizer, 1, wxEXPAND, 5 );
	
	
	bUpperSizer->Add( bleftSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bRightSizerButtons;
	bRightSizerButtons = new wxBoxSizer( wxVERTICAL );
	
	
	bRightSizerButtons->Add( 0, 0, 1, wxALL|wxEXPAND, 5 );
	
	m_buttonRead = new wxButton( this, ID_READ_NETLIST_FILE, _("Read Current Netlist"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRead->SetDefault(); 
	m_buttonRead->SetToolTip( _("Read the current netlist and update connections and connectivity info") );
	
	bRightSizerButtons->Add( m_buttonRead, 0, wxEXPAND|wxALL, 5 );
	
	m_buttonClose = new wxButton( this, wxID_CANCEL, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bRightSizerButtons->Add( m_buttonClose, 0, wxALL|wxEXPAND, 5 );
	
	m_buttonFPTest = new wxButton( this, ID_TEST_NETLIST, _("Test Footprints"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonFPTest->SetToolTip( _("Read the current netlist file and list missing and extra footprints") );
	
	bRightSizerButtons->Add( m_buttonFPTest, 0, wxEXPAND|wxALL, 5 );
	
	m_buttonRebild = new wxButton( this, ID_COMPILE_RATSNEST, _("Rebuild Board Connectivity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRebild->SetToolTip( _("Rebuild the full ratsnest (useful after a manual pad netname edition)") );
	
	bRightSizerButtons->Add( m_buttonRebild, 0, wxEXPAND|wxALL, 5 );
	
	
	bUpperSizer->Add( bRightSizerButtons, 0, wxBOTTOM|wxLEFT|wxTOP, 5 );
	
	
	bMainSizer->Add( bUpperSizer, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_staticline11 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bMainSizer->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bCenterSizer;
	bCenterSizer = new wxBoxSizer( wxVERTICAL );
	
	m_checkDryRun = new wxCheckBox( this, wxID_ANY, _("Dry run. Only report changes in message panel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkDryRun->SetToolTip( _("Dry Run:\nThe netlist is read, but no change is actually made on board.\nChanges are only reported in message panel, for info") );
	
	bCenterSizer->Add( m_checkDryRun, 0, wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_checkBoxSilentMode = new wxCheckBox( this, wxID_ANY, _("Silent mode"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxSilentMode->SetToolTip( _("Silent mode:\nDo not show the warning message before reading the netlist") );
	
	bCenterSizer->Add( m_checkBoxSilentMode, 0, wxRIGHT|wxLEFT, 5 );
	
	
	bMainSizer->Add( bCenterSizer, 0, wxALL|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bMainSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bLowerSizer;
	bLowerSizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerNetlistFilename;
	bSizerNetlistFilename = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* staticTextNetlistFile;
	staticTextNetlistFile = new wxStaticText( this, wxID_ANY, _("Netlist file:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextNetlistFile->Wrap( -1 );
	bSizerNetlistFilename->Add( staticTextNetlistFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_NetlistFilenameCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerNetlistFilename->Add( m_NetlistFilenameCtrl, 1, wxBOTTOM|wxEXPAND|wxTOP, 5 );
	
	m_browseButton = new wxBitmapButton( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	bSizerNetlistFilename->Add( m_browseButton, 0, 0, 5 );
	
	
	bLowerSizer->Add( bSizerNetlistFilename, 0, wxEXPAND, 5 );
	
	m_MessageWindow = new WX_HTML_REPORT_PANEL( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_MessageWindow->SetMinSize( wxSize( -300,150 ) );
	
	bLowerSizer->Add( m_MessageWindow, 1, wxEXPAND | wxALL, 5 );
	
	
	bMainSizer->Add( bLowerSizer, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	
	this->SetSizer( bMainSizer );
	this->Layout();
	bMainSizer->Fit( this );
	
	// Connect Events
	m_buttonRead->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnReadNetlistFileClick ), NULL, this );
	m_buttonRead->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( DIALOG_NETLIST_BASE::OnUpdateUIValidNetlistFile ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnCancelClick ), NULL, this );
	m_buttonFPTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnTestFootprintsClick ), NULL, this );
	m_buttonFPTest->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( DIALOG_NETLIST_BASE::OnUpdateUIValidNetlistFile ), NULL, this );
	m_buttonRebild->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnCompileRatsnestClick ), NULL, this );
	m_buttonRebild->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( DIALOG_NETLIST_BASE::OnUpdateUIValidNetlistFile ), NULL, this );
	m_checkBoxSilentMode->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnClickSilentMode ), NULL, this );
	m_browseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnOpenNetlistClick ), NULL, this );
}

DIALOG_NETLIST_BASE::~DIALOG_NETLIST_BASE()
{
	// Disconnect Events
	m_buttonRead->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnReadNetlistFileClick ), NULL, this );
	m_buttonRead->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( DIALOG_NETLIST_BASE::OnUpdateUIValidNetlistFile ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnCancelClick ), NULL, this );
	m_buttonFPTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnTestFootprintsClick ), NULL, this );
	m_buttonFPTest->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( DIALOG_NETLIST_BASE::OnUpdateUIValidNetlistFile ), NULL, this );
	m_buttonRebild->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnCompileRatsnestClick ), NULL, this );
	m_buttonRebild->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( DIALOG_NETLIST_BASE::OnUpdateUIValidNetlistFile ), NULL, this );
	m_checkBoxSilentMode->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnClickSilentMode ), NULL, this );
	m_browseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_NETLIST_BASE::OnOpenNetlistClick ), NULL, this );
	
}
