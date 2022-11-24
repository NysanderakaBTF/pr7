#include "RLE_coder_decoder.h"


std::string RLE_coder_decoder::RLE_encode(const std::string& i)
{
	std::string k;
	int cnt = 1;
	for (int qqq = 0; qqq < i.size(); ++qqq)
	{
		cnt = 1;
		while (qqq < i.size() - 1 && i[qqq] == i[qqq + 1]) {
			cnt++;
			qqq++;
		}
		k.push_back(i[qqq]);
		k += std::to_string(cnt);
	}
	return std::move(k);
}

std::string RLE_coder_decoder::RLE_decode(const std::string& mm)
{
	std::string ss = "";
	std::string sub = "";
	int q = 0, f = 0;
	for (int i = 0; i < mm.size(); ++i)
	{
		sub = "";
		q = 0; f = 0;
		ss.push_back(mm[i]);
		while (isdigit(mm[++i]))
		{
			q += char(int(mm[i]) - 48) * pow(10, f++);
		}
		i--;
		for (int j = 0; j < q - 1; ++j)
		{
			ss.push_back(ss.at(ss.size() - 1));
		}
	}
	return std::move(ss);
}