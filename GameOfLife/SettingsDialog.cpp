#define GRID_SIZE_ID 20001
#define INTERVAL_ID 20002
#define DEAD_CELL_ID 20003
#define LIVING_CELL_ID 20004
#define GRID_LINE_ID 20005
#define RESET_SETTINGS_ID 20006

#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
	EVT_BUTTON(wxID_OK, SettingsDialog::OnOkButtonClick)
	EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancelButtonClick)
	EVT_BUTTON(RESET_SETTINGS_ID, SettingsDialog::OnResetSettingsButtonClick)
wxEND_EVENT_TABLE()

void SettingsDialog::LoadSettings()
{
	gridSizeCtrl->SetValue(rSettings.gridSize);
	intervalCtrl->SetValue(rSettings.interval);
	deadColorCtrl->SetColour(rSettings.GetDeadCellColor());
	livingColorCtrl->SetColour(rSettings.GetLivingCellColor());
	gridLineColorCtrl->SetColour(rSettings.GetGridLineColor());
}

void SettingsDialog::SaveSettings()
{
	rSettings.gridSize = gridSizeCtrl->GetValue();
	rSettings.interval = intervalCtrl->GetValue();
	rSettings.SetDeadCellColor(deadColorCtrl->GetColour());
	rSettings.SetLivingCellColor(livingColorCtrl->GetColour());
	rSettings.SetGridLineColor(gridLineColorCtrl->GetColour());
	rSettings.SaveSettingsFile();
}

void SettingsDialog::OnOkButtonClick(wxCommandEvent& okButtonEvent)
{
	SaveSettings();
	EndModal(wxID_OK);
}

void SettingsDialog::OnCancelButtonClick(wxCommandEvent& cancelButtonEvent)
{

	EndModal(wxID_CANCEL);
}

void SettingsDialog::OnResetSettingsButtonClick(wxCommandEvent& resetButtonEvent)
{
	rSettings.RestoreSettings();
	LoadSettings();
	Refresh();
}

SettingsDialog::SettingsDialog(wxWindow* mainWindowPtr, GameSettings& settings) : 
	wxDialog(mainWindowPtr, wxID_ANY, "Configure Settings"),
	pMainSizer(new wxBoxSizer(wxVERTICAL)),
	rSettings(settings)
{
	SetSizer(pMainSizer);
	
	//grid size
	wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* gridSizeLabel = new wxStaticText(this, wxID_ANY, "Grid Size");
	gridSizeCtrl = new wxSpinCtrl(this, GRID_SIZE_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, INT_MAX);
	
	gridSizeSizer->Add(gridSizeLabel);
	gridSizeSizer->Add(gridSizeCtrl);
	pMainSizer->Add(gridSizeSizer);

	//interval
	wxBoxSizer* intervalSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* intervalLabel = new wxStaticText(this, wxID_ANY, "Interval (ms)");
	intervalCtrl = new wxSpinCtrl(this, INTERVAL_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, INT_MAX);
	
	intervalSizer->Add(intervalLabel);
	intervalSizer->Add(intervalCtrl);
	pMainSizer->Add(intervalSizer);

	//dead color
	wxBoxSizer* deadColorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* deadColorLabel = new wxStaticText(this, wxID_ANY, "Dead Cell Color");
	deadColorCtrl = new wxColourPickerCtrl(this, DEAD_CELL_ID);
	
	deadColorSizer->Add(deadColorLabel);
	deadColorSizer->Add(deadColorCtrl);
	pMainSizer->Add(deadColorSizer);

	//alive color
	wxBoxSizer* livingColorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* livingColorLabel = new wxStaticText(this, wxID_ANY, "Living Cell Color");
	livingColorCtrl = new wxColourPickerCtrl(this, LIVING_CELL_ID);
	
	livingColorSizer->Add(livingColorLabel);
	livingColorSizer->Add(livingColorCtrl);
	pMainSizer->Add(livingColorSizer);

	//grid line color
	wxBoxSizer* gridLineColorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* gridLineColorLabel = new wxStaticText(this, wxID_ANY, "Grid Lines Color");
	gridLineColorCtrl = new wxColourPickerCtrl(this, GRID_LINE_ID);

	gridLineColorSizer->Add(gridLineColorLabel);
	gridLineColorSizer->Add(gridLineColorCtrl);
	pMainSizer->Add(gridLineColorSizer);

	//restore default
	wxButton* resetSettingsButton = new wxButton(this, RESET_SETTINGS_ID, "Restore Default Settings");	
	pMainSizer->Add(resetSettingsButton);

	//ok or cancel
	wxSizer* confirmSizer = CreateButtonSizer(wxOK | wxCANCEL);
	pMainSizer->Add(confirmSizer);

	LoadSettings();
}

SettingsDialog::~SettingsDialog()
{
}
