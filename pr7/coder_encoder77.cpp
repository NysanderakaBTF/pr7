#include "coder_encoder77.h"
using namespace std;
#define maxWindow 4
coder_encoder::coder_encoder(int a, string f)
{
	coding_size = f.size();
	p.resize(f.size());
	window_size_lz77 = a;
}
void coder_encoder::set_window_size(int a)
{
	window_size_lz77 = a;
}


std::string coder_encoder::LZ77_encode(int buffsize, const std::string& a )
{
	string str = a;
	cout << str << endl;
	int window1, window2;
	for (int i = 0; i < str.length(); i++) {
		if (i + 1 <= maxWindow) window1 = i;
		else window1 = maxWindow;

		if (i + window1 < str.length()) window2 = window1;
		else window2 = str.length() - i;

		//printf("%d %d %d\n", window1, window2, i);
		string str1 = str.substr(i - window1, window1);
		string str2 = str.substr(i, window2);
		//cout << str1 << " : " << str2 << endl;

		int off = -1;
		while (true) {
			if (window2 == 0) break; // Пустая строка, прямой выход 
			string str3 = str2.substr(0, window2);
			off = str1.find(str3); // Не найдено, выкл. = -1 
			//cout << str3 << " :: " << off << " :: " << i + window2 << endl;
			if (off != -1) break; // Нашли, выходим 
			window2--;
			if (window2 <= 0) break;
		}

		if (off != -1) {
			coder_encoder::code cd;
			cd.len = window2;
			cd.off = window1 - off;
			cd.nextChar = str[i + window2];
			vt.push_back(cd);
			i += window2;
		}
		else {
			coder_encoder::code cd;
			cd.len = 0;
			cd.off = 0;
			cd.nextChar = str[i + window2];
			vt.push_back(cd);
		}
	}

	string res = "";
	for(auto i : vt)
	{
		res += "<" + to_string(i.off) + "," + to_string(i.len) + "," + i.nextChar + ">";
	}
	return res;
}

std::string coder_encoder::LZ77_decode(const std::string& ss)
{

	vector<code> v;
	string k = ss;
	while (k.size() != 0)
	{
		int a = k.find_first_of("<");
		int b = k.find_first_of(">");
		string m = k.substr(a + 1, b - a - 1);
		k.erase(k.find_first_of("<"), b - a + 1);
		int pos = 0;
		int aa = 0;
		int po = 0;
		while (m[pos] != ',')
		{
			if (m[pos] != ',')
			{
				aa += (int(m[pos] - 48)) * pow(10, po++);
			}
			pos++;
		}
		m.erase(0, pos + 1);
		po = 0;
		int bb = 0;
		pos = 0;
		while (m[pos] != ',')
		{
			if (m[pos] != ',')
			{
				bb += (int(m[pos] - 48)) * pow(10, po++);
			}
			pos++;
		}
		m.erase(0, pos + 1);
		char f = m[0];

		v.emplace_back(aa, bb, f);

	}




	string strOut;
	for (int i = 0; i < vt.size(); i++) {
		if (vt[i].len == 0) {
			strOut += v[i].nextChar;
		}
		else {
			int len = strOut.length();
			len -= v[i].off;
			string temp = strOut.substr(len, v[i].len);
			strOut += temp + v[i].nextChar;
		}
	}
	return strOut;

}

void coder_encoder::shannon(int l, int h, std::vector<coder_encoder::node>& p)
{
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
	int i, d, k, j;
	if ((l + 1) == h || l == h || l > h) {
		if (l == h || l > h)
			return;
		//p[h].arr[++(*p[h].top)] = 0;
		p[h].arr[++(p[h].top)] = 0;
		p[l].arr[++(p[l].top)] = 1;
		return;
	}
	else {
		for (i = l; i <= h - 1; i++)
			pack1 = pack1 + p[i].pro;
		pack2 = pack2 + p[h].pro;
		diff1 = pack1 - pack2;
		if (diff1 < 0)
			diff1 = diff1 * -1;
		j = 2;
		while (j != h - l + 1) {
			k = h - j;
			pack1 = pack2 = 0;
			for (i = l; i <= k; i++)
				pack1 = pack1 + p[i].pro;
			for (i = h; i > k; i--)
				pack2 = pack2 + p[i].pro;
			diff2 = pack1 - pack2;
			if (diff2 < 0)
				diff2 = diff2 * -1;
			if (diff2 >= diff1)
				break;
			diff1 = diff2;
			j++;
		}
		k++;
		for (i = l; i <= k; i++)
			p[i].arr[++(p[i].top)] = 1;
		for (i = k + 1; i <= h; i++)
			p[i].arr[++(p[i].top)] = 0;
		// Invoke shannon function
		shannon(l, k, p);
		shannon(k + 1, h, p);
	}
}

coder_encoder::code::code(int a, int b, char c)
{
	off = a;
	len = b;
	nextChar = c;
}

coder_encoder::code::code()
{
	off = 0;
	len = 0;
	nextChar = ' ';
}

void coder_encoder::display(int n, std::vector<coder_encoder::node> p)
{
	int i, j;
	cout << " Symbol Probability Code";
	for (i = n - 1; i >= 0; i--) {
		cout << " " << p[i].sym << " " << p[i].pro << " ";
		for (j = 0; j <= p[i].top; j++)
			cout << p[i].arr[j];
		cout << endl;
	}
}
