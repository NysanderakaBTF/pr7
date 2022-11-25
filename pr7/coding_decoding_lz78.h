#pragma once
#include <vector>
#include <iostream>
#include "string"
#include "unordered_map"

class coding_decoding_lz78
{
	struct node_encode
	{
		int i;
		char c;
		node_encode(int,char);
	};
public:
	int i;
	char c;
	//coding_decoding_lz78(int i, char c);
	std::vector<node_encode> encode_78(std::string&,std::string&);
	std::string decode_78(std::string&);
};




