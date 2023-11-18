#include "MainForm.h"

using namespace MagaFirstTermCourseProjectFormsApp;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainForm());
	return 0;
}

