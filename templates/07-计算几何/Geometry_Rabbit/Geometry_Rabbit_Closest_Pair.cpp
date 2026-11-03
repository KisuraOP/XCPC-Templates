// 依赖 Geometry_Rabbit_Base.cpp。
// 平面最近点对
// 扫描线，复杂度 O(nlogn)
T closest_pair(vector<Point> points)
{
    sort(points.begin(),points.end());
    const auto cmpy=[](const Point &a,const Point &b){return a.y!=b.y?a.y<b.y:a.x<b.x;};
    multiset<Point,decltype(cmpy)> s{cmpy};
    T ans=INF;
    for (size_t i=0,l=0;i<points.size();i++)
    {
        const T sqans=sqrtl(ans);
        while (l<i && points[i].x-points[l].x>=sqans) s.erase(s.find(points[l++]));
        for (auto it=s.lower_bound(Point{-INF,points[i].y-sqans});it!=s.end()&&it->y-points[i].y<=sqans;it++)
        {
            ans=min(ans,points[i].dis2(*it));
        }
        s.insert(points[i]);
    }
    return ans;
}

