#include "Headers/Logic.h"
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace __gnu_pbds;
using namespace std;
 
typedef long long int ll;
typedef unsigned long long int sll;
typedef long double ld;
typedef complex<ll> cll;
typedef complex<ld> cld;

#define re real
#define im imag
#define A 1000000007ll
#define D -100000000000000ll
#define B 998244353ll
#define C 1000000000000000000ll
#define E 500000002ll
#define M 1000000006ll
#define H 900000002599ll
#define F first
#define S second
#define pq priority_queue
#define pll pair<ll,ll>
#define ppll pair<ll,pair<ll,ll>>
#define FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define oset tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update> 
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define mxe(v) *max_element(v.begin(),v.end())
#define mne(v) *min_element(v.begin(),v.end())
#define rev(v) reverse(v.begin(),v.end())
#define sor(v) sort(v.begin(),v.end())
#define sorrev(v) sort(v.begin(),v.end(),greater<ll>())
#define uni(v) unique(v.begin(),v.end())
#define bs binary_search
#define lb lower_bound
#define ub upper_bound
#define ve vector
#define br break
#define PI acos(-1)
#define subt cerr << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC << "ms\n" 
const ll MAXN=100005; 
auto random_address = [] { char *p = new char; delete p; return sll(p); };
const sll SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);

void Logic::Logic_01()
{
    freopen("files/input_1.txt", "r", stdin);
    freopen("files/output_1.txt", "w", stdout);

    ve<int> cal;
    while(1)
    {
        int sum=0;
        while(1)
        {
            string n;
            getline(cin, n);
            if(n.length()==0)
                break;
            else
                sum+=stoi(n);
        }
        cal.pb(sum);
        if(sum==0)
            break;
    }
    sorrev(cal);

    cout<<"Max calories: "<<cal[0]<<'\n';
    cout<<"Top three calories sum: "<<cal[0]+cal[1]+cal[2]<<'\n';
}

void Logic::Logic_02()
{
    freopen("files/input_2.txt", "r", stdin);
    freopen("files/output_2.txt", "w", stdout);

    map<string, int> gameScore;

    // For first problem

    // gameScore["A X"] = 4;
    // gameScore["A Y"] = 8;
    // gameScore["A Z"] = 3;
    // gameScore["B X"] = 1;
    // gameScore["B Y"] = 5;
    // gameScore["B Z"] = 9;
    // gameScore["C X"] = 7;
    // gameScore["C Y"] = 2;
    // gameScore["C Z"] = 6;

    //For second problem

    gameScore["A X"] = 3;
    gameScore["A Y"] = 4;
    gameScore["A Z"] = 8;
    gameScore["B X"] = 1;
    gameScore["B Y"] = 5;
    gameScore["B Z"] = 9;
    gameScore["C X"] = 2;
    gameScore["C Y"] = 6;
    gameScore["C Z"] = 7;

    int totalScore = 0;
    string s;
    while(getline(cin,s))
        totalScore += gameScore[s];
    cout<<"Total Score: "<<totalScore<<'\n';
}

void Logic::Logic_03()
{
    freopen("files/input_3.txt", "r", stdin);
    freopen("files/output_3.txt", "w", stdout);

    string packing;
    int totalScore=0;

    //For first problem

    // while(cin>>packing)
    // {
    //     int packLen = packing.length();
    //     map<char, bool> itemPresent;
    //     for(int i=0;2*i<packLen;i++)
    //         itemPresent[packing[i]] = true;
    //     for(int i=packLen/2;i<packLen;i++)
    //         if(itemPresent[packing[i]])
    //         {
    //             int score = packing[i]-'a';
    //             if(score<0)
    //                 score = (packing[i]-'A')+26;
    //             totalScore += score+1;
    //             break;
    //         }
    // }

    //For second problem

    while(cin>>packing)
    {
        map<char, int> itemPresent;
        int packLen = packing.length(); 
        for(int i=0;i<packLen;i++)
            itemPresent[packing[i]]=1;
        
        cin>>packing;
        packLen = packing.length(); 
        for(int i=0;i<packLen;i++)
            if(itemPresent[packing[i]] == 1)
                itemPresent[packing[i]]=2;
        
        cin>>packing;
        packLen = packing.length(); 
        for(int i=0;i<packLen;i++)
            if(itemPresent[packing[i]] == 2)
            {
                int score = packing[i]-'a';
                if(score<0)
                    score = (packing[i]-'A')+26;
                totalScore += score+1;
                break;
            }
    }

    cout<<"Final Score: "<<totalScore;
}

