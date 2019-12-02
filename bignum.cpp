#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

class BigNum
{
    private:
        unsigned int * date; // каждое число - 9 цифр
    public:
        size_t sz;
        BigNum(){
            sz = 1;
            date = new unsigned int[sz];
        }
        BigNum(size_t s){
            sz = s;
            date = new unsigned int[sz];
        }
        BigNum(size_t s, const int * d){
            sz = s;
            date = new unsigned int[sz];
            for(size_t i = 0; i < sz; i++){
                date[i] = d[i];
            }
        }
        BigNum(int a){
            sz = 1;
            date = new unsigned int[sz];
            date[0] = a;
        }
        BigNum(BigNum &a){
            sz = a.sz;
            date = new unsigned int[sz];
            for(size_t i = 0; i < sz; i++)date[i] = a.get(i);
        }
        BigNum(const char * num){
            string s = num;
        }
        BigNum(string s){
            // надо реализовать!
        }
        unsigned int get(size_t i) const {
            return (i < sz)?date[i]:0;
        }
        BigNum & operator =(BigNum const& a){
            sz = a.sz;
            date = new unsigned int[sz];
            for(size_t i = 0; i < sz; i++)date[i] = a.get(i);
            return *this;
        }
        BigNum & operator +=(BigNum const& a){
            size_t szmax = (a.sz < sz)?sz:a.sz;
            unsigned int * s = new unsigned int[szmax + 1];
            unsigned int p = 0; // перенос
            for(size_t i = 0; i < szmax + 1; i++){
                s[i] = this->get(i) + a.get(i) + p;
                p = s[i] / 1000000000;
                s[i] %= 1000000000;
            }
            if(s[szmax] == 0){
                if(sz != szmax){//определение необходимости перераспределения памяти
                    delete [] date;
                    date = new unsigned int[szmax];
                    sz = szmax;
                }
            }else{
                delete [] date;
                date = new unsigned int[szmax + 1];
                sz = szmax + 1;
            }
            for(size_t i = 0; i < sz; i++)date[i] = s[i];
            delete [] s;
            return *this;
        }
        void show(){
            string s = "";
            for(size_t i = 0; i < sz; i++){
                stringstream ss;
                if(i == sz - 1){
                    ss << date[i];
                }else{
                    ss << setw(9) << setfill('0') << date[i];
                }
                s = ss.str() + s;
            }
            cout << s;
        }
        ~BigNum(){
            delete [] date;
        }
};

BigNum operator +(BigNum a1, BigNum const& a2){
    return a1 += a2;
}
// надо реализоваать операторы:
// [] - вместо метода get(i)
// -=, --, ++, >, <, >=, <=, ==, !=, *=, /=, %=, *, /, %
int main()
{
    BigNum a1;
    BigNum a2;
    BigNum a3;
    a1 = BigNum(1);
    a2 = BigNum(1);
    for(int i = 0; i < 100000; i++){
        a3 = a1 + a2;
        a1 = a2;
        a2 = a3;
    }
    a3.show();
    return 0;
}
