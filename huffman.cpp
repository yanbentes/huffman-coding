/* huffman coding */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;
  
/* caracter e codigo huffman associados */
map<char, string> codes;
  
/* frequencia do caracter */
map<char, int> freq;
  
/* Nodo */
struct MinHeapNode {
    
    char data;
    int freq;             
    MinHeapNode *left, *right;
  
    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
  
struct compare {

    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};
  
/* armazenar codigos */
void storeCodes(struct MinHeapNode* root, string str) {
    
    if (root==NULL)
        return;
    if (root->data != EOF)
        codes[root->data]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
  
/* constroi arvore de huffman */
void HuffmanCodes(int size) {

    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++){
        minHeap.push(new MinHeapNode(v->first, v->second));
    }
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode(EOF, left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}
  
/* frequencia de caracteres */
void calcFreq(string str, int n) {

    for (int i=0; i<str.size(); i++) {
        freq[str[i]]++;
    }
}  
  
int main() {
    /* lê arquivo txt */
    string content, fileName;

    cout << "file: ";
    cin >> fileName;

    ifstream file(fileName);
    
    string temp;
    while(getline(file, temp)) {
        content += temp;
    }

    file.close();

    string encodedText;

    calcFreq(content, content.length());
    
    HuffmanCodes(content.length());

    /* printa char frequencia e codigo */
    cout <<"\nchar\tfreq\tcode\n";
    auto f=freq.begin();
    for(auto v=codes.begin(); v!=codes.end(); v++){

        cout << v->first <<"\t"<< f->second <<"\t"<< v->second <<"\n";
        f++;
    }
    
    /* codifica string e printa */
    for(auto i : content){
        encodedText += codes[i];
    }
  
    cout << encodedText << "\n";
  
    return 0;
}
