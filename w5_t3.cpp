#include <iostream>
#include <algorithm>
using namespace std;
string strip(const string &s){
    int i = 0;
    while(i <(int)s.size() - 1 && s[i] == '0') 
        i++;
    return s.substr(i);
}
string add(const string &a,const string &b){
    int i = a.size()-1,j = b.size()-1,carry = 0;
    string res;
    while(i >= 0 || j >= 0 || carry){
        int x =(i >= 0 ? a[i--]-'0' : 0);
        int y =(j >= 0 ? b[j--]-'0' : 0);
        int s = x + y + carry;
        res.push_back(char('0' +(s % 10)));
        carry = s / 10;
    }
    reverse(res.begin(),res.end());
    return strip(res);
}
string sub(const string &a,const string &b){
    int i = a.size()-1,j = b.size()-1,borrow = 0; 
    string res;
    while(i >= 0){
        int x = a[i]-'0' - borrow;
        int y =(j >= 0 ? b[j--]-'0' : 0);
        if(x < y){ 
            x += 10; 
            borrow = 1; 
        }else 
            borrow = 0;
        res.push_back(char('0' +(x - y)));
        i--;
    }
    while(res.size() > 1 && res.back() == '0') 
        res.pop_back();
    reverse(res.begin(),res.end());
    return strip(res);
}
string karatsuba(const string &a,const string &b){
    string x = strip(a),y = strip(b);
    if(x.size() <= 4 || y.size() <= 4){
        long long n1 = stoll(x),n2 = stoll(y);
        return to_string(n1 * n2);
    }
    int n = max(x.size(),y.size());
    if(n % 2) 
        n++;
    x = string(n - x.size(),'0') + x;
    y = string(n - y.size(),'0') + y;
    int m = n / 2;
    string p = x.substr(0,n-m),q = x.substr(n-m);
    string r = y.substr(0,n-m),s = y.substr(n-m);
    string z0 = karatsuba(q,s);
    string z2 = karatsuba(p,r);
    string z1 = karatsuba(add(p,q),add(r,s));
    z1 = sub(sub(z1,z2),z0);
    return strip(add(add(z2 + string(2*m,'0'),z1 + string(m,'0')),z0));
}
string multiply(string num1,string num2){
    if(num1 == "0" || num2 == "0") return "0";
    return karatsuba(num1,num2);
}
int main(){
    cout << multiply("12123123133","412312312356") << endl;
}
