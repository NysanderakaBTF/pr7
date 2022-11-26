#include "coder_encoder77.h"
using namespace std;
coder_encoder::coder_encoder(int a, string f)
{
	coding_size = f.size();
	coding_size = f.size();
	window_size_lz77 = a;
}
void coder_encoder::set_window_size(int a)
{
	window_size_lz77 = a;
}


std::string coder_encoder::LZ77_encode(int buffsize, const std::string& a )
{
	string input_text_string = a;
	cout << input_text_string << endl;
	int checking_interval1, checking_interval2;
	for (int i = 0; i < input_text_string.length(); i++) {

		checking_interval1 = (i + 1 <= window_size_lz77) ? i : window_size_lz77;
		checking_interval2 = (i + checking_interval1 < input_text_string.length()) ? checking_interval1 : input_text_string.length() - i;

		string substring1 = "";
		for (int j = 0; j < checking_interval1; ++j)
			substring1.push_back(input_text_string[i-checking_interval1+ j]);
		string substring2 = "";
		for (int j = 0; j < checking_interval2; ++j)
			substring2.push_back(input_text_string[i+ j]);

		int offset_value = -1;

		while (checking_interval2 != 0  and !(offset_value != -1) and checking_interval2 >= 0) {
			string str3 = "";
			for (int j = 0; j < checking_interval2; ++j)
				str3.push_back(substring2[j]);
			offset_value = substring1.find(str3); 
			checking_interval2--;
		}

		if (offset_value != -1) {
			coder_encoder::coding_element_code cd;
			cd.replacement_length = checking_interval2;
			cd.offet_value = checking_interval1 - offset_value;
			cd.nextChar = input_text_string[i + checking_interval2];
			result_codes_dict.push_back(cd);
			i += checking_interval2;
		}
		else {
			coder_encoder::coding_element_code cd;
			cd.replacement_length = 0;
			cd.offet_value = 0;
			cd.nextChar = input_text_string[i + checking_interval2];
			result_codes_dict.push_back(cd);
		}
	}

	string res = "";
	for(auto i : result_codes_dict)
	{
		res += "<" + to_string(i.offet_value) + "," + to_string(i.replacement_length) + "," + i.nextChar + ">";
	}
	return res;
}

std::string coder_encoder::LZ77_decode(const std::string& ss)
{
	vector<coding_element_code> element_codes;
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

		element_codes.emplace_back(aa, bb, f);

	}

	string result;
	for (int i = 0; i < result_codes_dict.size(); i++) {
		if (result_codes_dict[i].replacement_length == 0) {
			result += element_codes[i].nextChar;
		}
		else {
			int len = result.length();
			len -= element_codes[i].offet_value;
			string temp = "";
			for (int jj = len; jj < element_codes[i].replacement_length+len; ++jj)
			{
				temp.push_back(result[jj]);
			}
			result += temp + element_codes[i].nextChar;
		}
	}
	return result;

}



coder_encoder::coding_element_code::coding_element_code(int a, int b, char c)
{
	offet_value = a;
	replacement_length = b;
	nextChar = c;
}

coder_encoder::coding_element_code::coding_element_code()
{
	offet_value = 0;
	replacement_length = 0;
	nextChar = ' ';
}

