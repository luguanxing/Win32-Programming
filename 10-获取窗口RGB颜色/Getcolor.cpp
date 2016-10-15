#include <windows.h>
#include <iostream>
using namespace std;

int x,y;
int red, green, blue;
COLORREF color;
POINT point1, point2;
HWND hwnd;


int main() {
	cout << "wait fot 5 s" << endl;
	Sleep(5000);
	while(true) {
		GetCursorPos(&point1);
		color = ::GetPixel(::GetDC(hwnd), point1.x, point1.y);
		red = GetRValue(color);
		green = GetGValue(color);
		blue = GetBValue(color);
		if (point2.x != point1.x && point2.y != point1.y) {
			system("cls");
			cout << red << " " << green << " " << blue << endl;
			Sleep(10);
		}
		point2 = point1;
	}

	return 0;
}