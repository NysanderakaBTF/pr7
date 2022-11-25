#pragma once
#include <string>
#include <tuple>

#include <iostream>
#include <vector>
class coder_encoder
{
	int window_size_lz77;
	int coding_size;
public:

	struct coding_element_code {
		int offet_value;
		int replacement_length;
		char nextChar;
		coding_element_code(int a, int b, char c);
		coding_element_code();
	};
	std::vector<coding_element_code> result_codes_dict;
	coder_encoder(int, std::string);
	void set_window_size(int a);
	 std::string LZ77_encode(int, const std::string&);
	 std::string LZ77_decode(const std::string&);

};
