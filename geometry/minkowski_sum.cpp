#include "basics.cpp"
#include "polygons.cpp"

//ITA MINKOWSKI

typedef vector<point> polygon;

/*
 * Minkowski sum
	 Distance between two polygons P and Q:
		Do Minkowski(P, Q)
		Ans = min(ans, dist((0, 0), edge))
 */

polygon minkowski(polygon & A, polygon & B) {
	polygon P; point v1, v2;
	sort_lex_hull(A), sort_lex_hull(B);
	int n1 = A.size(), n2 = B.size();
	P.push_back(A[0] + B[0]);
	for(int i = 0, j = 0; i < n1 || j < n2;) {
		v1 = A[(i + 1)%n1] - A[i%n1];
		v2 = B[(j + 1)%n2] - B[j%n2];
		if (j == n2 || cross(v1, v2) > EPS) {
			P.push_back(P.back() + v1); i++;
		}
		else if (i == n1 || cross(v1, v2) < -EPS) {
			P.push_back(P.back() + v2); j++;
		}
		else {
			P.push_back(P.back() + (v1 + v2));
			i++; j++;
		}
	}
	P.pop_back();
	sort_lex_hull(P);
	return P;
}