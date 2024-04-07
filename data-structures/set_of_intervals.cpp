// Set of Intervals
// Use when you have disjoint intervals
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

typedef pair<int, int> pii;
typedef pair<pii, int> piii;

int n, m, x, t;
set<piii> s;

void in(int l, int r, int i) {
	vector<piii> add, rem;
	auto it = s.lower_bound({{l, 0}, 0});
	if(it != s.begin()) it--;
	for(; it != s.end(); it++) {
		int ll = it->first.first;
		int rr = it->first.second;
		int idx = it->second;

		if(ll > r) break;
		if(rr < l) continue;
		if(ll < l) add.push_back({{ll, l-1}, idx});
		if(rr > r) add.push_back({{r+1, rr}, idx});
		rem.push_back(*it);
	}
	add.push_back({{l, r}, i});
	for(auto x : rem) s.erase(x);
	for(auto x : add) s.insert(x);
}