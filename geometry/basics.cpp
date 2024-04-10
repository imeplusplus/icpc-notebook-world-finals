const long double EPS = 1e-9;

typedef long double type;
//for big coordinates change to long long

bool ge(type x, type y) { return x + EPS > y; }
bool le(type x, type y) { return x - EPS < y; }
bool eq(type x, type y) { return ge(x, y) and le(x, y); }
int sign(type x) { return ge(x, 0) - le(x, 0); }

struct point {
	type x, y;

	point() : x(0), y(0) {}
	point(type _x, type _y) : x(_x), y(_y) {}

	point operator -() { return point(-x, -y); }
	point operator +(point p) { return point(x + p.x, y + p.y); }
	point operator -(point p) { return point(x - p.x, y - p.y); }
	point operator *(type k) { return point(x*k, y*k); }
	point operator /(type k) { return point(x/k, y/k); }
	type operator *(point p) { return x*p.x + y*p.y; }
	type operator %(point p) { return x*p.y - y*p.x; }
	bool operator ==(const point &p) const{ return x == p.x and y == p.y; }
	bool operator !=(const point &p) const{ return x != p.x  or y != p.y; }
	bool operator <(const point &p) const { return (x < p.x) or (x == p.x and y < p.y); }
	// 0 => same direction
	// 1 => p is on the left 
	//-1 => p is on the right    
	int dir(point o, point p) {
		type x = (*this - o) % (p - o);
		return ge(x,0) - le(x,0);
	}

	bool on_seg(point p, point q) {
		if (this->dir(p, q)) return 0;
		return ge(x, min(p.x, q.x)) and le(x, max(p.x, q.x)) and ge(y, min(p.y, q.y)) and le(y, max(p.y, q.y));
	}
	//rotation: cos * x - sin * y, sin * x + cos * y
};
int direction(point o, point p, point q) { return p.dir(o, q); }
point rotate_ccw90(point p)   { return point(-p.y,p.x); }
point rotate_cw90(point p)    { return point(p.y,-p.x); }

//double area
type area_2(point a, point b, point c) { return cross(a,b) + cross(b,c) + cross(c,a); }

//angle between (a1 and b1) vs angle between (a2 and b2)
//1  : bigger
//-1 : smaller
//0  : equal
int angle_less(const point& a1, const point& b1, const point& a2, const point& b2) {
	point p1(dot(   a1, b1), abs(cross(   a1, b1)));
	point p2(dot(   a2, b2), abs(cross(   a2, b2)));
	if(cross(p1, p2) < 0) return 1;
	if(cross(p1, p2) > 0) return -1;
	return 0;
}

ostream &operator<<(ostream &os, const point &p) {
	os << "(" << p.x << "," << p.y << ")"; 
	return os;
}