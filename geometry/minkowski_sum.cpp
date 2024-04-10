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

/*
Computing the Minkowski sum of multiple polygons:
the resulting polygon will have the number of sides equal to the number of vectors in all sequences for given polygons, if we count all parallel vectors as one.
Now we can solve the problem in such a way: construct the sequences of vectors for the given polygons and divide these vectors into equivalence classes
in such a way that vectors belong to the same class if and only if they are parallel.
The answer to each query is equal to the number of equivalence classes such that at least one vector belonging to this class is contained in at least one sequence on the segment of polygons;
this can be modeled as the query "count the number of distinct values on the given segment of the given array".
*/
//cmp from radial sort
//build equivalence classes from here with resizing unique and giving id to edges
struct edge{
    point l, r;
    edge(point _l = point(), point _r = point()) : l(_l), r(_r) {}

    bool operator <(const edge& p) const{
        point u = p.r, v = r;
        return cmp(v - l, u - p.l);
    }
    //actually this operator is checking >= not ==
    bool operator ==(const edge& p) const{
        point u = p.r, v = r;
        return cmp(v - l, u - p.l) == 0;
    }
};