#include "coder_encoder.h"
#include <iostream>

using namespace std;


int main()
{
	string a="aaaabbbbbbbbhbhbhddsl";

	coder_encoder m(6);
	string f = m.LZ77_encode(4, a);
	cout << f<<endl;
	string aa = m.LZ77_decode(f);
	cout << aa;

}