//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("ecg_saveFile.cpp", fmAddFile);
USEFORM("ecg_viewer.cpp", fmEcgViewer);
USEFORM("ecg_main.cpp", fmMain);
USEFORM("addForms\addPeople.cpp", fmPerson);
USEFORM("baseForms\basePeople.cpp", fmBasePeople);
USEFORM("ecg_dbviewerSignale.cpp", fmViewSignal);
//---------------------------------------------------------------------------
#pragma link "ecgcore.lib"
#pragma link "ecgmysql.lib"
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfmMain), &fmMain);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
