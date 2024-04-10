//Time complexity: O(V+E)                                                         
const int N = 2e5 + 5;

vector<int> adj[N], adjt[N];
int n, ordn, scc_cnt, vis[N], ord[N], scc[N];

//Directed Version
void dfs(int u) {
	vis[u] = 1;
	for (auto v : adj[u]) if (!vis[v]) dfs(v);
	ord[ordn++] = u;
}

void dfst(int u) {
	scc[u] = scc_cnt, vis[u] = 0;
	for (auto v : adjt[u]) if (vis[v]) dfst(v);
}

// add edge: u -> v
void add_edge(int u, int v){
	adj[u].push_back(v);
	adjt[v].push_back(u);
}

//Undirected version:
/*
	int par[N];

	void dfs(int u) {
		vis[u] = 1;
		for (auto v : adj[u]) if(!vis[v]) par[v] = u, dfs(v);
		ord[ordn++] = u;
	}

	void dfst(int u) {
		scc[u] = scc_cnt, vis[u] = 0;
		for (auto v : adj[u]) if(vis[v] and u != par[v]) dfst(v);
	}

	// add edge: u -> v
	void add_edge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

*/

// run kosaraju
void kosaraju(){
	for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
	for (int i = ordn - 1; i >= 0; --i) if (vis[ord[i]]) scc_cnt++, dfst(ord[i]);
}