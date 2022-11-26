#include <algorithm>

#include "coder_encoder77.h"
#include "coding_decoding_lz78.h"
#include "RLE_coder_decoder.h"
#include "hoffmaan.h"
#include "shennon_fano.h"
#include <iostream>
#include <map>


using namespace std;


int main()
{
	setlocale(LC_ALL, "rus");
	string a="aaaabbbbbbbbbbbbbbbbbbhbhbhddsl";
	cout << "Практическая работа №7 \"Кодирование и сжатие данных методами без потерь.\". Резников Григорий." << endl << endl;
	cout << " (1):Кодирование методом RLE\n" <<
		" (2): Кодирование методом LZ77\n" <<
		" (3): Кодирование методом LZ78\n" <<
		" (4): Кодирование методом Шеннона-Фано\n" <<
		" (5): Кодирование методом Хаффмана\n" <<
		" (6): Декодирование методом RLE\n" <<
		" (7): Декодирование методом LZ77\n" <<
		" (8): Декодирование методом LZ78\n" <<
		" (9): Декодирование методом Шеннона-Фано\n" <<
		" (10): Декодирование методом Хаффмана\n" <<
		endl;

	coder_encoder* fac = new coder_encoder(6,a);

	//string aaaa = fac->LZ77_encode(4,a);
	//cout << aaaa<<endl;
	//string bb = fac->LZ77_decode(aaaa);
	//cout << bb;

	coding_decoding_lz78* b = new coding_decoding_lz78;
	RLE_coder_decoder d;
	string f;
	f = d.RLE_encode(a);
	cout << f << endl;
	cout << d.RLE_decode(f);
	
	//string ssss, sss=a;
	//b->encode_78(sss, ssss);
	//cout << ssss << endl;
	//cout << b->decode_78(ssss) << endl;

	hoffmaan h;
	//string fa = h.encode_text(a);
	//cout << fa<<endl;
	//string faq = h.decode_text(fa);
	//cout << faq<<endl;


	//shennon_fano* f = new shennon_fano(a);
	//string q = f->encode(a);
	//cout << q<<endl;
	//string ss = f->decode(q);
	//cout << ss<<endl;
	//f->display(f->prpb.size(), f->p);

	string ans, out;
	int sel;
	//while (true)
	//{
	//	cout << "Enter num of task" << endl;
	//	cin >> sel;
	//	switch (sel)
	//	{
	//	case 1:
	//		cout << "Enter encoding str" << endl;
	//		getline(cin,ans);
	//		cout<<d.RLE_encode(ans);
	//		break;
	//	case 2:
	//		cout << "Enter encoding str" << endl;
	//		getline(cin, ans);
	//		cout << d.RLE_encode(ans);
	//		break;
	//	case 3:
	//		cout << "Enter encoding str" << endl;
	//		getline(cin, ans);
	//		cout << d.RLE_encode(ans);
	//		break;
	//	case 4:
	//		cout << "Enter encoding str" << endl;
	//		getline(cin, ans);
	//		cout << d.RLE_encode(ans);
	//		break;
	//	case 5:
	//		cout << "Enter encoding str" << endl;
	//		getline(cin, ans);
	//		cout << d.RLE_encode(ans);
	//		break;
	//	}
	//}
	
	return 0;

}