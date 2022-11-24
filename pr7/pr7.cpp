#include <algorithm>

#include "coder_encoder77.h"
#include <iostream>
#include <map>


using namespace std;


int main()
{
	string a="aaaabbbbbbbbhbhbhddsl";


	coder_encoder fuck(6,a);



	map<char, int> o;
	for (int i = 0; i < a.size(); ++i)
	{
		if(o.find(a[i])==o.end())
		{
			o.insert(make_pair(a[i], 1));
		}else
		{
			o[a[i]]++;
		}
	}
	map<char, double> prpb;
	for (int i = 0; i < a.size(); ++i)
	{
		if (prpb.find(a[i]) == prpb.end())
		{

			prpb.insert(make_pair(a[i], (count_if(a.begin(),a.end(),[&](char q)
			{
					return q == a[i];
			})/((double)a.size()) )));
		}
	}

	for (auto value : o)
	{
		cout << value.first<<" "<<value.second<<endl;
	}
	for (auto value : prpb)
	{
		cout << value.first << " " << value.second << endl;
	}

	int n, i, j;
	float total = 0;
	string ch;
	coder_encoder::node temp;
	// Input number of symbols
	// Input symbols
	//for (i = 0; i < n; i++) {
	//	cout << "Enter symbol " << i + 1 << " : ";
	//	ch = (char)(65 + i);
	//	cout << ch << endl;
	//	// Insert the symbol to node
	//	fuck.coder_encoder::p[i].sym += ch;
	//}
	int jj = 0;

	for (auto value : o)
	{
		fuck.p[jj++].sym += value.first;
	}
	jj = 0;
	for (auto value : prpb)
	{
		fuck.p[jj++].pro = value.second;
	}




	struct node {
		// for storing symbol
		std::string sym;
		// for storing probability or frquency
		double pro;
		int arr[20];
		int top;
	};

	tuple<string, double, int[20], int> elem;
	std::get<2>(elem)[1] = 7;

	// Input probability of symbols
	//float x[] = { 0.22, 0.28, 0.15, 0.30, 0.05 };
	//for (i = 0; i < n; i++) {
	//	cout << " Enter probability of " << fuck.coder_encoder::p[i].sym << " : ";
	//	cout << x[i] << endl;
	//	// Insert the value to node
	//	fuck.p[i].pro = x[i];
	//	total = total + fuck.p[i].pro;
	//	// checking max probability
	//	if (total > 1) {
	//		cout << "Invalid. Enter new values";
	//		total = total - fuck.p[i].pro;
	//		i--;
	//	}
	//}
	//fuck.p[i].pro = 1 - total;
	// Sorting the symbols based on
	// their probability or frequency
	//fuck.sortByProbability(n, fuck.p);
	n = a.size();
	sort(fuck.p.begin(), fuck.p.end(), [&](coder_encoder::node a, coder_encoder::node b)
		{
			return (a.pro) > (b.pro);
		});


	for (i = 0; i < n; i++)
		fuck.p[i].top = -1;
	// Find the shannon code
	fuck.shannon(0, o.size()-1, fuck.p);
	// Display the codes
	fuck.display(n, fuck.p);
	return 0;

}