void Logic::Logic_04()
{
    freopen("files/input_4.txt", "r", stdin);
    freopen("files/output_4.txt", "w", stdout);

    string ranges;
    int overlapCount = 0, subsetCount = 0;

    while(cin>>ranges)
    {
        int l1,r1,l2,r2;
        string temp;

        int inputLength = ranges.length(), index = 0;
        while(ranges[index] != '-')
            temp.pb(ranges[index++]); 
        l1 = stoi(temp);
        temp = "";

        index++;
        while(ranges[index] != ',')
            temp.pb(ranges[index++]); 
        r1 = stoi(temp);
        temp = "";

        index++;
        while(ranges[index] != '-')
            temp.pb(ranges[index++]); 
        l2 = stoi(temp);
        temp = "";

        index++;
        while(index < inputLength)
            temp.pb(ranges[index++]); 
        r2 = stoi(temp);
        temp = "";

        if((l1<=l2 && r1>=r2) || (l1>=l2 && r1<=r2))
            subsetCount++;
        if(!(l1>r2 || r1<l2))
            overlapCount++;
    }

    cout<<"Number of subset: "<<subsetCount<<'\n';
    cout<<"Number of overlap: "<<overlapCount<<'\n';
}

void Logic::Logic_05()
{

}

void Logic::Logic_11()
{

}

void Logic::Logic_12()
{
    freopen("files/input_12.txt", "r", stdin);
    freopen("files/output_12.txt", "w", stdout);

    ll rows=41, columes=0;
    ve<string> matrix(rows);
    
    for(int i=0;i<rows;i++)
        cin>>matrix[i];

    columes = matrix[0].length();
    ve<ve<ll>> minStepDP(rows, ve<ll>(columes,A));
    deque<pll> visitStack;

    int startX=0, startY=0, endX=0, endY=0;

    for(int i=0;i<rows;i++)
        for(int j=0;j<columes;j++)
        {
            //For First Part
            
            // if(matrix[i][j] == 'S')
            // {
            //     matrix[i][j] = 'a';
            //     minStepDP[i][j] = 0;
            //     startX = i;
            //     startY = j;
            //     visitStack.pb({i,j});
            // }

            //For Second Part

            if(matrix[i][j] == 'a' || matrix[i][j] == 'S')
            {
                minStepDP[i][j] = 0;
                matrix[i][j] = 'a';
                visitStack.pb({i,j});
            }
            if(matrix[i][j] == 'E')
            {
                matrix[i][j] = 'z';
                endX = i;
                endY = j;
            }
        }

    while(!visitStack.empty())
    {
        int x = visitStack.front().first, y = visitStack.front().second;
        visitStack.pop_front();
        if(x+1<rows && matrix[x+1][y]-matrix[x][y]<=1 && minStepDP[x+1][y]>minStepDP[x][y]+1 )
        {
            minStepDP[x+1][y] = minStepDP[x][y] + 1;
            visitStack.pb({x+1,y});
        }
        if(y+1<columes && matrix[x][y+1]-matrix[x][y]<=1 && minStepDP[x][y+1]>minStepDP[x][y]+1)
        {
            minStepDP[x][y+1] = minStepDP[x][y] + 1;
            visitStack.pb({x,y+1});
        }
        if(x-1>=0 && matrix[x-1][y]-matrix[x][y]<=1 && minStepDP[x-1][y]>minStepDP[x][y]+1)
        {
            minStepDP[x-1][y] = minStepDP[x][y] + 1;
            visitStack.pb({x-1,y});
        }
        if(y-1>=0 && matrix[x][y-1]-matrix[x][y]<=1 && minStepDP[x][y-1]>minStepDP[x][y]+1)
        {
            minStepDP[x][y-1] = minStepDP[x][y] + 1;
            visitStack.pb({x,y-1});
        }
    }
    cout<<minStepDP[endX][endY]<<'\n'; 
}

struct Node {
    ll v;
    ve<Node*> c;
};

ll comp(Node *a, Node *b)
{
    ll n = ((*a).c).size(), m = ((*b).c).size(), in=0;
    if(n==0 && m==0)
    {
        if(a->v > b->v)
            return 0;
        if(a->v == b->v)
            return 1;
        return 2;
    }
    else if(n!=0 && m!=0)
    {
        while(in<n && in<m)
        {
            ll temp = comp((a->c)[in], (b->c)[in]);
            if(temp == 0)
                return 0;
            if(temp == 2)
                return 2;
            in++;
        }
        if(in != n && in == m)
            return 0;
        if(n == m)
            return 1;
        return 2;
    }
    else
    {
        ll temp = 0;
        if(n!=0 && m==0)
        {
            temp = comp((a->c)[0], b);
            if(temp == 1 && n>1)
                temp = 0;
        }
        else
        {
            temp = comp(a, (b->c)[0]);
            if(temp == 1 && m>1)
                temp = 2; 
        }
        return temp;
    }
}

