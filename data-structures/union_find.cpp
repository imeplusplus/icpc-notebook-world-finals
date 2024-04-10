// DSU (DISJOINT SET UNION / UNION-FIND)                                           
// Time complexity:  Unite - O(alpha n)                                            
// 									Find - O(alpha n)                                             
// Usage: find(node), unite(node1, node2), sz[find(node)]                          
// Notation: par: vector of parents                                                
// 					sz:  vector of subsets sizes, i.e. size of the subset a node is in    
int par[N], sz[N], his[N];
stack <pii> sp, ss;

int find(int a) { return par[a] == a ? a : par[a] = find(par[a]); }

void unite(int a, int b) {
	if ((a = find(a)) == (b = find(b))) return;
	if (sz[a] < sz[b]) swap(a, b);
	par[b] = a; sz[a] += sz[b];
}

//in main
for(int i = 0; i < N; i++) par[i] = i, sz[i] = 1, his[i] = 0;

//Rollback
int find (int a) { return par[a] == a ? a : find(par[a]); }

void unite (int a, int b) {
	if ((a = find(a)) == (b = find(b))) return;
	if (sz[a] < sz[b]) swap(a, b);
	ss.push({a, sz[a]});
	sp.push({b, par[b]});
	sz[a] += sz[b];
	par[b] = a;
}

void rollback() {
	par[sp.top().st] = sp.top().nd; sp.pop();
	sz[ss.top().st]  = ss.top().nd; ss.pop();
}

//Partial Persistence
int t, par[N], sz[N]

int find(int a, int t){
	if(par[a] == a) return a;
	if(his[a] > t) return a;
	return find(par[a], t);
}

void unite(int a, int b){
	if(find(a, t) == find(b, t)) return;
	a = find(a, t), b = find(b, t), t++;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b], par[b] = a, his[b] = t;
}