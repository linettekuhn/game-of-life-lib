#define GRID_SIZE_ID 20001
#define INTERVAL_ID 20002
#define DEAD_CELL_ID 20003
#define LIVING_CELL_ID 20004

#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
	EVT_BUTTON(wxID_OK, SettingsDialog::OnOkButtonClick)
	EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancelButtonClick)
wxEND_EVENT_TABLE()

void SettingsDialog::LoadSettings()
{
	gridSizeCtrl->SetValue(rSettings.gridSize);
	intervalCtrl->SetValue(rSettings.interval);
	deadColorCtrl->SetColour(rSettings.GetDeadCellColor());
	livingColorCtrl->SetColour(rSettings.GetLivingCellColor());
}

void SettingsDialog::SaveSettings()
{
	rSettings.gridSize = gridSizeCtrl->GetValue();
	rSettings.interval = intervalCtrl->GetValue();
	rSettings.SetDeadCellColor(deadColorCtrl->GetColour());
	rSettings.SetLivingCellColor(livingColorCtrl->GetColour());
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

SettingsDialog::SettingsDialog(wxWindow* mainWindowPtr, GameSettings& settings) : wxDialog(mainWindowPtr, wxID_ANY, "Configure Settings"),
pMainSizer(new wxBoxSizer(wxVERTICAL)),
rSettings(settings)
{
	SetSizer(pMainSizer);
	
	wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* gridSizeLabel = new wxStaticText(this, wxID_ANY, "Grid Size");
	gridSizeCtrl = new wxSpinCtrl(this, GRID_SIZE_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, INT_MAX);
	
	gridSizeSizer->Add(gridSizeLabel);
	gridSizeSizer->Add(gridSizeCtrl);
	pMainSizer->Add(gridSizeSizer);

	wxBoxSizer* intervalSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* intervalLabel = new wxStaticText(this, wxID_ANY, "Interval (ms)");
	intervalCtrl = new wxSpinCtrl(this, INTERVAL_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, INT_MAX);
	
	intervalSizer->Add(intervalLabel);
	intervalSizer->Add(intervalCtrl);
	pMainSizer->Add(intervalSizer);

	wxBoxSizer* deadColorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* deadColorLabel = new wxStaticText(this, wxID_ANY, "Dead Cell Color");
	deadColorCtrl = new wxColourPickerCtrl(this, DEAD_CELL_ID);
	
	deadColorSizer->Add(deadColorLabel);
	deadColorSizer->Add(deadColorCtrl);
	pMainSizer->Add(deadColorSizer);

	wxBoxSizer* livingColorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* livingColorLabel = new wxStaticText(this, wxID_ANY, "Living Cell Color");
	livingColorCtrl = new wxColourPickerCtrl(this, LIVING_CELL_ID);
	
	livingColorSizer->Add(livingColorLabel);
	livingColorSizer->Add(livingColorCtrl);
	pMainSizer->Add(livingColorSizer);

	wxSizer* confirmSizer = CreateButtonSizer(wxOK | wxCANCEL);
	pMainSizer->Add(confirmSizer);

	LoadSettings();
}

SettingsDialog::~SettingsDialog()
{
}
