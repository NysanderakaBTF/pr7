#include "coder_encoder.h"

#include <iostream>
#include <vector>
using namespace std;

std::tuple<int, int, char> coder_encoder::find_match(int buffsize,const std::string& a, int pos)
{
	int kon = std::min(pos + buffsize, (int) a.size());
	int p = -1;
	int l = -1;
	char c = ' ';
	auto AMOGUS = [](const std::string& aaaa, int begi, int endi)
	{
		std::string ss = "";
		for (int i = begi; i < endi; ++i)
		{
			ss.push_back(aaaa[i]);
		}
		return ss;
	};
	for (int i = pos+1; i <= kon; ++i)
	{
		int mmmm = std::max(0, pos - window_size_lz77 + 1);
		//std::string ss = a.substr(pos +1, i + 1);
		//std::string ss = AMOGUS(a,pos + 1, i + 1);
		std::string ss = a.substr(pos + 1, (i + 1)-(pos +1));
		for (int j = mmmm; j <= pos; ++j)
		{
			int qqqq = ss.size() / (pos - j + 1);
			int ent = ss.size() % (pos - j + 1);

			std::string mat = ""; 
			for (int k = 0; k < qqqq; ++k)
			{
				//mat += AMOGUS(a,j, pos + 1);
				mat += a.substr(j, pos + 1 - j);
			}

			//mat += AMOGUS(a,j, j + ent);
			mat += a.substr(j, ent);
			std::cout <<qqqq<< "      "<<j << " " << pos << "    " << ent << "    " << mat << "          " << ss << std::endl;

			if (mat==ss && ss.size()>1 )
			{
				p = pos - j + 1;
				l = ss.size();
				c = a[i + 1];
			}
		}
		
	}
	if (p == -1 && l == -1)
	{
		return std::make_tuple(0, 0, a[pos + 1]);
	}else
	{
		return std::make_tuple(p, l, c);
	}
}
coder_encoder::coder_encoder(int a)
{
	window_size_lz77 = a;
}
void coder_encoder::set_window_size(int a)
{
	window_size_lz77 = a;
}
std::string coder_encoder::RLE_encode(const std::string& i)
{
	std::string k;
	int cnt = 1;
	for (int qqq = 0; qqq < i.size(); ++qqq)
	{
		cnt = 1;
		while (qqq < i.size()- 1 && i[qqq] == i[qqq + 1]) {
			cnt++;
			qqq++;
		}
		k.push_back(i[qqq]);
		k+=std::to_string(cnt);
	}
	return std::move(k);
}

std::string coder_encoder::RLE_decode(const std::string& mm)
{
	std::string ss="";
	std::string sub = "";
	int q = 0, f=0;
	for (int i = 0; i < mm.size(); ++i)
	{
		sub = "";
		q = 0; f = 0;
		ss.push_back(mm[i]);
		while (isdigit(mm[++i]))
		{
			q+=char(int(mm[i]) - 48)*pow(10,f++);
		}
		i--;
		for (int j = 0; j <q-1; ++j)
		{
			ss.push_back( ss.at(ss.size()-1));
		}
	}
	return std::move(ss);
}

std::string coder_encoder::LZ77_encode(int buffsize, const std::string& a )
{
	
	std::string res="";
	for(int i=-1; i < (int)a.size()-1;)
	{
		auto re = find_match(buffsize, a, i);
		res += "<" + std::to_string(std::get<0>(re)) + "," + std::to_string(std::get<1>(re)) +","+ std::get<2>(re) + ">";
		
		i += std::get<1>(re) + 1;
	}
	return res;
}

std::string coder_encoder::LZ77_decode(const std::string& ss)
{
	int p = -1;
	std::string res = "";
	vector<tuple<int, int, char>> v;
	string k = ss;
	while (k.size()!=0)
	{
		int a = k.find_first_of("<");
		int b = k.find_first_of(">");
		string m = k.substr(a+1, b - a-1);
		k.erase(k.find_first_of("<"), b-a+1);
		int pos = 0;
		int aa = 0;
		int po = 0;
		while (m[pos]!=',')
		{
			if(m[pos]!=',')
			{
				aa += (int(m[pos] - 48)) * pow(10, po++);
			}
			pos++;
		}
		m.erase(0, pos+1);
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
		m.erase(0, pos+1);
		char f = m[0];

		cout << aa << " " << bb << " " << f << endl;

		if(aa == 0 && bb == 0)
			res.push_back(f);
		else if (aa>=bb)
		{
			for (int i = pos-aa+1; i < pos+1; ++i)
			{
				res.push_back(res[i]);
			}
			
			res.push_back(f);
		}else
		{
			int pov = bb / aa;
			int en = bb % aa;
			string hh = "";
			for (int i = pos - aa + 1; i < pos + 1; ++i)
			{
				hh.push_back(res[i]);
			}
			for (int i = 0; i < pov; ++i)
			{
				res += hh;
			}
			for (int i = pos-aa+1; i <en; ++i)
			{
				res.push_back(res[i]);
			}
			res.push_back(f);
		}
		pos += bb + 1;

	}
	return res;
}
