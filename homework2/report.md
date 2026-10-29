# 41443143

作業二

## 解題說明

這題要製作term類別用來儲存多項式非零項的係數與指數
以及polynomial類別計算多項式相加，相乘及帶入x的值

### 解題策略

1. 建立term與polynomial的基本架構
2. 在term宣告coef與exp用來儲存係數與指數
3. 用newterm函式將coef & exp 儲存進 termarray 並實作自動擴充儲存空間
4. 為了能有效率的debug，先實作輸入與輸出的運算子多載:重載>>&<<
5. 實作計算功能: 多項式相加add，多項式相乘mult，多項式求值eval
6. 完成主程式的輸入多項式，使用者選擇功能與輸出答案。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class term;
class polynomial;

ostream& operator<<(ostream& os, const polynomial& p);
istream& operator>>(istream& is, polynomial& p);

class term {
    friend polynomial;
    friend ostream& operator<<(ostream& os, const polynomial& p);
    friend istream& operator>>(istream& is, polynomial& p);
private:
    float coef;
    int exp;
public:
    term(float c = 0, int e = 0) :coef(c), exp(e) {}
};

class polynomial {
    friend ostream& operator<<(ostream& os, const polynomial& p);
    friend istream& operator>>(istream& is, polynomial& p);
private:
    term* termarray;
    int capacity;
    int terms;
public:
    polynomial() {

        capacity = 1;
        terms = 0;
        termarray = new term[capacity];

    }

    ~polynomial() {
        delete[] termarray;
    }

    polynomial(const polynomial& other) {
        capacity = other.capacity;
        terms = other.terms;
        termarray = new term[capacity];
        for (int i = 0; i < terms; i++) termarray[i] = other.termarray[i];
    }

    polynomial& operator=(const polynomial& other) {
        if (this == &other)return *this;
        delete[] termarray;
        capacity = other.capacity;
        terms = other.terms;
        termarray = new term[capacity];
        for (int i = 0; i < terms; i++) termarray[i] = other.termarray[i];
        return *this;
    }

    void newterm(const float coef, const int exp) {

        if (coef == 0)return;

        for (int i = 0; i < terms; i++) {
            if (termarray[i].exp == exp) {
                termarray[i].coef += coef;
                return;
            }
        }

        if (terms == capacity) {

            capacity *= 2;
            term *arraycopy = new term[capacity];
            copy(termarray, termarray + terms, arraycopy);
            delete[] termarray;
            termarray = arraycopy;

        }

        int idx = terms;
        for (int i = 0; i < terms; i++) {
            if (exp > termarray[i].exp) {
                idx = i;
                break;
            }
        }

        for (int i = terms; i > idx; i--) {
            termarray[i] = termarray[i - 1];
        }

        termarray[idx].coef = coef;
        termarray[idx].exp = exp;
        terms++;

    }

    polynomial add(polynomial p) {

        polynomial c;
        int a = 0, b = 0;

        while (a < terms && b < p.terms) {
            if (termarray[a].exp == p.termarray[b].exp) {
                float sum = termarray[a].coef + p.termarray[b].coef;
                if (sum != 0)c.newterm(sum, termarray[a].exp);
                a++;
                b++;
            }
            else if (termarray[a].exp < p.termarray[b].exp) {
                c.newterm(p.termarray[b].coef, p.termarray[b].exp);
                b++;
            }
            else if (termarray[a].exp > p.termarray[b].exp) {
                c.newterm(termarray[a].coef, termarray[a].exp);
                a++;
            }
            
        }

        for (; a < terms; a++)c.newterm(termarray[a].coef, termarray[a].exp);
        for (; b < p.terms; b++) c.newterm(p.termarray[b].coef, termarray[b].exp);

        return c;

    }

    polynomial mult(polynomial p) {

        polynomial c;

        if (terms == 0 || p.terms == 0) return c;

        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < p.terms; j++) {

                float co = termarray[i].coef * p.termarray[j].coef;
                int ex = termarray[i].exp + p.termarray[j].exp;
                c.newterm(co, ex);
            }
        }

        return c;

    }

    float eval(float f) {

        float result = 0;
        for (int i = 0; i < terms; i++) {
            result += termarray[i].coef * pow(f, termarray[i].exp);
        }
        return result;
    }
};

