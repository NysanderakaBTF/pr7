#include "coding_decoding_lz78.h"
#include <algorithm>
#include <functional>
//#define DEBUG

coding_decoding_lz78::node_encode::node_encode(int a, char c): i{a}, c{c}{}

std::vector<coding_decoding_lz78::node_encode> coding_decoding_lz78::encode_78(std::string& input_str,std::string& out_string)
{
	std::vector<node_encode> ret;

	std::string answer = "";
	std::string prev_substing = "";

	std::vector<std::pair<std::string, int> > codeing_dictionary;


	codeing_dictionary.push_back(std::make_pair("", 0));
	for (auto c : input_str) {
		std::string next = prev_substing + c;
#ifdef DEBUG
		for (auto c : codeing_dictionary) {

			std::cout << c.first << " " << c.second << std::endl;
			
		}
#endif
		std::function<int(std::vector<std::pair<std::string, int> >&, std::string)> find = [&](std::vector<std::pair<std::string, int> >& a, std::string ste)
		{
			for (int i = 0; i < a.size(); ++i)
			{
				if (a[i].first.compare(ste)==0) return  i;
			}
			return -1;
		};
		std::function<int(std::vector<std::pair<std::string, int> >&, std::string)> get = [&](std::vector<std::pair<std::string, int> >& a, std::string ste)
		{
			for (auto sub : a)
				if(ste==sub.first)
					return sub.second;
			return -1;
		};
		if (find(codeing_dictionary, next) == -1) {
			int lplpl=0;
			std::string dafgedrgs;
			lplpl = get(codeing_dictionary,prev_substing);
			node_encode code(lplpl, c);
			ret.push_back(code);
			answer += "<"; answer.push_back(c);answer+="," + std::to_string(lplpl) + ">";
			codeing_dictionary.push_back(std::make_pair(next, (int)codeing_dictionary.size()));

			
			prev_substing = "";
		}
		else {
			prev_substing = next;
		}
	}
	out_string = answer;
	return ret;
}

std::string coding_decoding_lz78::decode_78(std::string& inp)
{
	std::vector<node_encode> input_sequence;
	std::string k = inp;
	while (k.size() != 0)
	{
		int a = k.find_first_of("<");
		int b = k.find_first_of(">");
		std::string m = k.substr(a + 1, b - a - 1);
		k.erase(k.find_first_of("<"), b - a + 1);
		int pos = 0;
		int aa = 0;
		int po = 0;
		char f = m[0];
		m.erase(0, pos + 2);
		while (m[pos] != ',' && pos<m.size())
		{
			if (m[pos] != ',')
			{
				aa += (int(m[pos] - 48)) * pow(10, po++);
			}
			pos++;
		}
		
		

		input_sequence.emplace_back(aa, f);

	}


	std::string resilting_decoded = "";
	std::vector<std::string> sub_dict;
	sub_dict.push_back("");
	for (auto code : input_sequence) {
		std::string sub_str = sub_dict[code.i] + code.c;
		sub_dict.push_back(sub_str);
		resilting_decoded += sub_str;
	}
	return resilting_decoded;
}
