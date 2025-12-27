constexpr int P1 = 1e9 + 7;
constexpr int P2 = 1e9 + 9;
constexpr int B1_x = 313;
constexpr int B1_y = 373;
constexpr int B2_x = 331;
constexpr int B2_y = 401;
struct Hash_2D {
	vector<int> p1x, p1y;
	vector<int> p2x, p2y;
	vector<vector<int>> H1, H2; 
	int Add(int a, int b, int mod) {
		return (a + b) % mod;
	}
	int Sub(int a, int b, int mod) {
		return (a - b + mod) % mod;
	}
	int Mul(int a, int b, int mod) {
		return a * b % mod;
	}
	
	int n, m;
	Hash_2D(const vector<vector<int>> &a) { 
		// {a} is 0-index
		n = a.size();
		m = a[0].size();
		init(a);
	}
	void init(const vector<vector<int>> &a) {
		p1x.resize(m + 1);
		p1y.resize(n + 1);
		p2x.resize(m + 1);
		p2y.resize(n + 1);
		p1x[0] = 1;
		p1y[0] = 1;
		p2x[0] = 1;
		p2y[0] = 1;
		for (int i = 1; i <= m; i++) {
			p1x[i] = Mul(p1x[i - 1], B1_x, P1);
			p2x[i] = Mul(p2x[i - 1], B2_x, P2);
		}
		for (int i = 1; i <= n; i++) {
			p1y[i] = Mul(p1y[i - 1], B1_y, P1);
			p2y[i] = Mul(p2y[i - 1], B2_y, P2);
		}
		vector h1(n + 1, vector<int>(m + 1)), h2(h1);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				h1[i][j] = Add(Mul(h1[i][j - 1], B1_x, P1), a[i - 1][j - 1] + 1, P1);
				h2[i][j] = Add(Mul(h2[i][j - 1], B2_x, P2), a[i - 1][j - 1] + 1, P2);
			}
		}
		H1.assign(n + 1, vector<int>(m + 1, 0));
		H2.assign(n + 1, vector<int>(m + 1, 0));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				H1[i][j] = Add(Mul(H1[i - 1][j], B1_y, P1), h1[i][j], P1);
				H2[i][j] = Add(Mul(H2[i - 1][j], B2_y, P2), h2[i][j], P2);
			}
		}
	}
	array<int, 2> get_hash(int r1, int c1, int r2, int c2) {
		// r1, c1, r2, c2 is 1-index
		int h = r2 - r1 + 1;
		int w = c2 - c1 + 1;
		int X1 = Sub(H1[r2][c2], Mul(H1[r1 - 1][c2], p1y[h], P1), P1);
		int Y1 = Sub(H1[r2][c1 - 1], Mul(H1[r1 - 1][c1 - 1], p1y[h], P1), P1);
		int hash1 = Sub(X1, Mul(Y1, p1x[w], P1), P1);
		int X2 = Sub(H2[r2][c2], Mul(H2[r1 - 1][c2], p2y[h], P2), P2);
		int Y2 = Sub(H2[r2][c1 - 1], Mul(H2[r1 - 1][c1 - 1], p2y[h], P2), P2);
		int hash2 = Sub(X2, Mul(Y2, p2x[w], P2), P2);
		return {hash1, hash2};
	}
};