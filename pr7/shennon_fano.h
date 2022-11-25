#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>

class shennon_fano
{
	
public:
	struct node {
		// for storing symbol
		std::string encoding_symbol;
		// for storing probability or frquency
		double usage_probability;
		int codes_array[20];
		int final_coding_length;
	};
	std::vector<node> p;
	std::map<char, int> o;
	std::map<char, double> prpb;
	std::map<std::string, std::string> dict;

	shennon_fano(std::string&);
	void display(int n, std::vector<node> p);
	// void shennon_generator(int l, int h, coder_encoder::node p[]);
	void shennon_generator(int l, int h, std::vector<node>& p);
	std::string encode(const std::string& text);
	std::string decode(const std::string& text );
};

