#include<iostream>
#include"../../../Vector/Vector.h"
#include"../../../Vector/Vector_fun.h"
#include<cstdlib>
using namespace std;
int BiggestArea(Vector<int>& heights) { //  用的不是队列而是向量
        int n = heights.size();
        int ans = 0;
        for (int mid = 0; mid < n; mid++) {
            int height = heights[mid];
            int left = mid, right = mid;
            // 确定左右边界
            while (left - 1 >= 0 && heights[left - 1] >= height) {
                --left;
            }
            while (right + 1 < n && heights[right + 1] >= height) {
                ++right;
            }
            // 计算面积
            ans = max(ans, (right - left + 1) * height);
        }
        return ans;
    }


int main() {

    int X[6] = { 2,1,5,6,2,3 };
    Vector<int> heights(X,6);
    int a= BiggestArea(heights);
    cout << "heights = [2,1,5,6,2,3]"<<endl;
    cout << "最大面积为" << a << endl;
    

    for (int i = 0; i < 10; i++) {
        int Y[105];
        int y = rand() % 105  + 1;
        for (int j = 0; j < y; j++) {
            Y[j] = rand() % 105;
            cout << Y[j] << " ";  
        }
        Vector<int>Heights(Y, y);
        int b = BiggestArea(Heights);
        cout << endl;
        cout << "最大面积为" << b<<endl;
    }

    
 
    return 0;
}