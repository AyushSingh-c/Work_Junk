#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace __gnu_pbds;
using namespace std;
 
typedef long long int ll;
typedef unsigned long long int sll;
typedef long double ld;
typedef complex<ll> cll;
typedef complex<ld> cld;

// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
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
#define sorrev(v) sort(v.begin(),v.end(),greater<pll>())
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

int main() 
{
    FAST;

    ll n;
    cin>>n;
    cout<<10*n;


    subt;       

    return 0;
}
