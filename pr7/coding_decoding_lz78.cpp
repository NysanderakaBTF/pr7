#include "coding_decoding_lz78.h"
//#define DEBUG

coding_decoding_lz78::node_encode::node_encode(int a, char c): i{a}, c{c}{}

std::vector<coding_decoding_lz78::node_encode> coding_decoding_lz78::encode_78(std::string& input_str,std::string& out_string)
{
	std::vector<node_encode> ret;
	std::string answer = "";
	std::string prev_substing = "";
	std::unordered_map<std::string, int> codeing_dictionary;
	codeing_dictionary.insert(std::make_pair("", 0));
	for (auto c : input_str) {
		std::string next_sub = prev_substing + c;
		for (auto c : codeing_dictionary) {
#ifdef DEBUG
			std::cout << c.first << " " << c.second << std::endl;
#endif
			
		}
		if (codeing_dictionary.find(next_sub) == codeing_dictionary.end()) {
			int i = codeing_dictionary[prev_substing];
			node_encode code(i, c);
			ret.push_back(code);
			answer += "<"; answer.push_back(c);answer+="," + std::to_string(i) + ">";
			codeing_dictionary[next_sub] = codeing_dictionary.size();
			prev_substing = "";
		}
		else {
			prev_substing = next_sub;
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
