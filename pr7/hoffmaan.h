#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <queue>

class hoffmaan
{
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

// ������� ��� ��������� ������ ���� ������
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// ������ ���������, ������� ����� �������������� ��� �������������� ����
struct comp
{
	bool operator()(const Node* l, const Node* r) const
	{
		// ������� � ��������� ����������� ����� ���������� �������
		return l->freq > r->freq;
	}
};

// ��������������� ������� ��� ��������, �������� �� ������ �������� ������ ���� ����
bool isLeaf(Node* root) {
	return root->left == nullptr && root->right == nullptr;
}

// �������� �� ������ �������� � ��������� ���� �������� �� �����.
void encode(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode)
{
	if (root == nullptr) {
		return;
	}

	// ������ �������� ����
	if (isLeaf(root)) {
		huffmanCode[root->ch] = (str.size()==0) ? str : "1";
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// �������� �� ������ �������� � ���������� �������������� ������
void decode(Node* root, int &index, std::string str)
{
	if (root == nullptr) {
		return;
	}

	// ������ �������� ����
	if (isLeaf(root))
	{
		std::cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0') {
		decode(root->left, index, str);
	}
	else {
		decode(root->right, index, str);
	}
}

// ������ ������ �������� � ���������� �������� ������� �����
void buildHuffmanTree(std::string text)
{
	// ������� ������: ������ ������
	if (text == "") {
		return;
	}

	// ������������ ������� ��������� ������� �������
	// � ��������� ��� �� �����
	std::unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// ������� ������������ ������� ��� �������� �������� ����� ������ ��������
	std::priority_queue<Node*, std::vector<Node*>, comp> pq;

	// ������� �������� ���� ��� ������� ������� � ��������� ���
	// � ������������ �������.
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// ������ �� ��� ���, ���� � queue �� �������� ����� ������ ����
	while (pq.size() != 1)
	{
		// ������� ��� ���� � ��������� �����������
		// (����� ������ �������) �� queue

		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();    pq.pop();

		// ������� ����� ���������� ���� � ����� ����� ������ � �������� �������� �
		// � ��������, ������ ����� ������ ���� �����.
		// ��������� ����� ���� � ������������ �������.

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// `root` ������ ��������� �� ������ ������ ��������
	Node* root = pq.top();

	// �������� �� ������ �������� � ��������� ���� ��������
	// �� �����. ����� ����, ������������ ��
	std::unordered_map<char, std::string> huffmanCode;
	encode(root, "", huffmanCode);

	std::cout << "Huffman Codes are:\n" << std::endl;
	for (auto pair: huffmanCode) {
		std::cout << pair.first << " " << pair.second << std::endl;
	}

	std::cout << "\nThe original string is:\n" << text << std::endl;

	// �������� �������������� ������
	std::string str;
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	std::cout << "\nThe encoded string is:\n" << str << std::endl;
	std::cout << "\nThe decoded string is:\n";

	if (isLeaf(root))
	{
		// ������ ������: ��� ����� ���� a, aa, aaa � �. �.
		while (root->freq--) {
			std::cout << root->ch;
		}
	}
	else {
		// ����� �������� �� ������ �������� � �� ���� ���
		// ���������� �������������� ������
		int index = -1;
		while (index < (int)str.size() - 1) {
			decode(root, index, str);
		}
	}
}

};

