vector<pair<point, point>> edges;

//add id to point struct, mark the point with an Id, better if long long coordinates
sort(pts.begin(), pts.end());
for(int i = 0; i < pts.size(); i++){
		point p = pts[i];
		id[p] = i;
}

//create edges and sort perpendicular radially
for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			edges.pb({pts[i], pts[j]});
		}
}
//geometry/radial_sort.cpp
sort(edges.begin(), edges.end(), cmp);

//smaller triangle
for(auto e : edges){
		int tmp = INF;
		int l = id[e.st], r = id[e.nd];
		//do stuff
		//1- remember points will for sure be adjacents.
		//2- if you are not sure about adjacency, the points in beetween will be collinear
		//3- point [r + 1, ..., n] are ordered by distance to r (r + 1: closest, n: furthest)
		//4- point [0, ..., l - 1] are ordered by distance to l (l - 1: closest, 0: furthest)
		//5- you can find max, min triangles and do binary search / two points using this information.
		swap(pts[l], pts[r]);
		swap(id[e.nd], id[e.st]);
}