#pragma once
#include <string>
#include <tuple>
class coder_encoder
{
	int window_size_lz77;
	std::tuple<int, int, char> find_match(int, const std::string&, int);
public:
	coder_encoder(int);
	void set_window_size(int a);
	 std::string RLE_encode(const std::string&);
	 std::string RLE_decode(const std::string&);

	 std::string LZ77_encode(int, const std::string&);
	 std::string LZ77_decode(const std::string&);
};
