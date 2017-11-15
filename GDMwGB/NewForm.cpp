#include "NewForm.h"

System::Void GDMwGB::NewForm::OkButtonClick(System::Object ^ sender, System::EventArgs ^ e)
{
	this->Done = true;
	this->Close();
	return System::Void();
}

System::Void GDMwGB::NewForm::CancelButtonClick(System::Object ^ sender, System::EventArgs ^ e)
{
	this->Done = false;
	this->Close();
	return System::Void();
}
