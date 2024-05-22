#define GRID_SIZE_ID 10005
#define INTERVAL_ID 10006
#define DEAD_CELL_ID 10007
#define LIVING_CELL_ID 10008

#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
	EVT_BUTTON(wxID_OK, SettingsDialog::OnOkButtonClick)
	EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancelButtonClick)
wxEND_EVENT_TABLE()

void SettingsDialog::LoadSettings()
{
	gridSizeCtrl->SetValue(mSettings.gridSize);
	intervalCtrl->SetValue(mSettings.interval);
	deadColorCtrl->SetColour(mSettings.GetDeadCellColor());
	livingColorCtrl->SetColour(mSettings.GetLivingCellColor());
}

void SettingsDialog::SaveSettings()
{
	mSettings.gridSize = gridSizeCtrl->GetValue();
	mSettings.interval = intervalCtrl->GetValue();
	mSettings.SetDeadCellColor(deadColorCtrl->GetColour());
	mSettings.SetLivingCellColor(livingColorCtrl->GetColour());
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

SettingsDialog::SettingsDialog(wxWindow* mainWindowPtr) : wxDialog(mainWindowPtr, wxID_ANY, "Configure Settings"),
pMainSizer(new wxBoxSizer(wxVERTICAL))
{
	SetSizer(pMainSizer);
	
	LoadSettings();
	
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
}

SettingsDialog::~SettingsDialog()
{
}
