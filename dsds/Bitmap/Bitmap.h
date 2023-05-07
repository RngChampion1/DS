#include<iostream>
#include<string>
using namespace std;
typedef int Rank;
class Bitmap//位图Bitmap类 
{
private:
    unsigned char* M;
    Rank N, _sz; //位图空间M[]，N*sizeof(char)*8个比特中含_sz个有效位
protected:
    void init(Rank n)
    {
        M = new unsigned char[N = (n + 7) / 8]; memset(M, 0, N); _sz = 0;
    }
public:
    Bitmap(Rank n = 8) { init(n); } //按指定容量创建位图

    ~Bitmap() { delete[] M; M = NULL; _sz = 0; } //析构时释放位图空间

    Rank size() { return _sz; }
    void set(Rank k) { expand(k); _sz++; M[k >> 3] |= (0x80 >> (k & 0x07)); }
    void clear(Rank k) { expand(k); _sz--; M[k >> 3] &= ~(0x80 >> (k & 0x07)); }
    bool test(Rank k) { expand(k); return M[k >> 3] & (0x80 >> (k & 0x07)); }


    char* bits2string(Rank n) //将前n位转换为字符串——
    {
        expand(n - 1); //此时可能被访问的最高位为bitmap[n - 1]
        char* s = new char[n + 1]; s[n] = '\0'; //字符串所占空间，由上层调用者负责释放
        for (Rank i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
        return s; //返回字符串位置
    }
    void expand(Rank k)//若被访问的Bitmap[k]已出界，则需扩容
    {
        if (k < 8 * N) return; //仍在界内，无需扩容
        Rank oldN = N; unsigned char* oldM = M;
        init(2 * k); //与向量类似，加倍策略
        memcpy_s(M, N, oldM, oldN);
        delete[] oldM; //原数据转移至新空间
    }
};