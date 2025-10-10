/*
最短路：
    spfa(s); // 以 s 为起点跑最短路，dis[x] 代表 s -> x 的最短距离。

负环：
    bool ok = spfa(s); // 若有环，则 ok = false。

差分约束：
    1. 建一个超级源点 n + 1，从点 n + 1 向点 1 ~ n 都连一条边权为 0 的有向边。
    2. 对于形为 x1 - x2 <= y 的限制，从点 x2 向点 x1 连一条边权为 y 的有向边。
    3. bool ok = spfa(n + 1);
    4. 若 ok = false, 则不存在一组可行解；否则 dis[1 ~ n] 代表一组可行解 {x1, x2, ..., xn}。
*/

vector<int> dis(n + 2), num(n + 2);
vector<bool> vis(n + 2);
auto spfa = [&] (int s) {
	// x1 - x2 <= y
	// x2 -> x1  w = y
	// n + 1 -> (1 ~ n) w = 0
	dis.assign(n + 2, inf);
	vis.assign(n + 2, 0);
	num.assign(n + 2, 0);
	dis[s] = 0;
	vis[s] = true;
	priority_queue<int> q;
	q.push(s);
	num[s]++;
	while(!q.empty()) {
		int x = q.top();
		q.pop();
		vis[x] = false;
		for (auto [y, z] : adj[x]) {
			if(dis[y] > dis[x] + z) {
				dis[y] = dis[x] + z;
				if (!vis[y]) {
					vis[y] = true;
					q.push(y);
					if (++num[y] > n) {
						return false;
					}
				}
			}
		}
	}
	return true;
};
/*
if (!spfa(n + 1)) {
	cout << "NO\n";
	return ;
}
*/