#include"hufftree.h"
#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
    int* freq = statistics("dream.txt"); //���������ļ���ͳ�Ƹ��ַ��ĳ���Ƶ��
    HuffForest* forest = initForest(freq); release(freq); //����Huffmanɭ��
    HuffTree* tree = generateTree(forest); release(forest); //����Huffman������
    HuffTable* table = generateTable(tree); //��Huffman������ת��Ϊ�����
    char str[30][30] = { "I","have","a","dream","b","c","d","e","f"};
    for (int i = 0; str[i][0] != '\0'; i++)
    {
        Bitmap* codeString = new Bitmap;
        int n = encode(table, codeString, str[i]);
        decode(tree, codeString, n);
        cout << endl;
        release(codeString);
    }
    release(tree); //�ͷű�����
    return 0;
}