Node* constr(string &s, ll &pos)
{
    Node* a = new Node();
    (*a).v = -1;
    if(s[pos] == ',')
    {
        return NULL;
    }
    else if(s[pos] == '[')
    {
        while(pos<s.length() && s[pos] != ']')
        {
            Node* temp = constr(s, ++pos);
            if(temp != NULL)
                (*a).c.pb(temp);
        }
        pos++;
        return a;
    }
    else if(s[pos] == ']')
    {
        return NULL; 
    }
    else
    {
        string num;
        while(s[pos]!=',' && s[pos]!='[' && s[pos]!=']')
        {
            num.pb(s[pos]);
            pos++;
        }
        (*a).v = stoi(num);
        return a;
    }
}

bool compstr(string s1, string s2)
{
    ll p1=0,p2=0;
    return comp(constr(s1, p1), constr(s2, p2));
}

void Logic::Logic_13()
{
    freopen("files/input_13.txt", "r", stdin);
    freopen("files/output_13.txt", "w", stdout);

    ll ans=0, co=0;
    // For first part

    // string s1,s2;
    // while(cin>>s1)
    // {
    //     cin>>s2;
    //     co++;
    //     ll p1=0, p2=0;
    //     if(compstr(s1,s2))
    //         ans+=co;
    // }

    // for second part
    string s;
    ve<string> cm;
    
    while(cin>>s)
        cm.pb(s);
    cm.pb("[[2]]");
    cm.pb("[[6]]");

    sort(cm.begin(), cm.end(), compstr);

    for(int i=0;i<cm.size();i++)
    {
        if(cm[i] == "[[2]]")
            ans=i+1;
        if(cm[i] == "[[6]]")
            ans*=i+1;
    }
    cout<<ans<<'\n';
}

bool check(char c)
{
    return ((c-'0')<10 && (c-'0')>=0) || c=='-';
}

void Logic::Logic_14()
{
    freopen("files/input_14.txt", "r", stdin);
    freopen("files/output_14.txt", "w", stdout);

    ll n=910, m=910, ma=0;
    ve<ve<ll>> a(n, ve<ll>(m,0));
    ve<ve<bool>> fun(n,ve<bool>(m,false));
    string s;

    while(getline(cin,s))
    {
        ve<pll> wtf;
        ll in=0;
        while(in<s.length())
        {
            pll dwtf;
            string temp;
            while(in<s.length() && check(s[in]))
                temp.pb(s[in++]);
            while(in<s.length() && !check(s[in]))
                in++;

            dwtf.S = stoi(temp);

            temp = "";
            while(in<s.length() && check(s[in]))
                temp.pb(s[in++]);
            while(in<s.length() && !check(s[in]))
                in++;

            dwtf.F = stoi(temp);
            ma=max(ma,dwtf.F);
            wtf.pb(dwtf);
        }
        ll xx=wtf[0].F, yy = wtf[0].S;
        for(auto i:wtf)
        {
            ll x=i.F, y=i.S;
            if(x==xx)
            {
                if(y>yy)
                    for(ll i=yy;i<=y;i++)
                    {
                        a[x][i] = -1;
                        fun[x][i] = true;
                    }
                else
                    for(ll i=yy;i>=y;i--)
                    {
                        a[x][i] = -1;
                        fun[x][i] = true;
                    }
            }
            else
            {
                if(x>xx)
                    for(ll i=xx;i<=x;i++)
                    {
                        a[i][y] = -1;
                        fun[i][y] = true;
                    }
                else
                    for(ll i=xx;i>=x;i--)
                    {
                        a[i][y] = -1;
                        fun[i][y] = true;
                    }             
            }
            xx=x;
            yy=y;
        }
    }

    a[0][500] = 1;

    ma+=2;
    for(ll i=0;i<m;i++)
    {
        fun[ma][i] = true;
        a[ma][i] = -1;
    }

    for(ll i=n-2;i>=0;i--)
        for(ll j=1;j<n-1;j++)
            if(fun[i+1][j] && fun[i+1][j-1] && fun[i+1][j+1])
                fun[i][j] = true;

    for(ll i=1;i<n-1;i++)
        for(ll j=1;j<n-1;j++)
            if(a[i][j] == 0 && ((a[i-1][j] == 1) || (j!=1 && a[i-1][j-1] == 1 && fun[i][j-1] && fun[i][j-2]) || (a[i-1][j+1] == 1 && fun[i][j+1])))
                a[i][j] = 1;
    ll ans=0;
    for(ll i=0;i<n;i++)
        for(ll j=0;j<m;j++)
            if(a[i][j] == 1 && fun[i][j])
                ans++;

    for(ll i=0;i<12;i++)
    {
        for(ll j=490;j<510;j++)
        {
            if(a[i][j] == -1)
                cout<<"# ";
            else if(a[i][j] == 1 && fun[i][j])
                cout<<"o ";
            else
                cout<<". "; 
        }
        cout<<'\n';
    }
    
    cout<<ma<<' '<<ans<<'\n';
}

