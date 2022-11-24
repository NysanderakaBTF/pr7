#pragma once
#include <string>
#include <tuple>
#include <vector>

class coder_encoder
{
	int window_size_lz77;
	std::tuple<int, int, char> find_match(int, const std::string&, int);
public:
	struct code {
		int off;
		int len;
		char nextChar;
		code(int a, int b, char c);
		code();
	};


	std::vector<code> vt;
	coder_encoder(int);
	void set_window_size(int a);
	 std::string RLE_encode(const std::string&);
	 std::string RLE_decode(const std::string&);

	 std::string LZ77_encode(int, const std::string&);
	 std::string LZ77_decode(const std::string&);
};
