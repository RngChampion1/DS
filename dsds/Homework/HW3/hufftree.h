#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <memory.h>
#include<cstdlib>
#include <cstring>
#include"../../BinTree/BinTree.h"
#define N_CHAR (0x80 - 0x20)//���Կɴ�ӡ�ַ�Ϊ��

struct HuffChar//Huffman�ַ�
{
    char ch; unsigned int weight; //�ַ���Ƶ��
    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {};
    // �Ƚ������е���
    bool operator< (HuffChar const& hc) { return weight > hc.weight; } //Ƶ��Խ�󣬻���������ֵԽС
    bool operator<= (HuffChar const& hc) { return weight >= hc.weight; }
    bool operator> (HuffChar const& hc) { return weight < hc.weight; }
    bool operator>= (HuffChar const& hc) { return weight <= hc.weight; }
    bool operator== (HuffChar const& hc) { return weight == hc.weight; }
    bool operator!= (HuffChar const& hc) { return weight != hc.weight; }
};

class Bitmap//λͼBitmap�� 
{
private:
    unsigned char* M;
    Rank N, _sz; //λͼ�ռ�M[]��N*sizeof(char)*8�������к�_sz����Чλ
protected:
    void init(Rank n)
    {
        M = new unsigned char[N = (n + 7) / 8]; memset(M, 0, N); _sz = 0;
    }
public:
    Bitmap(Rank n = 8) { init(n); } //��ָ����������λͼ
    Bitmap(char* file, Rank n = 8)//��ָ����Ĭ�Ϲ�ģ����ָ���ļ��ж�ȡλͼ
    {
        init(n);
        FILE* fp = fopen(file, "r");
        fread(M, sizeof(char), N, fp);
        fclose(fp);
        for (Rank k = 0, _sz = 0; k < n; k++) _sz += test(k);
    }
    ~Bitmap() { delete[] M; M = NULL; _sz = 0; } //����ʱ�ͷ�λͼ�ռ�

    Rank size() { return _sz; }
    void set(Rank k) { expand(k); _sz++; M[k >> 3] |= (0x80 >> (k & 0x07)); }
    void clear(Rank k) { expand(k); _sz--; M[k >> 3] &= ~(0x80 >> (k & 0x07)); }
    bool test(Rank k) { expand(k); return M[k >> 3] & (0x80 >> (k & 0x07)); }

