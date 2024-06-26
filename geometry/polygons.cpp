//Monotone chain O(nlog(n))
#define REMOVE_REDUNDANT
#ifdef REMOVE_REDUNDANT
bool between(const point &a, const point &b, const point &c) {
	return (fabs(area_2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
#endif

//new change: <= 0 / >= 0 became < 0 / > 0 (yet to be tested)

void convex_hull(vector<point> &pts) {
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	vector<point> up, dn;
	for (int i = 0; i < pts.size(); i++) {
		while (up.size() > 1 && area_2(up[up.size()-2], up.back(), pts[i]) > 0) up.pop_back();
		while (dn.size() > 1 && area_2(dn[dn.size()-2], dn.back(), pts[i]) < 0) dn.pop_back();
		up.push_back(pts[i]);
		dn.push_back(pts[i]);
	}
	pts = dn;
	for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);

	#ifdef REMOVE_REDUNDANT
	if (pts.size() <= 2) return;
	dn.clear();
	dn.push_back(pts[0]);
	dn.push_back(pts[1]);
	for (int i = 2; i < pts.size(); i++) {
		if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
		dn.push_back(pts[i]);
	}
	if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
		dn[0] = dn.back();
		dn.pop_back();
	}
	pts = dn;
	#endif
}

//avoid using long double for comparisons, change type and add division by 2
type compute_signed_area(const vector<point> &p) {
	type area = 0;
	for(int i = 0; i < p.size(); i++) {
		int j = (i+1) % p.size();
		area += p[i].x*p[j].y - p[j].x*p[i].y;
	}
	return area;
}

point compute_centroid(vector<point> &p) {
	point c(0,0);
	ld scale = 3.0 * compute_signed_area(p);
	for (int i = 0; i < p.size(); i++){
			int j = (i+1) % p.size();
			c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
	}
	return c / scale;
}

bool is_ccw(vector<point> &p) {
	type area = 0;
	for(int i = 2; i < p.size(); i++) {
			area += cross(p[i] - p[0], p[i - 1] - p[0]);
	}
	return area > 0;
}

bool point_in_triangle(point a, point b, point c, point cur){
	ll s1 = abs(cross(b - a, c - a));
	ll s2 = abs(cross(a - cur, b - cur)) + abs(cross(b - cur, c - cur)) + abs(cross(c - cur, a - cur));
	return s1 == s2;
}

void sort_lex_hull(vector<point> &hull){
	if(compute_signed_area(hull) < 0) reverse(hull.begin(), hull.end());
	int n = hull.size();

	//Sort hull by x
	int pos = 0;
	for(int i = 1; i < n; i++) if(hull[i] <  hull[pos]) pos = i;
	rotate(hull.begin(), hull.begin() + pos, hull.end());
}

//determine if point is inside or on the boundary of a polygon (O(logn))
bool point_in_convex_polygon(vector<point> &hull, point cur){
	int n = hull.size();
	//Corner cases: point outside most left and most right wedges
	if(cur.dir(hull[0], hull[1]) != 0 && cur.dir(hull[0], hull[1]) != hull[n - 1].dir(hull[0], hull[1]))
		return false;
	if(cur.dir(hull[0], hull[n - 1]) != 0 && cur.dir(hull[0], hull[n - 1]) != hull[1].dir(hull[0], hull[n - 1]))
		return false;

	//Binary search to find which wedges it is between
	int l = 1, r = n - 1;
	while(r - l > 1){
		int mid = (l + r)/2;
		if(cur.dir(hull[0], hull[mid]) <= 0)l = mid;
		else r = mid;
	}
	return point_in_triangle(hull[l], hull[l + 1], hull[0], cur);
}

//Simple Polygons

// this code assumes that there are no 3 colinear points
int maximize_scalar_product(vector<point> &hull, point vec /*, int dir_flag*/) {
	/*
		For Minimize change: >= becomes <= and > becomes <
		For finding tangents, use same code passing direction flag
		dir_flag = -1 for right tangent
		dir_flag =  1 for left tangent
		>= or > becomes: == dir_flag
		< or <= becomes != dir_flag
		commentaries below for better clarification
	*/
	int ans = 0;
	int n = hull.size();
	if(n < 20) {
		for(int i = 0; i < n; i++) {
			if(hull[i] * vec > hull[ans] * vec) {
				//hull[ans].dir(vec, hull[i]) == dir_flag
				ans = i;
			}
		}
	} else {
		if(hull[1] * vec > hull[ans] * vec) {
			//hull[ans].dir(vec, hull[1]) == dir_flag
			ans = 1;
		}
		for(int rep = 0; rep < 2; rep++) {
			int l = 2, r = n - 1;
			while(l != r) {
				int mid = (l + r + 1) / 2;
				bool flag = hull[mid] * vec >= hull[mid-1] * vec;
				//(hull[ans].dir(vec, hull[l]) == dir_flag
				if(rep == 0) { flag = flag && hull[mid] * vec >= hull[0] * vec; }
				//(hull[ans].dir(vec, hull[l]) == dir_flag
				else { flag = flag || hull[mid-1] * vec < hull[0] * vec; }
				//(hull[ans].dir(vec, hull[l]) != dir_flag
				if(flag) {
					l = mid;
				} else {
					r = mid - 1;
				}
			}
			if(hull[l] * vec > hull[ans] * vec) {
				//(hull[ans].dir(vec, hull[l]) == dir_flag
				ans = l;
			}
		}
	}
	return ans;
}