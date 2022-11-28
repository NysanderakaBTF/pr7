#include "hoffmaan.h"

//#define DEBUG

hoffmaan::tree_node::tree_node(char ch, int freq, std::shared_ptr<tree_node> left, std::shared_ptr<tree_node> right)
{
	this->coding_symbol = ch;
	this->freq = freq;
	if (left != nullptr)
		this->left_node = std::make_shared<tree_node>(*left);
	if (left != nullptr)
		this->right_node = std::make_shared<tree_node>(*right);
}

hoffmaan::tree_node::tree_node()
{
}

void hoffmaan::encode(const std::shared_ptr<tree_node> root, std::string str, std::unordered_map<char, std::string>& codes_pairs)
{
	if (root == nullptr) {
		return;
	}
	if (root->left_node == nullptr && root->right_node == nullptr) {
		codes_pairs[root->coding_symbol] = (str.size() != 0) ? str : "1";
	}
	encode(root->left_node, str + "0", codes_pairs);
	encode(root->right_node, str + "1", codes_pairs);
}

void hoffmaan::decode(std::shared_ptr<tree_node> root, int& position, std::string& str, std::string& res)
{
	if (root == nullptr)
		return;
	if (root->left_node == nullptr && root->right_node == nullptr){
		res.push_back(root->coding_symbol); return;
	}
	position++;
	if (str[position] == '0') {
		decode(root->left_node, position, str,res);
	}
	else {
		decode(root->right_node, position, str,res);
	}
}

std::string hoffmaan::encode_text(std::string& text)
{
	cout << text.size() << endl;
	if (text == "") {
		return "";
	}
	std::unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}
#ifdef ANALIS
	for (auto value : freq)
	{
		double lol = (double)value.second / (double)text.size();
		cout << "Symbol: " << value.first << " count: " << value.second << " propability: " << lol << endl;
	}
#endif

	for (auto pair : freq) {
		pq.push(std::make_shared<tree_node>(*new tree_node(pair.first, pair.second, nullptr, nullptr)));
	}
	while (pq.size() != 1)
	{
		std::shared_ptr<tree_node> left = pq.top();
		pq.pop();
		std::shared_ptr<tree_node> right = pq.top();
		pq.pop();
		int sum = left->freq + right->freq;
		pq.push(std::make_shared<tree_node>(*new tree_node('\0', sum, left, right)));
	}

	std::shared_ptr<tree_node> root = pq.top();
	function<void(tree_node*, string, string, string, string)> ptint = [&](tree_node* n, string  rpref, string cpref, string lpref, string code)
	{
		string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";
		if (!n) return;
		if (n->right_node)
			ptint(n->right_node.get(), rpref + "  ", rpref + ch_ddia_hor, rpref + ch_ver_spa, code + "1");
		if (generated_code_pairs[n->coding_symbol] != "")
			cout << cpref << generated_code_pairs[n->coding_symbol] << " -- " << n->coding_symbol << endl;
		else cout << cpref << code << endl;
		//else cout << cpref << generated_code_pairs[n->coding_symbol] << endl;
		if (n->left_node)
			ptint(n->left_node.get(), lpref + ch_ver_spa, lpref + ch_udia_hor, lpref + "  ", code + "0");
	};
	encode(root, "", generated_code_pairs);
	std::string str;
	std::string alla;
	int sum_lrn = 0;
	double fffff = 0;
	for (auto value : generated_code_pairs)
	{
		sum_lrn += value.second.size();
		cout << value.first << " " << value.second << endl;
	}
	int kol = generated_code_pairs.size();
	for (char ch : text)
	{
		str += generated_code_pairs[ch] + "|";
		fffff += generated_code_pairs[ch].size();
		for (int jj = 0; jj < generated_code_pairs[ch].size() - 1; ++jj)
		{
			alla += " ";
		}
		alla.push_back(ch); alla += "|";
	}
	//alla = str + "\n" + alla;
#ifdef ANALIS
	str += "\n" + alla;
	cout << sum_lrn << "/" <<  kol << "=" << (double)sum_lrn / (double)kol << endl;
	cout << fffff << endl << text.size() << endl << fffff/double(text.size() * 8)  << endl;
#endif

	cout << "Builded tree of codes" << endl;

	ptint(root.get(), "","","","");




	return str;
}

bool hoffmaan::tree_node::operator()(const std::shared_ptr<tree_node> l, const std::shared_ptr<tree_node> r) const
{
	return l->freq > r->freq;
}


std::string hoffmaan::decode_text(std::string& text)
{
	std::shared_ptr<tree_node> root = pq.top();
	std::string resurl="";
	if (root->left_node == nullptr && root->right_node == nullptr)
	{
		while (root->freq--) {
			resurl.push_back(root->coding_symbol);
		}
	}
	else {
		int position = -1;
		while (position < (int)text.size() - 1) {
			decode(root, position, text, resurl);
		}
	}
	return resurl;
}

void hoffmaan::display_tree_of_codes()
{
	tree t;
	for (auto element : generated_code_pairs)
	{
		t.add_node(element.first, element.second);
		std::cout << element.first << " " << element.second << std::endl;
	}

	cout << "\n\n\n\n";
	t.print(t.root);
}