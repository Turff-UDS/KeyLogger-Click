#include <iostream>
#include <windows.h>
#include "Helper.h"
#include "Base64.h"
#include "keyConstants.h"
#include "IO.h"
#include "Timer.h"

using namespace std;

int main() {

	MSG Msg;

	while (GetMessage(&Msg, NULL, 0, 0)) {

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return 0;
}