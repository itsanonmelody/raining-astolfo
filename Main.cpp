#include "App.h"

#include <algorithm>

#ifdef _RELEASE
#include <windows.h>

#include "Misc/Util.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	std::vector<std::string> args = Util::SplitString(lpCmdLine);

	App app;
	app.ProcessArguments(args);
	app.Init();
	app.Run();

	return 0;
}


#endif // _RELEASE

#ifndef _RELEASE
int main(int argc, const char* argv[])
{
	std::vector<std::string> args;
	std::transform(
		argv + 1,
		argv + argc,
		std::back_inserter(args),
		[](const char* arg) {
			return std::string(arg);
		}
	);

	App app;
	app.ProcessArguments(args);
	app.Init();

	int statusCode = app.Run();
	return statusCode;
}
#endif
