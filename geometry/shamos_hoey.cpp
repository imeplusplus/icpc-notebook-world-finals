//Shamos - Hoey for test polygon simple in O(nlog(n))
inline bool adj(int a, int b, int n) {return (b == (a + 1)%n or a == (b + 1)%n);}

struct edge{
	point ini, fim;
	edge(point ini = point(0,0), point fim = point(0,0)) : ini(ini), fim(fim) {}
};

struct lower_hull{
    point ini, fim;
    int id_ini, id_fim;
 
    lower_hull(point ini = point(LINF, LINF), point fim = point(-LINF, -LINF)) : ini(ini), fim(fim) {
        id_ini = id_fim = -1;
    }
};

//< here means the edge on the top will be at the begin
bool operator < (const edge& a, const edge& b) {
	if (a.ini == b.ini) return direction(a.ini, a.fim, b.fim) < 0;
	if (a.ini.x < b.ini.x) return direction(a.ini, a.fim, b.ini) < 0;
	return direction(a.ini, b.fim, b.ini) < 0;
}

int n, k[N], p[N], a[N], root;
vector<int> par_upd[N], adj[N];
set<int> paired;
vector <point> hull[N];
pair<point, int> end_hull[N];
lower_hull low[N];

bool is_simple_polygon(const vector<point> &pts){
	//remember to change events style if it is a bunch of convex polygons
	vector <pair<point, pii>> eve;
	vector <pair<edge, int>> edgs;
	set <pair<edge, int>> sweep;
	int n = (int)pts.size();
	for(int i = 0; i < n; i++){
		point l = min(pts[i], pts[(i + 1)%n]);
		point r = max(pts[i], pts[(i + 1)%n]);
		eve.pb({l, {0, i}});
		eve.pb({r, {1, i}});
		edgs.pb(make_pair(edge(l, r), i));
	}
	//{point, {initial/final endpoint, edge index in vector}}
	sort(eve.begin(), eve.end());
	for(auto e : eve){
		if(!e.nd.st){
			auto cur = sweep.lower_bound(edgs[e.nd.nd]);
			pair<edge, int> above, below;
			if(cur != sweep.end()){
				below = *cur;
				if(!adj(below.nd, e.nd.nd, n) and segment_segment_intersect(pts[below.nd], pts[(below.nd + 1)%n], pts[e.nd.nd], pts[(e.nd.nd + 1)%n]))
					return false;
			}
			if(cur != sweep.begin()){
				above = *(--cur);
				if(!adj(above.nd, e.nd.nd, n) and segment_segment_intersect(pts[above.nd], pts[(above.nd + 1)%n], pts[e.nd.nd], pts[(e.nd.nd + 1)%n]))
					return false;
			}
			sweep.insert(edgs[e.nd.nd]);
		}
		else{
			auto below = sweep.upper_bound(edgs[e.nd.nd]);
			auto cur = below, above = --cur;
			if(below != sweep.end() and above != sweep.begin()){
				--above;
				if(!adj(below->nd, above->nd, n) and segment_segment_intersect(pts[below->nd], pts[(below->nd + 1)%n], pts[above->nd], pts[(above->nd + 1)%n]))
					return false;
			}

			//For convex polygons:
			//Process things if the point is the endpoint of this convex hull
			//event: {point, {initial/final endpoint, {hull index, edge index in hull}}}
			if(above != sweep.begin() and end_hull[e.nd.nd.st].nd == e.nd.nd.nd){
				--above;
				//if below lower hull then its father is the father from the polygon with edge above
				if(above->nd.nd < low[above->nd.st].id_fim){
						a[e.nd.nd.st] = above->nd.st;
						par_upd[above->nd.st].pb(e.nd.nd.st);
				}
				//if below upper hull then it is inside the polygon with edge above
				else{
						p[e.nd.nd.st] = above->nd.st;
						paired.insert(e.nd.nd.st);
				}
			}

			sweep.erase(cur);
		}
	}
	return true;
}


//calculate lower hull
//sort lex hull to make most left point to have index 0
sort_lex_hull(hull[i]);
		
low[i].ini = hull[i][0];
low[i].id_ini = 0;
end_hull[i] = {point(-LINF, -LINF), -1};
//search for point that ends lower hull
//end_hull[i] = point that will mark the end of the hull so we can process the polygon in the sweep line
for(int j = 0; j < k[i]; j++){
		point u = hull[i][j];
		if((u.x > low[i].fim.x) or (u.x == low[i].fim.x and u.y < low[i].fim.y)) low[i].fim = u, low[i].id_fim = j;
		end_hull[i] = max(end_hull[i], {u, j});
}

//calculate simple polygon to generate graph of convex hulls
//for all nodes with parent add parent to the nodes that depend on them
while(!paired.empty()){
		auto cur = paired.begin();
		for(auto v : par_upd[*cur]){
				p[v] = p[*cur];
				paired.insert(v);
		}
		par_upd[*cur].clear();
		paired.erase(cur);
}

//generate graph
//n = virtual node;
for(int i = 0; i < n; i++){
		if(p[i] != -1){
				adj[p[i]].pb(i);
		}
		else{
				adj[n].pb(i);
		}
}