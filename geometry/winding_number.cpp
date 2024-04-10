bool upward_edge(point a, point b, point c, point d){
    //Line: a - b
    //Edge: c - d
    //Edge who comes from bottom to top (or from right to left), but does not consider the final endpoint
    return (direction(a, b, c) < 1 and direction(a, b, d) == 1);
}

bool downward_edge(point a, point b, point c, point d){
    //Line: a - b
    //Edge: c - d
    //Edge who comes from top to bottom (or from left to right), but does not consider the initial endpoint
    return (direction(a, b, c) == 1 and direction(a, b, d) < 1);
}

//Crossing Number
//Check ray intersection if point aiming to the infinite hits a bound of the polygon
//Direction: Ray_a -> Ray_b
//upward and downward disconsider parallel edges to the ray
if(upward_edge(ray_a, ray_b, pts[j], pts[(j + 1)%n]) || downward_edge(ray_a, ray_b, pts[j], pts[(j + 1)%n]))
		if(segment_ray_intersect(ray_a, ray_b, pts[j], pts[(j + 1)%n]))
			crossing_number++;

//Winding Number
//Check ray intersection if point aiming to the infinite hits a bound of the polygon
//upward and downward disconsider parallel edges to the ray
if(upward_edge(ray_a, ray_b, pts[j], pts[(j + 1)%n]))
	if(segment_ray_intersect(ray_a, ray_b, pts[j], pts[(j + 1)%n]))
		winding_number++;
if(downward_edge(ray_a, ray_b, pts[j], pts[(j + 1)%n]))
	if(segment_ray_intersect(ray_a, ray_b, pts[j], pts[(j + 1)%n]))
		winding_number--;

//Check if edge is inside simple polygon (assure it is ccw using geometry/polygons.cpp)
bool check_edge(int i, int j, vector<point>& pts){
    int n = pts.size();
    int wn = 0;
    for(int k = 0; k < n; k++){
        if(k % n == i or (k + 1)%n == i) continue;
        if(upward_edge(pts[i], pts[j], pts[k % n], pts[(k + 1) % n]) or downward_edge(pts[i], pts[j], pts[k % n], pts[(k + 1) % n])){
            if(segment_ray_intersect(pts[k % n], pts[(k + 1) % n], pts[i], pts[j])){
                wn++;
            }
        }
    }
    return wn % 2;
}