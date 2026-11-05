// 依赖 Geometry_Rabbit_Base.cpp。
// 返回三角形二倍面积的最小值和最大值。
// 点集形成的最小最大三角形
// 极角序扫描线，复杂度 O(n^2logn)
// 最大三角形问题可以使用凸包与旋转卡壳做到 O(n^2)
pair<T,T> minmax_triangle(const vector<Point> &vec)
{
    if (vec.size()<=2) return {0,0};
    vector<array<int,2>> evt;
    evt.reserve(vec.size()*vec.size());
    T maxans=0,minans=INF;
    for (int i=0;i<vec.size();i++)
    {
        for (int j=0;j<vec.size();j++)
        {
            if (i==j) continue;
            if (vec[i].x==vec[j].x && vec[i].y==vec[j].y) minans=0;
            else evt.push_back({i,j});
        }
    }
    sort(evt.begin(),evt.end(),[&](const array<int,2> &u,const array<int,2> &v)
    {
        const Point du=vec[u[1]]-vec[u[0]],dv=vec[v[1]]-vec[v[0]];
        if ((du^dv)==0 && du.quad()==dv.quad()) return du.x?abs(du.x)>abs(dv.x):abs(du.y)>abs(dv.y);
        return Argcmp()({du.y,-du.x},{dv.y,-dv.x});
    });
    vector<size_t> vx(vec.size()),pos(vec.size());
    for (size_t i=0;i<vec.size();i++) vx[i]=i;
    sort(vx.begin(),vx.end(),[&](int x,int y){return vec[x]<vec[y];});
    for (size_t i=0;i<vx.size();i++) pos[vx[i]]=i;
    for (auto [u,v]:evt)
    {
        const size_t i=pos[u],j=pos[v];
        const size_t l=min(i,j),r=max(i,j);
        const Point vecu=vec[u],vecv=vec[v];
        if (l>0) minans=min(minans,abs((vec[vx[l-1]]-vecu)^(vec[vx[l-1]]-vecv)));
        if (r<vx.size()-1) minans=min(minans,abs((vec[vx[r+1]]-vecu)^(vec[vx[r+1]]-vecv)));
        maxans=max({maxans,abs((vec[vx[0]]-vecu)^(vec[vx[0]]-vecv)),abs((vec[vx.back()]-vecu)^(vec[vx.back()]-vecv))});
        if (i<j) swap(vx[i],vx[j]),pos[u]=j,pos[v]=i;
    }
    return {minans,maxans};
}

