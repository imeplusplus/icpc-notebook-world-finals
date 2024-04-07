#include "basics.cpp"
//DIVIDE AND CONQUER METHOD
//Warning: include variable id into the struct point

struct cmp_y {
	bool operator()(const point & a, const point & b) const {
		return a.y < b.y;
	}
};

ld min_dist = LINF;
pair<int, int> best_pair;
vector<point> pts, stripe;
int n;

void upd_ans(const point & a, const point & b) {
	ld dist = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
	if (dist < min_dist) {
		min_dist = dist;
		// best_pair = {a.id, b.id};
	}
}

void closest_pair(int l, int r) {
	if (r - l <= 3) {
		for (int i = l; i < r; ++i) {
			for (int j = i + 1; j < r; ++j) {
				upd_ans(pts[i], pts[j]);
			}
		}
		sort(pts.begin() + l, pts.begin() + r, cmp_y());
		return;
	}

	int m = (l + r) >> 1;
	type midx = pts[m].x;
	closest_pair(l, m);
	closest_pair(m, r);

	merge(pts.begin() + l, pts.begin() + m, pts.begin() + m, pts.begin() + r, stripe.begin(), cmp_y());
	copy(stripe.begin(), stripe.begin() + r - l, pts.begin() + l);

	int stripe_sz = 0;
	for (int i = l; i < r; ++i) {
		if (abs(pts[i].x - midx) < min_dist) {
			for (int j = stripe_sz - 1; j >= 0 && pts[i].y - stripe[j].y < min_dist; --j)
				upd_ans(pts[i], stripe[j]);
			stripe[stripe_sz++] = pts[i];
		}
	}
}

int main(){
	//read and save in vector pts
	min_dist = LINF;
	stripe.resize(n);
	sort(pts.begin(), pts.end());
	closest_pair(0, n);
}