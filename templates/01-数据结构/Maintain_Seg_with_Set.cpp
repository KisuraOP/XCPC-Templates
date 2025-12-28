struct Seg {
	int l, r;
	bool operator<(const Seg &other) const {
		return r < other.l;
	}
};
struct segSet {
	set<Seg> s;
	void insert(int l, int r) {
		if (l > r) {
			return ;
		}
		Seg seg = {l, r};
		for (auto it = s.find(seg); it != s.end(); it = s.find(seg)) {
			seg.l = min(seg.l, it->l);
			seg.r = max(seg.r, it->r);
			s.erase(it);
		}
		s.insert(seg);
	}
};