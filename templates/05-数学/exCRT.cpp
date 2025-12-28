/*
CRT t;
构建。

t.add(a, m); 
添加一条如上限制，即 x \equiv a \pmod{m}。

int ans = t.calc(); 
返回答案。
*/
int Lcm(int x, int y) {
	return x / __gcd(x, y) * y;
}
int exgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1;
		y = 0;
		return 0;
	}
	exgcd(b, a % b, y, x);
	y -= x * (a / b);
	return (x % b + b) % b;
}
int inv(int x, int m) {
	int t1, t2;
	return exgcd(x, m, t1, t2);
}

struct CRT {
	int n = -1;
	int A = 0, M = 0;
	vector<int> a, m;

	bool merge(int x, int y) {
		M = Lcm(m[x], m[y]);
		int d = __gcd(m[x], m[y]);
		int t1, t2;
		if ((a[y] - a[x]) % d) {
			A = inf;
			return false;
		}
		A = ((a[y] - a[x]) % m[y] + m[y]) % m[y] / d;
		A = (A * inv(m[x] / d, m[y] / d) % m[y] + m[y]) % m[y];
		A = (A * m[x] + a[x]);
		A = (A % M + M) % M;
		a[y] = A;
		m[y] = M;
		return true;
	}
	void add(int x, int P) {
		n++;
		a.push_back(x);
		m.push_back(P);
		if (n > 0 && A != inf) {
			merge(n - 1, n);
		}
	}
	int calc() {
		return A;
	}
};