#include <algorithm>

#include "coder_encoder77.h"
#include "coding_decoding_lz78.h"
#include "hoffmaan.h"
#include "shennon_fano.h"
#include <iostream>
#include <map>


using namespace std;


int main()
{
	setlocale(LC_ALL, "rus");
	string a="aaaabbbbbbbbhbhbhddsl";


	//coder_encoder fuck(6,a);

	//string aaaa = fuck.LZ77_encode(4,a);
	//cout << aaaa<<endl;
	//string bb = fuck.LZ77_decode(aaaa);
	//cout << bb;

	coding_decoding_lz78 b;
	
	string ssss, sss=a;
	b.encode_78(sss, ssss);
	cout << ssss << endl;
	cout << b.decode_78(ssss) << endl;




	hoffmaan h;
	string fa = h.encode_text(a);
	cout << fa<<endl;
	string faq = h.decode_text(fa);
	cout << faq<<endl;


	shennon_fano f(a);
	string q = f.encode(a);
	cout << q<<endl;
	string ss = f.decode(q);
	cout << ss<<endl;
	f.display(f.prpb.size(), f.p);
	
	return 0;

}