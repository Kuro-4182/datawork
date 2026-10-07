# 41443143

作業一問題一

## 解題說明

這題是Ackermann's function 的實作

### 解題策略

1. 呼叫函式a(m,n)，若m=0回傳n+1
2. 若n=0則使用遞迴呼叫a(m-1,1)
3. 其他情況則使用遞迴呼叫a(m-1,a(m,n-1))  
4. 主程式輸出計算結果。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>

using namespace std;

int a(int m, int n) {

    if (m == 0) return(n + 1);
    else if (n == 0)return a(m - 1, 1);
    else return a(m - 1, a(m, n - 1));
}

int main(){
    int m, n;
    while (cin >> m >> n) {
        cout << a(m, n) << endl;
    }
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(2^n)$。
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$， $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $m = 0$， $n = 0$| 1        | 1        |
| 測試二   | $m = 0$， $n = 3$| 4        | 4        |
| 測試三   | $m = 1$， $n = 0$| 2        | 2        |
| 測試四   | $m = 1$， $n = 2$| 4       | 4       |
| 測試五   | $m = 2$， $n = 2$| 7 | 7 |

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算的主要原因為:
   題目以明確指出符合特定條件則需再次使用阿克曼函式計算，剛好符合遞迴的結構。



作業一問題二

## 解題說明

這題是輸出字元集合的所有子集合。

### 解題策略

1. 定義函式
2. 若index == n則結束遞迴呼叫並輸出陣列
3. index != n則遞迴呼叫 
4. 把目前的字元放入陣列
5. 在遞迴
6. 主程式將字元陣列輸入遞迴函式計算。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>

using namespace std;

void func(char S[], int n, int index, char current[], int currentSize) {
    
    if (index == n) {
        cout << "(";
        for (int i = 0; i < currentSize; ++i) {
            cout << current[i];
            if (i < currentSize - 1) {
                cout << ",";
            }
        }
        cout << ") ";
        return;
    }

    func(S, n, index + 1, current, currentSize);

    current[currentSize] = S[index];
    func(S, n, index + 1, current, currentSize + 1);
}

int main() {
    char S[] = { 'a', 'b', 'c'};
    int n = sizeof(S) / sizeof(S[0]);

    char current[1000];

    cout << "powerset (S) = { ";
    func(S, n, 0, current, 0);
    cout << "}" << endl;

}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(2^n)$。
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | a, b, c | powerset (S) = { () (a) (b) (c) (a,b) (a,c) (b,c) (a,b,c) } | powerset (S) = { () (c) (b) (b,c) (a) (a,c) (a,b) (a,b,c) } |

## 申論及開發報告

在本程式中，使用遞迴來計算的主要原因為:
   使用二元判斷能簡單達成題目要求，而二元判斷剛好符合遞迴的結構。

需再研究能按照字母順序輸出的方式。
