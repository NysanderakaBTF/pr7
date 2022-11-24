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

	struct node {
		// for storing symbol
		std::string sym;
		// for storing probability or frquency
		double pro;
		int arr[20];
		int top;
	};
	

	struct code {
		int off;
		int len;
		char nextChar;
		code(int a, int b, char c);
		code();
	};

	std::vector<node> p;
	std::vector<code> vt;
	coder_encoder(int, std::string);
	void set_window_size(int a);
	 std::string RLE_encode(const std::string&);
	 std::string RLE_decode(const std::string&);

	 std::string LZ77_encode(int, const std::string&);
	 std::string LZ77_decode(const std::string&);
	 void display(int n, std::vector<coder_encoder::node> p);
	// void shannon(int l, int h, coder_encoder::node p[]);
	 void shannon(int l, int h, std::vector<coder_encoder::node>& p);
};
