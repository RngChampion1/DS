#include"hufftree.h"
#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
    int* freq = statistics("dream.txt"); //根据样本文件，统计各字符的出现频率
    HuffForest* forest = initForest(freq); release(freq); //创建Huffman森林
    HuffTree* tree = generateTree(forest); release(forest); //生成Huffman编码树
    HuffTable* table = generateTable(tree); //将Huffman编码树转换为编码表
    char str[30][30] = { "I","have","a","dream","b","c","d","e","f"};
    for (int i = 0; str[i][0] != '\0'; i++)
    {
        Bitmap* codeString = new Bitmap;
        int n = encode(table, codeString, str[i]);
        decode(tree, codeString, n);
        cout << endl;
        release(codeString);
    }
    release(tree); //释放编码树
    return 0;
}