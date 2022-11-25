#include "tree.h"
#include <vector>
#include <algorithm>
#include <functional>


tree::node::node(char a, string b)
{
    info.first =a ;

    info.second = b;
    left = nullptr;
    right = nullptr;
}

tree::node::~node()
{
    delete left;
    delete right;
}

tree::tree()
{
    root = nullptr;
}

void tree::add_node(char ch, string k)
{
    function<int(string, string)> compare = [](string a, string b)
    {
        int m = min(a.size(), b.size());
        for (int i = 0; i < m; ++i)
        {
            if (a[i] > b[i]) return  1;
        }
        return -1;
    };



    node* cur = root;
    if (cur == nullptr) {
        root = new node(ch, k);
    }
    else {
        while (cur->left != nullptr || cur->right != nullptr)
        {
            if (compare(k, cur->info.second) > 0)
                if (cur->right != nullptr)
                    cur = cur->right;
                else
                    break;
            else
                if (cur->left != nullptr)
                    cur = cur->left;
                else
                    break;
        }
        if (compare(k, cur->info.second) > 0)
            cur->right = new node(ch, k);
        else
            cur->left = new node(ch, k);
    }
}




void tree::print(node* n, string  rpref, string cpref, string lpref)
{
    string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";
    if (!n) return;
    if (n->right)
        print(n->right, rpref + "  ", rpref + ch_ddia_hor, rpref + ch_ver_spa);

    cout << cpref << n->info.second <<" -- " <<n->info.first<< endl;
    if (n->left)
        print(n->left, lpref + ch_ver_spa, lpref + ch_udia_hor, lpref + "  ");
}
