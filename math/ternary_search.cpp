//Ternary Search - O(log(n))
//Max version, for minimum version just change signals
//Faster version - 300 iteratons up to 1e-6 precision
//For integers do (r - l > 3) and beware of boundaries
double ternary_search(double l, double r, int No = 300){
	// for(int i = 0; i < No; i++){
	while(r - l > EPS){
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		// if (f(m1) > f(m2))
		if (f(m1) < f(m2))
			l = m1;
		else
			r = m2;
	}
	return f(l);  
}