void Logic::Logic_15()
{
    freopen("files/input_15.txt", "r", stdin);
    freopen("files/output_15.txt", "w", stdout);

    ll nn=23, yvv=2000000;
    ve<ve<ll>> pos(nn,ve<ll>(4,0));
    ve<ll> dis(nn,0);
    for(ll j=0;j<nn;j++)
    {
        string s;
        getline(cin, s);
        ll in=0;
        for(ll i=0;i<4;i++)
        {
            while(in<s.length() && !check(s[in]))
                in++;
            string temp; 
            while(in<s.length() && check(s[in]))
                temp.pb(s[in++]);
            pos[j][i] = stoi(temp);
        }
        dis[j] = abs(pos[j][0]-pos[j][2]) + abs(pos[j][1]-pos[j][3]);
        ll py = 2573243ll, px = 3257428ll;
        cout<<dis[j] - (abs(px-pos[j][0]) + abs(py-pos[j][1]))<<'\n';
    }   

    // for(ll j=0;j<=4000000;j++)
    // {
    //     ve<pll> npos;
    //     for(ll i=0;i<nn;i++)
    //     {
    //         ll a = pos[i][0], b = dis[i]-abs(pos[i][1]-j);
    //         if(b>=0)
    //             npos.pb({(ll)max(0ll,a-b), (ll)min(4000000ll,a+b)});
    //     }
    //     sor(npos);
    //     ll ans=0;
    //     pll r = npos[0];
    //     for(auto i:npos)
    //     {
    //         if(r.S+1<i.F)
    //         {
    //             ans+=r.S-r.F+1;
    //             if(j == 2573243)
    //                 cout<<r.F<<' '<<r.S<<'\n';
    //             // set<ll> sss;
    //             // for(ll pp=0;pp<nn;pp++)
    //             //     if(pos[pp][2]<=r.S && pos[pp][2]>=r.F && pos[pp][3]==j)
    //             //         sss.insert(pos[pp][2]);
    //             // ans-=sss.size();
    //             r=i;
    //         }
    //         else    
    //             r = {r.F,max(r.S,i.S)};
    //     }
    //     ans+=r.S-r.F+1;
    //     // set<ll> sss;
    //     // for(ll pp=0;pp<nn;pp++)
    //     //     if(pos[pp][2]<=r.S && pos[pp][2]>=r.F && pos[pp][3]==j)
    //     //         sss.insert(pos[pp][2]);
    //     // ans-=sss.size();
    //     if(ans<4000001)
    //     {
    //         cout<<j<<' '<<ans<<' '<<r.F<<' '<<r.S<<'\n';
    //     }
    // }
    // x= 2573243; y=3257428
    cout<<(3257428ll*4000000ll) + 2573243ll;

    // cout<<ans;
}

void Logic::Logic_16()
{
    freopen("files/input_16.txt", "r", stdin);
    freopen("files/output_16.txt", "w", stdout);

    ve<string> st(54); 
    map<pair<char,char>,ll> mp;
    ve<ll> flo(54,0);
    ve<ve<ll>> gra(54);

    for(ll i=0;i<54;i++)
        getline(cin, st[i]);
    for(ll i=0;i<54;i++)
        mp[{(st[i][6]), (st[i][7])}] = i;
    for(ll i=0;i<54;i++)
    {
        string temp;
        ll in=23;
        while(in<st[i].length() && check(st[i][in]))
            temp.pb(st[i][in++]);
        flo[i] = stoi(temp);
        while(in<st[i].length())
        {
            temp="";
            while(in<st[i].length() && !isupper(st[i][in]))
                in++;
            while(in<st[i].length() && isupper(st[i][in]))
                temp.pb(st[i][in++]);
            // cout<<temp<<' ';
            gra[i].pb(mp[{temp[0], temp[1]}]);
        }
        // cout<<'\n';
    }
    ve<ve<ll>> dis(54,ve<ll>(54,0));
    for(ll j=0;j<54;j++)
    {
        ve<bool> vis(54,false);
        deque<pll> d;
        d.pb({j,0});
        while(!d.empty())
        {
            pll x=d.front();
            vis[x.F]=1;
            dis[j][x.F]=x.S;
            d.pop_front();
            for(auto i:gra[x.F])
                if(!vis[i])
                    d.pb({i, dis[j][x.F]+1});   
        }
    }
    for(ll i=0;i<54;i++)
        if(flo[i]!=0)
            cout<<i<<' '<<dis[3][i]<<' '<<flo[i]<<'\n';

}