    void dump(char* file) //��λͼ���嵼����ָ�����ļ����Ա�Դ˺����λͼ������ʼ��
    {
        FILE* fp = fopen(file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }
    char* bits2string(Rank n) //��ǰnλת��Ϊ�ַ�������
    {
        expand(n - 1); //��ʱ���ܱ����ʵ����λΪbitmap[n - 1]
        char* s = new char[n + 1]; s[n] = '\0'; //�ַ�����ռ�ռ䣬���ϲ�����߸����ͷ�
        for (Rank i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
        return s; //�����ַ���λ��
    }
    void expand(Rank k)//�������ʵ�Bitmap[k]�ѳ��磬��������
    {
        if (k < 8 * N) return; //���ڽ��ڣ���������
        Rank oldN = N; unsigned char* oldM = M;
        init(2 * k); //���������ƣ��ӱ�����
        memcpy_s(M, N, oldM, oldN);
        delete[] oldM; //ԭ����ת�����¿ռ�
    }
};

class HuffTable//Huffman�����
{
public:
    HuffTable() {};
    HuffTable(char, char*);
    ~HuffTable();
    bool put(char, char*);
    char** get(char k);
private:
    Vector<char> key;
    Vector<char*> value;
};
HuffTable::HuffTable(char k, char* v)
{
    key.insert(k);
    value.insert(v);
}
HuffTable::~HuffTable()
{
    key.~Vector();
    value.~Vector();
}
inline bool HuffTable::put(char k, char* v)
{
    if (key.find(k) != -1)
    {
        return false;
    }
    key.insert(k);
    value.insert(v);
    return true;
}
inline char** HuffTable::get(char k)
{
    Rank r = key.find(k);
    if (r == -1)
    {
        return nullptr;
    }
    else
    {
        return &value[r];
    }
}


int* statistics(const char* sample_text_file)//ͳ���ַ�����Ƶ�� 
{
    FILE* fp;
    if (fopen_s(&fp, sample_text_file, "r") != 0) {
        std::cerr << "Error: cannot open file \"" << sample_text_file << "\"." << std::endl;
        return nullptr;
    }

    int* freq = new int[N_CHAR]();  //��ʼ��Ϊ 0
    char ch;
    while (fscanf_s(fp, "%c", &ch, 1) == 1) {
        if (ch >= 0x20 && ch < 0x7F) {
            freq[ch - 0x20]++;
        }
    }

    fclose(fp);
    return freq;
}


using HuffTree = BinTree<HuffChar>; //Huffman������BinTree�������ڵ�����ΪHuffChar
using HuffForest = List<HuffTree*>; //Huffmanɭ��
using HuffCode = Bitmap; //Huffman�����Ʊ���


HuffForest* initForest(int* freq)//����Ƶ��ͳ�Ʊ�Ϊÿ���ַ�����һ����
{
    HuffForest* forest = new HuffForest; //��Listʵ�ֵ�Huffmanɭ��
    for (int i = 0; i < N_CHAR; i++) //Ϊÿ���ַ�
    {
        forest->insertAsLast(new HuffTree); //����һ�����������ַ�����Ƶ��
        forest->last()->data->insertAsRoot(HuffChar(0x20 + i, freq[i])); //��������
    }
    return forest;
}

HuffTree* minHChar(HuffForest* forest)//��Huffmanɭ�����ҳ�Ȩ����С��Huffman�ַ�
{
    ListNodePosi(HuffTree*) m = forest->first(); //���׽ڵ�������������нڵ�
    for (ListNodePosi(HuffTree*) p = m->succ; forest->valid(p); p = p->succ)
    {
        if (m->data->root()->data.weight > p->data->root()->data.weight) //���ϸ���
        {
            m = p; //�ҵ���С�ڵ㣨����Ӧ��Huffman������
        }
    }
    return forest->remove(m); //��ɭ����ȡ����������������
}

HuffTree* generateTree(HuffForest* forest) //Huffman�����㷨
{
    while (1 < forest->size())
    {
        HuffTree* T1 = minHChar(forest); HuffTree* T2 = minHChar(forest);
        HuffTree* S = new HuffTree();
        S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
        S->attachAsLC(S->root(), T1);
        S->attachAsRC(S->root(), T2);
        forest->insertAsLast(S);
    } //assert: ѭ������ʱ��ɭ����Ψһ���б��׽ڵ��У����ǿ�����Huffman������
    return forest->first()->data;
}

static void generateCT(Bitmap* code, int length, HuffTable* table, BinNodePosi(HuffChar) v)//ͨ��������ȡ���ַ��ı���
{
    if (IsLeaf(*v)) //����Ҷ�ڵ�
    {
        table->put(v->data.ch, code->bits2string(length));
        return;
    }
    if (HasLChild(*v)) //Left = 0
    {
        code->clear(length);
        generateCT(code, length + 1, table, v->lc);
    }
    if (HasRChild(*v)) //Right = 1
    {
        code->set(length);
        generateCT(code, length + 1, table, v->rc);
    }
}
HuffTable* generateTable(HuffTree* tree) //�����ַ�����ͳһ������ɢ�б�ʵ�ֵı������
{
    HuffTable* table = new HuffTable; Bitmap* code = new Bitmap;
    generateCT(code, 0, table, tree->root()); release(code); return table;
};
int encode(HuffTable* table, Bitmap* codeString, char* s) //���ձ�����Bitmap������
{
    int n = 0; //�����صı��봮�ܳ�n
    for (size_t m = strlen(s), i = 0; i < m; i++) //���������е�ÿ���ַ�
    {
        char** pCharCode = table->get(s[i]); //ȡ�����Ӧ�ı��봮
        if (!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a'); //Сд��ĸתΪ��д
        if (!pCharCode) pCharCode = table->get(' '); //�޷�ʶ����ַ�ͳһ�����ո�
        printf("%s", *pCharCode); //�����ǰ�ַ��ı���
        for (size_t m = strlen(*pCharCode), j = 0; j < m; j++) //����ǰ�ַ��ı��������봮
            '1' == *(*pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
    }
    printf("\n");
    return n;
} //�����Ʊ��봮��¼��λͼcodeString��
void decode(HuffTree* tree, Bitmap* code, int n)
{
    BinNodePosi(HuffChar) x = tree->root();
    for (int i = 0; i < n; i++)
    {
        x = code->test(i) ? x->rc : x->lc;
        if (IsLeaf(*x))
        {
            printf("%c", x->data.ch);
            x = tree->root();
        }
    }
} 

