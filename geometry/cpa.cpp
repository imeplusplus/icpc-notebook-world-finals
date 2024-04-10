//Closest Point Approach
ld CPA(point p, point u, point q, point v){
    point w = p - q;
    if(fabs(dot(u - v, u - v)) < EPS) return LINF;
    return -dot(w, u - v)/dot(u - v, u - v);
}

pair <bool, ld> time_intersects(point p, point a, point b, point v, point u){
    ld num = (p.x - a.x)*(b.y - a.y) - (p.y - a.y)*(b.x - a.x);
    ld den = (v.x - u.x)*(b.y - a.y) - (v.y - u.y)*(b.x - a.x);
    if(eq(abs(num), 0.0) and eq(abs(u%v), 0.0)){
			if(!ge((b - a)*(u), 0)) swap(b, a);
			if(!le((p - a)*(b - a), 0)){
				if(le(u * v,  0) or !le(v.abs2(), u.abs2()))
					return{true, p.dist(b)/(u - v).abs()};
				else
					return {false, LINF};
			}
			else{
				if(ge(u * v, 0) and !le(u.abs2(), v.abs2()))
					return{true, p.dist(a)/(u - v).abs()};
				else
					return {false, LINF};
			}
    }
    if(eq(abs(den), 0)) return {false, LINF};
    ld ans = -num/den;
    if(ge(ans, 0)) return {true, ans};
    return {false, LINF};
}
//check intersection
if((p[i][j] + v[i]*t.nd).on_seg((p[i^1][0] + v[i^1]*t.nd), (p[i^1][1] + v[i^1]*t.nd))) ans = min(ans, t.nd), ok = true;
