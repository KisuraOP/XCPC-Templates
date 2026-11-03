// 依赖 Geometry_Rabbit_Circle.cpp。
// 圆面积并
// 轮廓积分，复杂度 O(n^2logn)
// ans[i] 表示被至少覆盖了 i+1 次的区域的面积
vector<T> area_union(vector<Circle> circs)
{
    Point o=circs.empty()?Point{}:circs[0].c;
    for (const auto &c:circs)
    {
        if (abs(c.c.x-o.x)>=abs(o.x)/2) o.x=0;
        if (abs(c.c.y-o.y)>=abs(o.y)/2) o.y=0;
    }
    for (auto &c:circs) c.c=c.c-o;
    const size_t siz=circs.size();
    using arc_t=tuple<Point,T,T,T,Point,Point>;
    vector<vector<arc_t>> arcs(siz);
    const auto eq=[](const arc_t &u,const arc_t &v)
    {
        const auto [u1,u2,u3,u4,u5,u6]=u;
        const auto [v1,v2,v3,v4,v5,v6]=v;
        return u1==v1 && abs(u2-v2)<=eps && u3==v3 && u4==v4;
    };

    auto cut_circ=[&](const Circle &ci,const size_t i)
    {
        vector<tuple<T,int,Point>> evt;
        const Point p={ci.c.x-ci.r,ci.c.y};
        evt.push_back({-PI,0,p}); evt.push_back({PI,0,p});
        int init=0;
        for (size_t j=0;j<circs.size();j++)
        {
            if (i==j) continue;
            const Circle &cj=circs[j];
            const T d=ci.c.dis(cj.c);
            const int t=d>=ci.r+cj.r?0:d<=abs(ci.r-cj.r)?4:2;
            if (ci.r<cj.r && t==4) init++;
            const bool rev=tie(ci.c.x,ci.c.y,ci.r)>tie(cj.c.x,cj.c.y,cj.r);
            auto inters=rev?cj.inter(ci,t):ci.inter(cj,t);
            if (rev) reverse(inters.begin(),inters.end());
            if (inters.size()==1) evt.push_back({atan2l((inters[0]-ci.c).y,(inters[0]-ci.c).x),0,inters[0]});
            if (inters.size()==2)
            {
                const Point dl=inters[0]-ci.c,dr=inters[1]-ci.c;
                T argl=atan2l(dl.y,dl.x),argr=atan2l(dr.y,dr.x);
                if (argl==-PI) argl=PI;
                if (argr==-PI) argr=PI;
                if (argl>argr)
                {
                    evt.push_back({argl,1,inters[0]}); evt.push_back({PI,-1,p});
                    evt.push_back({-PI,1,p}); evt.push_back({argr,-1,inters[1]});
                }
                else
                {
                    evt.push_back({argl,1,inters[0]});
                    evt.push_back({argr,-1,inters[1]});
                }
            }
        }
        sort(evt.begin(),evt.end(),[](const auto &a,const auto &b){return get<0>(a)<get<0>(b);});
        int sum=init;
        for (size_t i=0;i<evt.size();i++)
        {
            const auto [l,t,p]=evt[i];
            const auto [r,v,q]=evt[i+1];
            sum+=t;
            if (l<r) arcs[sum].push_back({ci.c,ci.r,l,r,p,q});
            if (r==PI) break;
        }
    };

    const auto oint=[](const arc_t &arc,const Point &o)
    {
        const auto [cc,cr,l,r,p,q]=arc;
        const Point a=p-cc,b=q-cc;
        T t=atan2l(a^b,a*b);
        if (t<0 || (t==0 && r-l>PI)) t+=2*PI;
        const T z=t*t,d=t<.01l?t*z*(1.0l/6-z*(1.0l/120-z/5040)):t-sin(t);
        return make_pair((p-q)^(q-o),cr*cr*d);
    };

    for (size_t i=0;i<circs.size();i++)
    {
        const auto &ci=circs[i];
        cut_circ(ci,i);
    }
    vector<T> ans(siz);
    for (size_t i=0;i<siz;i++)
    {
        T sum=0,seg=0;
        const Point o=arcs[i].empty()?Point{}:get<4>(arcs[i][0]);
        sort(arcs[i].begin(),arcs[i].end());
        int cnt=0;
        for (size_t j=0;j<arcs[i].size();j++)
        {
            if (j>0 && eq(arcs[i][j],arcs[i][j-1])) arcs[i+(++cnt)].push_back(arcs[i][j]);
            else {cnt=0;const auto [a,b]=oint(arcs[i][j],o);sum+=a;seg+=b;}
        }
        ans[i]=(sum+seg)/2;
    }
    return ans;
}

