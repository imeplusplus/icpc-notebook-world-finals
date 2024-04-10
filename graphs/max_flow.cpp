// Dinic - O(V^2 * E)
// Bipartite graph or unit flow - O(sqrt(V) * E)
// Small flow - O(F * (V + E))
// USE INF = 1e9!
template <class T = int>
class Dinic {
public:
	struct Edge {
		Edge(int a, T b){to = a;cap = b;}
		int to;
		T cap;
	};

	Dinic(int _n) : n(_n) {
		edges.resize(n);
	}

	T maxFlow(int src, int sink) {
		T ans = 0;
		while(bfs(src, sink)) {
			// maybe random shuffle edges against bad cases?
			T flow;
			pt = std::vector<int>(n, 0);
			while((flow = dfs(src, sink))) {
				ans += flow;
			}
		}
		return ans;
	}

	void addEdge(int from, int to, T cap, T other = 0) {
		edges[from].push_back(list.size());
		list.push_back(Edge(to, cap));
		edges[to].push_back(list.size());
		list.push_back(Edge(from, other));
	}

	bool inCut(int u) const { return h[u] < n; }
	int size() const { return n; }
private:
	int n;
	std::vector<std::vector<int> > edges;
	std::vector<Edge> list;
	std::vector<int> h, pt;

	T dfs(int on, int sink, T flow = 1e9) {
		if(flow == 0) {
			return 0;
		} if(on == sink) {
			return flow;
		}
		for(; pt[on] < (int) edges[on].size(); pt[on]++) {
			int cur = edges[on][pt[on]];
			if(h[on] + 1 != h[list[cur].to]) {
				continue;
			}
			T got = dfs(list[cur].to, sink, std::min(flow, list[cur].cap));
			if(got) {
				list[cur].cap -= got;
				list[cur ^ 1].cap += got;
				return got;
			}
		}
		return 0;
	}

	bool bfs(int src, int sink) {
		h = std::vector<int>(n, n);
		h[src] = 0;
		std::queue<int> q;
		q.push(src);
		while(!q.empty()) {
			int on = q.front();
			q.pop();
			for(auto a : edges[on]) {
				if(list[a].cap == 0) {
					continue;
				}
				int to = list[a].to;
				if(h[to] > h[on] + 1) {
					h[to] = h[on] + 1;
					q.push(to);
				}
			}
		}
		return h[sink] < n;
	}
};

// FLOW WITH DEMANDS                                                                            
																																														
// 1 - Finding an arbitrary flow                                                                
// Assume a network with [L, R] on edges (some may have L = 0), let's call it old network.      
// Create a New Source and New Sink (this will be the src and snk for Dinic).                   
// Modelling Network:                                                                           
// 1) Every edge from the old network will have cost R - L                                      
// 2) Add an edge from New Source to every vertex v with cost:                                  
// 	Sum(L) for every (u, v). (sum all L that LEAVES v)                                        
// 3) Add an edge from every vertex v to New Sink with cost:                                    
// 	Sum(L) for every (v, w). (sum all L that ARRIVES v)                                       
// 4) Add an edge from Old Source to Old Sink with cost INF (circulation problem)               
// The Network will be valid if and only if the flow saturates the network (max flow == sum(L)) 
																																														
// 2 - Finding Min Flow                                                                         
// To find min flow that satisfies just do a binary search in the (Old Sink -> Old Source) edge 
// The cost of this edge represents all the flow from old network                               
// Min flow = Sum(L) that arrives in Old Sink + flow that leaves (Old Sink -> Old Source)