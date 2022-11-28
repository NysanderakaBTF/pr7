#include <algorithm>
#include <fstream>

#include "coder_encoder77.h"
#include "coding_decoding_lz78.h"
#include "RLE_coder_decoder.h"
#include "hoffmaan.h"
#include "shennon_fano.h"
#include <iostream>
#include <map>



using namespace std;
auto read_file(std::string_view path) -> std::string {
	constexpr auto read_size = std::size_t(4096);
	auto stream = std::ifstream(path.data());
	stream.exceptions(std::ios_base::badbit);

	auto out = std::string();
	auto buf = std::string(read_size, '\0');
	while (stream.read(&buf[0], read_size)) {
		out.append(buf, 0, stream.gcount());
	}
	out.append(buf, 0, stream.gcount());
	return out;
}

auto string_to_file_bin(string& alla)
{
	string q = alla;
	ofstream ou("o.bin", ios::binary);
	while (q.size() != 0) {
		//if(q.size()<=1000) cout << q.size() << endl;
		unsigned char _byte = 0;
		int len = (q.size() >= 8) ? 8 : q.size();

		for (unsigned long long i = 0; i < len; ++i) {
			if (q[i] == '1') _byte |= 1 << (7 - i);
		}
		ou.write(reinterpret_cast<char*>(&_byte), sizeof(_byte));
		if (q.size() >= 8)
			q.erase(q.begin(), q.begin() + 8);
		else q.erase(q.begin(),q.end());
	}
	ou.close();
}

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
	string ffa = "Перводан, другодан, На колоде барабан;\nСвистель, коростель, Пятерка, шестерка, утюг.";

	//coder_encoder* fac = new coder_encoder(6,a);

	////string aaaa = fac->LZ77_encode(4,a);
	////cout << aaaa<<endl;
	////string bb = fac->LZ77_decode(aaaa);
	////cout << bb;

	////coding_decoding_lz78* b = new coding_decoding_lz78;
	////RLE_coder_decoder d;
	////string f;
	////f = d.RLE_encode(a);
	////cout << f << endl;
	////cout << d.RLE_decode(f);
	//
	////string ssss, sss=a;
	////b->encode_78(sss, ssss);
	////cout << ssss << endl;
	////cout << b->decode_78(ssss) << endl;

	//hoffmaan h;
	////string fa = h.encode_text(a);
	////cout << fa<<endl;
	////string faq = h.decode_text(fa);
	////cout << faq<<endl;


	//shennon_fano* f = new shennon_fano(a);
	//string q = f->encode(a);
	//cout << q<<endl;
	//string ss = f->decode(q);
	//cout << ss<<endl;
	//f->display(f->prpb.size(), f->p);

	string ans, out;
	int sel;

	fstream in("aaa.txt");
	coder_encoder* fac = new coder_encoder(8, a);
	coding_decoding_lz78* b = new coding_decoding_lz78;
	hoffmaan h;
	shennon_fano* f = new shennon_fano(a);
	RLE_coder_decoder d;
	char c;
	cout << ffa.size() << endl;
	while (true)
	{
		cout<<endl <<"Enter num of task" << endl;
		cin >> sel;
		switch (sel)
		{
		case 1:
			cout << "Enter encoding str" << endl;
			cin.get(c);
			getline(cin,ans);
			cout<<d.RLE_encode(ans);
			break;
		case 2:
			cout << "Enter encoding str" << endl;
			cin.get(c);
			getline(cin, ans);
			
			cout << fac->LZ77_encode(8, ans);;
			break;
		case 3:
			cout << "Enter encoding str" << endl;
			cin.get(c);
			getline(cin, ans);
			b->encode_78(ans, out);
			cout << out;
			break;
		case 4:
			cout << "Enter encoding str" << endl;
			//cin.get(c);
			//getline(cin, ans);
			cout << ffa << endl;
			cout << f->encode(ffa);
			break;
		case 5:
			cout << "Enter encoding str" << endl;
			cout << "Reznikov Grigory Anantolievich" << endl;
			ans = "Reznikov Grigory Anantolievich";
			ans = read_file("aaa.txt");
			out= h.encode_text(ans);
			//cout << out << endl;
			cout << out.size();
			string_to_file_bin(out);
			break;
		case 6:
			cout << "Enter decoding str" << endl;
			cin.get(c);
			getline(cin, ans);
			cout << d.RLE_decode(ans);
			break;
		case 7:
			cout << "Enter decoding str" << endl;
			cin.get(c);
			getline(cin, ans);
			cout << fac->LZ77_decode(ans);
			break;
		case 8:
			cout << "Enter decoding str" << endl;
			cin.get(c);
			getline(cin, ans);
			cout << b->decode_78(ans);
			break;
		case 9:
			cout << "Enter decoding str" << endl;
			cin.get(c);
			getline(cin, ans);
			cout << f->decode(ans);
			break;
		case 10:
			cout << "Enter decoding str" << endl;
			cin.get(c);
			getline(cin, ans);
			cout << h.decode_text(ans);
			break;
		}
	}
	
	return 0;

}