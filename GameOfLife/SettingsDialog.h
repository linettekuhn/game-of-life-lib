#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include "GameSettings.h"

class SettingsDialog : public wxDialog
{
private:
	wxBoxSizer* pMainSizer;
	GameSettings& rSettings;
	
	wxSpinCtrl* gridSizeCtrl;
	wxSpinCtrl* intervalCtrl;
	wxColourPickerCtrl* deadColorCtrl;
	wxColourPickerCtrl* livingColorCtrl;

	void LoadSettings();
	void SaveSettings();
	void OnOkButtonClick(wxCommandEvent& okButtonEvent);
	void OnCancelButtonClick(wxCommandEvent& cancelButtonEvent);
public:
	SettingsDialog(wxWindow* mainWindowPtr, GameSettings& settings);
	~SettingsDialog();
	wxDECLARE_EVENT_TABLE();
};

