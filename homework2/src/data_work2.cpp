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

        while (true) {
            cout << "請輸入第 " << i + 1 << " 項的係數與指數 (如: 3 2):";
            is >> coef >> exp;

            if (exp >= 0)break;
            cout << "[錯誤]請重新輸入!\n";

        }

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