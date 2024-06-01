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
	
	int padding = 5;

	//grid size
	wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* gridSizeLabel = new wxStaticText(this, wxID_ANY, "Grid Size");
	gridSizeCtrl = new wxSpinCtrl(this, GRID_SIZE_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, INT_MAX);
	
	gridSizeSizer->Add(gridSizeLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	gridSizeSizer->Add(gridSizeCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	pMainSizer->Add(gridSizeSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, padding);

	//interval
	wxBoxSizer* intervalSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* intervalLabel = new wxStaticText(this, wxID_ANY, "Interval (ms)");
	intervalCtrl = new wxSpinCtrl(this, INTERVAL_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, INT_MAX);
	
	intervalSizer->Add(intervalLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	intervalSizer->Add(intervalCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	pMainSizer->Add(intervalSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, padding);

	//dead color
	wxBoxSizer* deadColorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* deadColorLabel = new wxStaticText(this, wxID_ANY, "Dead Cell Color");
	deadColorCtrl = new wxColourPickerCtrl(this, DEAD_CELL_ID);
	
	deadColorSizer->Add(deadColorLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	deadColorSizer->Add(deadColorCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	pMainSizer->Add(deadColorSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, padding);

	//alive color
	wxBoxSizer* livingColorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* livingColorLabel = new wxStaticText(this, wxID_ANY, "Living Cell Color");
	livingColorCtrl = new wxColourPickerCtrl(this, LIVING_CELL_ID);
	
	livingColorSizer->Add(livingColorLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	livingColorSizer->Add(livingColorCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	pMainSizer->Add(livingColorSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, padding);

	//grid line color
	wxBoxSizer* gridLineColorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* gridLineColorLabel = new wxStaticText(this, wxID_ANY, "Grid Lines Color");
	gridLineColorCtrl = new wxColourPickerCtrl(this, GRID_LINE_ID);

	gridLineColorSizer->Add(gridLineColorLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	gridLineColorSizer->Add(gridLineColorCtrl, 0, wxALL | wxALIGN_CENTER_VERTICAL, padding);
	pMainSizer->Add(gridLineColorSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, padding);

	//restore default
	wxButton* resetSettingsButton = new wxButton(this, RESET_SETTINGS_ID, "Restore Default Settings");	
	pMainSizer->Add(resetSettingsButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, padding);

	//ok or cancel
	wxSizer* confirmSizer = CreateButtonSizer(wxOK | wxCANCEL);
	pMainSizer->Add(confirmSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, padding);

	SetMinSize(pMainSizer->GetMinSize());
	Fit();

	LoadSettings();
}

SettingsDialog::~SettingsDialog()
{
}
