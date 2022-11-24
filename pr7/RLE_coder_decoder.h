#pragma once
#include <string>
class RLE_coder_decoder
{
public:
	std::string RLE_encode(const std::string&);
	std::string RLE_decode(const std::string&);
};