istream& operator>>(istream& is, polynomial& p) {
    
    int numterms;
    cout << "請輸入多項式的項數:";
    is >> numterms;

    for (int i = 0; i < numterms; i++) {
        float coef;
        int exp;
        cout << "請輸入第 " << i + 1 << " 項的係數與指數 (如: 3 2):";
        is >> coef >> exp;

        p.newterm(coef, exp);

    }

    cout << endl;
    return is;

}

ostream& operator<<(ostream& os, const polynomial& p) {

    if (p.terms == 0) {
        os << "0";
        return os;
    }

    for (int i = 0; i < p.terms; i++) {
        
        float c = p.termarray[i].coef;
        int e = p.termarray[i].exp;

        if (i > 0 && c > 0) {
            os << " + ";
        }
        else if (c < 0) {
            os << " - ";
            c = -c;
        }

        os << c;
        if (e > 0) {
            os << "x^" << e;
        }
        
    }

    return os;

}

void list() {
    cout << "1.多項式相加。" << endl;
    cout << "2.多項式相乘。" << endl;
    cout << "3.帶入x的值。" << endl;
    cout << "4.結束。" << endl;
    cout << "請輸入要對多項式的運算:";
}

int main()
{
    polynomial a, b;
    cout << "請輸入第一個多項式" << endl;
    cin >> a ;
    cout << "請輸入第二個多項式" << endl;
    cin >> b;

    int n;
    list();
    while (cin >> n && n != 4) {

        switch (n) {
        case 1: {
            polynomial c = a.add(b);
            cout << "a + b = " << c << endl;
            break;
        }
        case 2: {
            polynomial c = a.mult(b);
            cout << "a * b = " << c << endl;
            break;
        }
        case 3: {
            int in, x;
            float ans;
            cout << "選擇要帶入運算的多項式 (1 or 2):";
            cin >> in;
            cout << "輸入x的值:";
            cin >> x;
            if (in == 1)ans = a.eval(x);
            else if (in == 2)ans = b.eval(x);
            cout << "x帶入 " << x << " = " << ans << endl;
            break;
        }
        default:break;
        }

        list();

    } 
      
}
```

## 效能分析

1. 時間複雜度：
     add函式:設兩個多項式的非零項數分別為m和n，時間複雜度則為 $O(m + n)$。
     mult函式的時間複雜度為 $O((m \dot n)^2)$
     eval函式:設多項式共有n個非零項，時間複雜度則為 $O(n)$。
3. 空間複雜度：設多項式共有n個非零項，空間複雜度為 $O(t)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 多項式一， 多項式二 | 運算方式 | 預期輸出 | 實際輸出 |
|----------|-------------------------|----------|----------|----------|
| 測試一   | $3x^2+2x+1$， $x^2-2x+5$| 相加      | $4x^2+6$ | &4x^2+6& |
|         | 同上， 同上              | 相乘      | $3x^4-4x^3+12x^2+8x+5$|$3x^4-4x^3+12x^2+8x^1+5$|        |
|         | 同上， /                 | 代入x=2   | 17      |17        |
| 測試二   | $2x^3-4$， $x^2+3x$     | 相加     | $2x^3+x^2+3x-4$|$2x^3+1x^2+3x^1-4$|
|         | 同上， 同上              | 相乘     | $2x^5+6x^4-4x^2-12x$ |$2x^5+6x^4-4x^2-12x^1$|
|         | /， 同上                 | 代入x=3   | 18      | 18       |
| 測試三   | $5x$， $-5x$            | 相加     | 0        | 0        |
|         | 同上， 同上              | 相乘     | $-25x^2$ | $-25x^2$ |
|         | 同上， /                 | 代入x=4  | 20       | 20       |

## 申論及開發報告

### 問題與解決方法
    開發過程中遇到的問題主要有兩個:
        1.未建立copy constructor:進行多項式運算時會將答案儲存近一個新的多項式類別中，但若未建立copy constructor在複製過程會出現錯誤，造成程式崩潰。
            解決方法:建立copy constructor。
        2.未合併次方數相同的項:進行多項式相乘時可能產生複數個次方數相同的項，會造成輸出兩個相同次方的項(例：$(x^2+2)*(x^2+1)$=$x^4+x^2+2x^2+2$)。
            解決方法:在newterm函式中使用for迴圈檢查是否已經儲存過次方數相同的項，若有則直接加上coef。
            
