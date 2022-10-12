// HESSAMALDIN MOHAMMADI cs610 3014 prp
#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#include<array>
#include <fstream>
#include "Node.cpp"
using namespace std;

vector<HuffmanNode>   v;
vector<string> EncodedData;
vector<PairItem> PairItems;
vector<pair<char, string>> EncodedItems;
int heapsize;
void MinHeapify(int node);
void BuildMinHeap();
void InsertNode(HuffmanNode node);
void Encode();
void Decode();
char FindMainData(string encoded);
string FindEnodedData(char ch);
string filename;
void ReadFile();

vector<unsigned> InputData;
vector<char> InputData2;
int CharCounts[256];
int main()
{

	for (int i = 0; i < 256; i++)
	{
		CharCounts[i] = 0;
	}

	ReadFile();

	HuffmanNode obj;
	obj.IsHuffmanLeaf = true;

	for (int i = 0; i < 128; i++)
	{
		obj.Key = i;
		obj.Value = CharCounts[i];
		v.push_back(obj);
	}
	for (int i = 128; i < 256; i++)
	{
		obj.Key = i - 256;
		obj.Value = CharCounts[i];
		v.push_back(obj);
	}
	int hh = 0;

	int leafstartpoint = floor((v.size() - 1) / 2);//heap array starts form 0 !!

	BuildMinHeap();

	while (v.size() > 1)
	{
		HuffmanNode a, b, newNode;
		newNode.IsHuffmanLeaf = false;
		a = v[0];
		swap(v[0], v.back());
		v.pop_back();
		MinHeapify(0);

		b = v[0];
		swap(v[0], v.back());
		v.pop_back();
		MinHeapify(0);

		if (a.Value <= b.Value)
		{
			newNode.Left = new HuffmanNode(a);
			newNode.Right = new HuffmanNode(b);
		}
		else
		{
			newNode.Left = new HuffmanNode(b);
			newNode.Right = new HuffmanNode(a);
		}
		newNode.Value = a.Value + b.Value;
		InsertNode(newNode);
	}

	v[0].Traverse("");
	Encode();
	Decode();
	return 0;
}

void ReadFile()
{
	FILE *fp;
	int x = 0;
	cout << "please enter your file name (e.g. a.pdf): ";
	cin >> filename;
	cout << "please wait....\n";
	//filename = "a.pdf";
	fp=fopen(filename.c_str(), "rb");
	//fp = fopen("a.pdf", "rb");
	unsigned char buf[1];
	size_t size;
	while ((size = fread(buf, 1, sizeof(buf), fp)) > 0)
	{
		InputData.push_back(buf[0]);
		CharCounts[(buf[0] + 256) % 256]++;
	}
	fclose(fp);
}

void BuildMinHeap()
{
	int LastParent = floor((v.size() - 1) / 2) - 1;

	for (int i = LastParent; i >= 0; i--)
	{
		MinHeapify(i); // because started from 0
	}
}

void MinHeapify(int node)
{
	int TempMin = node;
	int left = 2 * node + 1;
	int right = 2 * node + 2;
	int t = v.size() - 1;
	if (left < v.size() && (v[node].Value > v[left].Value)) // right
		TempMin = left;

	if (right < v.size() && v[TempMin].Value > v[right].Value) // left
	{
		TempMin = right;
	}
	if (TempMin != node)
	{
		swap(v[TempMin], v[node]);
		MinHeapify(TempMin);
	}
}

void InsertNode(HuffmanNode node)
{

	v.push_back(node);
	if (v.size() > 1)
	{
		int parentIndex = (v.size() - 1 - 1) / 2;// 1 minus because the array size is one mode than the index
		int tempindex = v.size() - 1;									     // 1 minus for because we started from 0
		while (parentIndex > 0)
		{
			if (v[tempindex].Value > v[parentIndex].Value)
				swap(v[tempindex], v[parentIndex]);
			else
				break;
			tempindex = parentIndex;
			parentIndex = (parentIndex - 1) / 2;
		}


	}



}

void Encode()
{
	for (int i = 0; i <InputData.size() ; i++)
	{
		string s = FindEnodedData(InputData[i]);
		EncodedData.push_back(s);
	}

	FILE* fw;
	string outputFilename = "Huffman_.huf" ;
	fw = freopen(outputFilename.c_str(), "wb", stdout);

	for (int i = 0; i < EncodedData.size(); i++)
	{
		string t = EncodedData[i];
		fwrite(&t, t.size(), 1, fw);
	}
	fclose(stdout);

}

void Decode()
{
	FILE* fw;
	string outputFilename = "Decoded_" + filename;
	fw=freopen(outputFilename.c_str(), "wb", stdout);
	//fw = freopen("out_a.pdf", "wb", stdout);

	for (int i = 0; i < EncodedData.size(); i++)
	{
		unsigned char t = FindMainData(EncodedData[i]);
		fwrite(&t, 1, 1, fw);
	}
	fclose(stdout);
}

char FindMainData(string encoded)
{
	//for (int i = 0; i < PairItems.size(); i++)
	//	if (PairItems[i].encodedItem == encoded)
	//		return PairItems[i].mainItem;
	for (int i = 0; i < EncodedItems.size(); i++)
		if (EncodedItems[i].second == encoded)
			return EncodedItems[i].first;
}
string FindEnodedData(char ch)
{
	for (int i = 0; i < EncodedItems.size(); i++)
		if (EncodedItems[i].first == ch)
			return EncodedItems[i].second;
}