#include "shennon_fano.h"
#include "tree.h"
#include <algorithm>
#include <numeric>


#define	DEBUG

shennon_fano::shennon_fano(std::string& text)
{
	p.resize(text.size());
}


void shennon_fano::display(int n, std::vector<node> p)
{
	tree t;
	string kal = "";
	for (int i = 0; i < n-1; ++i)
	{
		kal = "";
		for (int j = 0; j <= p[i].final_coding_length; ++j)
		{
			kal.push_back(static_cast<char>(p[i].codes_array[j] + 48));
		}
		t.add_node(p[i].encoding_symbol[0], kal);
	}
	t.print(t.root);
}



void shennon_fano::shennon_generator(int l, int h, std::vector<node>& p)
{
	float first_prob = 0, secondpopo = 0, d1 = 0, d2 = 0;
	int i, d, k, j;
	if ((l + 1) == h || l == h || l > h) {
		if (l == h || l > h)
			return;
		p[h].codes_array[++(p[h].final_coding_length)] = 0;
		p[l].codes_array[++(p[l].final_coding_length)] = 1;
		return;
	}
	else {
		for (i = l; i <= h - 1; i++)
			first_prob = first_prob + p[i].usage_probability;
			secondpopo = secondpopo + p[h].usage_probability;
		d1 = first_prob - secondpopo;
		if (d1 < 0)
			d1 = d1 * -1;
		j = 2;
		while (j != h - l + 1) {
			k = h - j;
			first_prob = secondpopo = 0;

			for (i = l; i <= k; i++)
				first_prob = first_prob + p[i].usage_probability;
			for (i = h; i > k; i--)
				secondpopo = secondpopo + p[i].usage_probability;
			d2 = first_prob - secondpopo;
			if (d2 < 0)
				d2 = d2 * -1;
			if (d2 >= d1)
				break;
			d1 = d2;
			j++;
		}
		k++;
		for (i = l; i <= k; i++)
			p[i].codes_array[++(p[i].final_coding_length)] = 1;
		for (i = k + 1; i <= h; i++)
			p[i].codes_array[++(p[i].final_coding_length)] = 0;
		shennon_generator(l, k, p);
		shennon_generator(k + 1, h, p);
	}
}

std::string shennon_fano::encode(const std::string& a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		if (o.find(a[i]) == o.end())
		{
			o.insert(std::make_pair(a[i], 1));
		}
		else
		{
			o[a[i]]++;
		}
	}

	for (int i = 0; i < a.size(); ++i)
	{
		if (prpb.find(a[i]) == prpb.end())
		{
			prpb.insert(std::make_pair(a[i], (count_if(a.begin(), a.end(), [&](char q){return q == a[i];}) / ((double)a.size()))));
		}
	}
	#ifdef DEBUG

		for (auto value : o)
			std::cout << value.first << " " << value.second << std::endl;
		for (auto value : prpb)
			std::cout << value.first << " " << value.second << std::endl;

	#endif

	node temp;
	int jj = 0;

	vector<pair<char, double>> aaaaaa;
	aaaaaa.resize(o.size());


	for (auto value : o)
		aaaaaa[jj++].first = value.first;
	jj = 0;
	for (auto value : prpb)
		aaaaaa[jj++].second = value.second;



	auto u = [&](char a, double b)
	{
		node *q = new node;
		q->encoding_symbol = a;
		q->usage_probability = b;
		return q;
	};
	for (int i = 0; i < aaaaaa.size(); ++i)
	{
		p.push_back(*u(aaaaaa[i].first,aaaaaa[i].second));
	}

	sort(p.begin(), p.end(), [&](node a, node b){return (a.usage_probability) > (b.usage_probability);});

	for (int i = 0; i < p.size(); i++)
		p[i].final_coding_length = -1;

	shennon_generator(0, o.size() - 1, p);
	std::string generated_sequence = "";

	for (int i = o.size() - 1; i >= 0; i--) {
		generated_sequence.clear();
		for (int j = 0; j <= p[i].final_coding_length; j++)
			generated_sequence.push_back(static_cast<char>(p[i].codes_array[j] + 48));
		dict.emplace(generated_sequence, p[i].encoding_symbol);
	}
	for (auto value : dict)
	{
		cout << value.first<<"     "<< o[value.first[0]] << " -----> " << value.second << endl;
	}
	generated_sequence.clear();
	for (char a1 : a)
	{
		for (auto re : dict)
		{
			if(re.second[0]==a1)
			{
				generated_sequence += re.first;
				break;
			}
		}
	}
	return generated_sequence;
}

std::string shennon_fano::decode(const std::string& text)
{
	int l = 0, count = 1;
	std::string buffer = "";
	std::string deocded_text = "";
	do
	{
		buffer = text.substr(l, count);
		if(dict.find(buffer)!=dict.end())
		{
			deocded_text += dict[buffer];
			l += count;
			count = 1;
		}else
		{
			count++;
		}
	} while (l + count != text.size()+1);
	return deocded_text;
}
