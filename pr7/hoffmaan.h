#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <memory>
#include "tree.h"
class hoffmaan
{
public:
	struct tree_node
	{
		char coding_symbol;
		int freq;
		std::shared_ptr<tree_node> left_node, right_node;
		bool operator()(const std::shared_ptr<tree_node> l, const std::shared_ptr<tree_node> r) const;
		tree_node(char ch, int freq, std::shared_ptr<tree_node> left, std::shared_ptr<tree_node> right);
		tree_node();
	};
	std::unordered_map<char, std::string> generated_code_pairs;
	std::priority_queue<std::shared_ptr<tree_node>, std::vector<std::shared_ptr<tree_node>>, tree_node> pq;
	void encode(const std::shared_ptr<tree_node> root, std::string str, std::unordered_map<char, std::string>& codes_pairs);
	void decode(std::shared_ptr<tree_node> root, int& position, std::string& str, std::string& res);
	std::string encode_text(std::string& text);
	std::string decode_text(std::string& text);
	void display_tree_of_codes();


};

