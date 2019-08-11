#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> v = {
	{0,0,8, 0,0,0, 0,0,0},
	{6,0,0, 0,9,0, 0,4,1},
	{0,4,0, 0,0,6, 9,7,0},

	{0,0,4, 2,0,0, 0,1,6},
	{0,0,0, 0,4,0, 0,0,0},
	{3,1,0, 0,0,5, 7,0,0},

	{0,6,9, 7,0,0, 0,0,0},
	{4,8,0, 0,5,0, 0,0,3},
	{0,0,0, 0,0,0, 4,0,0}
};

void show(){
	for(auto vx: v){
		for(int x: vx){
			printf("%d ", x);
		}
		printf("\n");
	}
	printf("\n");
}

vector<int> possibleValue(int i, int j){
	map<int, int> mp;
	for(int k = 0; k < 9; ++k){
		if(v[i][k] > 0){
			mp[v[i][k]]++;
		}
	}
	for(int k = 0; k < 9; ++k){
		if(v[k][j] > 0){
			mp[v[k][j]] = 1;
		}
	}
	int ix = i / 3 * 3, jy = j / 3 * 3;
	for(int k = ix; k < ix + 3; ++k){
		for(int l = jy; l < jy + 3; ++l){
			if(v[k][l] > 0){
				mp[v[k][l]] = 1;
			}
		}
	}
	vector<int> vres;
	for(int val = 1; val <= 9; ++val){
		if(mp.count(val) == 0){
			vres.push_back(val);
		}
	}
	return vres;
}
void res2file(){
	ofstream out("result.txt", ios::app);
	for(auto vx: v){
		for(int x: vx){
			out << x << " ";
		}
		out << endl;
	}
	out << endl;
	out.close();
}
void dfs(int n){
	if(n > 80) {
		show();
		res2file();
		return;
	}
	int i = n / 9, j = n % 9;
	if(v[i][j] == 0){
		auto vals = possibleValue(i, j);
		if(vals.size() == 0) return;
		for(int e: vals){
			v[i][j] = e;
			dfs(n + 1);
			// if(res) return true;
			v[i][j] = 0;
		}
	}else{
		dfs(n + 1);
	}
}

int main()
{
	int k, l;
	if(remove("result.txt") == 0){
		printf("delete success\n");
	}
	for(int i = 0; i < 9; ++ i){
		for(int j = 0; j < 9; ++j){
			if(v[i][j] == 0){
				k = i;
				l = j;
				break;
			}
		}
		break;
	}
	printf("k = %d, l = %d\n", k, l);
	dfs(k * 9 + l);
	return 0;
}
