#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <cmath>
#include <stack>
#include <deque>
#include <queue>
#include <iomanip>
#include <fstream>
#include <climits>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

//#define cout fout
//#define cin fin
//#define double long double
//#define int ll

//const int inf = INT_MAX;
//const double eps = 1e-9;
using namespace std;

struct xy {
	int x, y;
	bool operator<(const xy& rhs) const {
		return make_pair(this->x, this->y) < make_pair(rhs.x, rhs.y);
	}
	bool operator==(const xy& rhs) const {
		return make_pair(this->x, this->y) == make_pair(rhs.x, rhs.y);
	}
};

map<xy, int> num;
vector<int> coun;
vector<int> quan;
vector<int> p, sz;

class dsu {
public:
	dsu() {};
	void init(int& n) {
		p.assign(2 * n, -1);
		sz.resize(2 * n);
		c.assign(2 * n, -1);
	}
	void make_root(int& v) {
		p[v] = v;
		sz[v] = 1;
	}
	int root(int v) {
		if (v == p[v])
			return v;
		return p[v] = root(p[v]);
	}
	void add(int a, int b) {
		a = root(a);
		b = root(b);
		if (a != b) {
			if (sz[a] < sz[b])
				swap(a, b);
			p[b] = a;
			sz[a] += sz[b];
		}
	}
private:
	vector<int> p, sz;
	vector<int> c;
};

dsu D;

int ok(int& v) {
	if (quan[D.root(v)] == -1) return quan[D.root(v)] = 0;
	return ((quan[D.root(v)] == 0) || (quan[D.root(v)] == 2)) ? 1 : 0;
}

int main()
{
	//ifstream fin("input.txt");
	//ofstream fout("output.txt");
	//ios_base::sync_with_stdio(false);
	//cout.tie(0);
	int n; cin >> n;
	coun.assign(2 * n, 0);
	quan.assign(2 * n, 0);
	int ans = 0;
	xy v, u;
	D.init(n);
	vector<int> Ans;
	for (int i = 0; i < n; ++i) {
		cin >> v.x >> v.y >> u.x >> u.y;
		int v1, v2;
		if (num.find(v) == num.end()) {
			v1 = num[v] = num.size();
			D.make_root(v1);
			quan[D.root(v1)] = -1;
		}
		if (num.find(u) == num.end()) {
			v2 = num[u] = num.size();
			D.make_root(v2);
			quan[D.root(v2)] = -1;
		}
		v1 = num[v]; v2 = num[u];
		//cout << '!' << v1 << ' ' << v2 << endl;
		//if (v1 > v2) swap(v1, v2);
		if (D.root(v1) == D.root(v2)) {
			if (ok(v1)) --ans;
			if (coun[v2] % 2)
				--quan[D.root(v2)];
			else
				++quan[D.root(v2)];
			if (coun[v1] % 2)
				--quan[D.root(v1)];
			else
				++quan[D.root(v1)];
			++coun[v1]; ++coun[v2];
			if (ok(v1)) ++ans;
			Ans.push_back(ans);
			continue;
		}
		if (ok(v2)) --ans;
		if (ok(v1)) --ans;
		if (coun[v2] % 2)
			--quan[D.root(v2)];
		if (coun[v1] % 2)
			--quan[D.root(v1)];
		int buf = quan[D.root(v2)] + quan[D.root(v1)];
		quan[D.root(v2)] = quan[D.root(v1)] = 0;
		++coun[v1]; ++coun[v2];
		D.add(v1, v2);
		if (coun[v2] % 2)
			++quan[D.root(v2)];
		if (coun[v1] % 2)
			++quan[D.root(v1)];
		quan[D.root(v1)] += buf;
		if (ok(v1)) ++ans;
		Ans.push_back(ans);
	}
	for (int& ai: Ans)
		cout << ai << endl;
	//fin.close(); fout.close();
	return 0;
}
