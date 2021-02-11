
#include <windows.h>

// some code(s) were taken from [ https://bitbucket.org/knatech/ ]. 
typedef void (WINAPI *_EdSetBacklightBright)(int);
_EdSetBacklightBright EdSetBacklightBright = NULL;
extern _EdSetBacklightBright EdSetBacklightBright;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
										LPTSTR lpCmdLine, int nCmdShow){

	HWND SHARPSIM = FindWindow(_T("SHARP SIM"), NULL);
	// Kill it.
	PostMessage(SHARPSIM, WM_CLOSE, NULL, NULL);

	// Load SharpLib.dll
	static HMODULE sharpLib = LoadLibrary(_T("SharpLib.dll"));
	if(sharpLib == NULL){
		// load failed
		return -1;
	}
	
	// Get Proc address
	EdSetBacklightBright = (_EdSetBacklightBright)
			GetProcAddress(sharpLib, _T("EdSetBacklightBright"));

	if(EdSetBacklightBright == NULL){
		MessageBox(NULL, _T("GetProcAddress: FAILED"), _T("ERROR"), MB_OK);
	}

	// Change Brightness.
	EdSetBacklightBright(100);
	for(int i=0;i<5;i++){
		for(int _brightness=0; _brightness<=100; _brightness=_brightness+20){
			Sleep(50);
			EdSetBacklightBright(_brightness);
		}

		for(int __brightness=100; __brightness>=0; __brightness=__brightness-20){
			Sleep(50);
			EdSetBacklightBright(__brightness);
		}
	}

	// Free DLL.
	FreeLibrary(sharpLib);
	
	return EXIT_SUCCESS;
}

