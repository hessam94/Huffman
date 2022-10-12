// HESSAMALDIN MOHAMMADI cs610 3014 prp
#include<string>
#include<iostream>
#include<map>
#include<vector>
using namespace std;
struct PairItem
{
	char mainItem;
	string encodedItem;

};
 extern vector<PairItem> PairItems;
 extern vector<pair<char,string>> EncodedItems;
class HuffmanNode
{
public:
	bool IsHuffmanLeaf= false;
	char Key;
	int Value=0;
	string EnodedValue;
	HuffmanNode *Left,*Right;
	void Traverse(string code)
	{
		PairItem item;
		if (IsHuffmanLeaf == true)
		{
			EncodedItems.push_back(make_pair(Key, code));
			item.encodedItem = code;
			item.mainItem = Key;
			PairItems.push_back(item);
		}
		else
		{
			Left->Traverse( code + '0');
			Right->Traverse(code + '1');
		}
	
	
	}

};


