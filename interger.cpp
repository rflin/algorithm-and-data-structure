#include <bits/stdc++.h>
using namespace std;
string Add(string a, string b){
	if(a.size() < b.size()) return Add(b, a);
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int len = a.size(), i = 0;
	int sur = 0;
	b += string(a.size() - b.size(), '0');
	string res;
	while(i < len){
		int sum = (a[i] - '0' + b[i] - '0' + sur);
		res += '0' + sum % 10;
		sur = sum / 10;
		++i;
	}
	if(sur > 0) res += '0' + sur;
	reverse(res.begin(), res.end());
	return res;
}
string Substract(string a, string b){
	if(a.size() < b.size() || (a.size() == b.size() && a < b)) return "-" + Substract(b, a);
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	b += string(a.size() - b.size(), '0');
	vector<int> va;
	for(char &x: a) va.push_back(x - '0');
	for(unsigned i = 0; i < va.size(); ++i){
		va[i] = va[i] - (b[i] - '0');
		if(va[i] < 0){
			va[i] += 10;
			va[i + 1] --;
		}
	}
	while(va.back() == 0 && va.size() > 1) va.pop_back();
	string res;
	for(auto it = va.rbegin(); it != va.rend(); ++it){
		res += '0' + *it;
	}
	return res;
}
string Multiply(string a, string b){
	if(a.size() < b.size()) return Multiply(b, a);
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	b += string(a.size() - b.size(), '0');
	vector<int> v(a.size() * a.size(), 0);
	int len = a.size();
	for(int i = 0; i < len; ++i){
		for(int j = 0; j < len; ++j){
			v[i + j] += (a[i] - '0') * (b[j] - '0');
		}
	}
	int sur = 0;
	string res;
	for(unsigned i = 0; i < v.size(); ++i){
		int sum = v[i] + sur;
		v[i] = sum % 10;
		sur = sum / 10;
		res += '0' + v[i];
	}
	while(res.back() == '0' && res.size() > 1) res.pop_back();
	reverse(res.begin(), res.end());
	return res;
}
string Divide(string a, string b){
	int cnt = 0;
	while((a = Substract(a, b))[0] != '-') ++cnt;
	return to_string(cnt);
}
int main()
{
	while(true){
		string a, b;
		cin >> a >> b;
		cout << Divide(a, b) << endl;
	}
	return 0;
} 
