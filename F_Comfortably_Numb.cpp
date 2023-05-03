#pragma GCC optimize("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#define rsrt(v) sort(v.begin(), v.end(), greater<int>())
#define srt(v) sort(v.begin(),v.end())
#define all(x) (x).begin(),(x).end()
#define ll long long
// #define int long long
ll md = 1000000007;
// int inf = 1e18;
using namespace std;
template <typename T>
T pw(T a, T b) {T c = 1, m = a;while(b) {if (b & 1) c=(c*m); m=(m*m); b/=2;} return c;}
template <typename T>
T ceel(T a, T b){if (a%b==0) return a/b; else return a/b + 1;}
template <typename T>
T gcd(T a, T b) {return b == 0 ? a : gcd(b, a % b);}
ll pwmd(ll a, ll b) {ll c = 1, m = a%md;while(b) {if (b & 1) c=(c*m)%md; m=(m*m)%md; b/=2;} return c;}
ll modinv(ll n){return pwmd(n, md - 2);}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l, ll r){ // gives random number in [l,r]
  return uniform_int_distribution<ll>(l, r)(rng);
}
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
  return os << '{' << p.first << ", " << p.second << '}';
}
template <class T, class = decay_t<decltype(*begin(declval<T>()))>,
          class = enable_if_t<!is_same<T, string>::value>>
ostream &operator<<(ostream &os, const T &c) {
  os << '[';
  for (auto it = c.begin(); it != c.end(); ++it)
    os << &", "[2 * (it == c.begin())] << *it;
  return os << ']';
}
//support up to 5 args
#define _NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N
#define _FE_0(_CALL, ...)
#define _FE_1(_CALL, x) _CALL(x)
#define _FE_2(_CALL, x, ...) _CALL(x) _FE_1(_CALL, __VA_ARGS__)
#define _FE_3(_CALL, x, ...) _CALL(x) _FE_2(_CALL, __VA_ARGS__)
#define _FE_4(_CALL, x, ...) _CALL(x) _FE_3(_CALL, __VA_ARGS__)
#define _FE_5(_CALL, x, ...) _CALL(x) _FE_4(_CALL, __VA_ARGS__)
#define FOR_EACH_MACRO(MACRO, ...)                                             \
  _NTH_ARG(dummy, ##__VA_ARGS__, _FE_5, _FE_4, _FE_3, _FE_2, _FE_1, _FE_0)     \
  (MACRO, ##__VA_ARGS__)
// #ifdef LOCAL
#define out(x) #x " = " << x << "; "
#define dbg(...)                                                              \
  cerr << "Line " << __LINE__ << ": " FOR_EACH_MACRO(out, __VA_ARGS__) << "\n"
// #else
// #define debug(...) 42
// #endif
//--------------------------------theartofwar-------------------------------------------//


const int M = 7e6;
int ar[M][2][2];
void in_it(int x, int e) {
	ar[x][0][e] = ar[x][1][e] = 0;
}
vector<int> cur(2), root(2);
int newnode(int e) {
	in_it(++cur[e], e);
	return cur[e];
}
void clear(int e) {
	cur[e] = 0;
}

void INSERT(int x, int e) {
	int v = root[e];
    for (int i = 29; i >= 0; i--) {
        int a = ((x & (1ll << i)) > 0);
        if (!ar[v][a][e]) ar[v][a][e] = newnode(e);
		v = ar[v][a][e];
    }
}
int check(int x, int e) {
    int ans = 0, v = root[e];
    for (int i = 29; i >= 0; i--){
        int a = ((x & (1ll << i)) > 0);
        if (ar[v][a ^ 1][e]) ans += (1ll << i), v = ar[v][a ^ 1][e];
        else v = ar[v][a][e];
    }
    return ans;
}
const int N = 2e5 + 5;
vector<int> v(N);
int go(int l, int r) {
    if (l == r) return 0;
    int mid = (l + r) / 2;
    int a = go(l, mid);
    int b = go(mid + 1, r);
    int lp = mid, rp = mid + 1, lmx = -1, rmx = -1, mx = -1, lx = 0, rx = 0;
	clear(0), clear(1);
	root[0] = newnode(0), root[1] = newnode(1);
	INSERT(0, 0), INSERT(0, 1);
    int ans = 0;
    while (lp >= l || rp <= r) {
        if (lp < l) {
            rmx = max(rmx, v[rp]), rx ^= v[rp];
            ans = max(ans, check(rx ^ rmx, 0));
            rp++;
            continue;
        }
        if (rp > r) {
            lmx = max(lmx, v[lp]), lx ^= v[lp];
            ans = max(ans, check(lx ^ lmx, 1));
            lp--;
            continue;
        }
        if (v[rp] >= v[lp]) {
            mx = v[rp];
            while (lp >= l && v[lp] <= mx) {
                lmx = max(lmx, v[lp]), lx ^= v[lp--];
                ans = max(ans, check(lmx ^ lx, 1));
                INSERT(lx, 0);
            }
            while (rp <= r && v[rp] <= mx) {
                rmx = max(rmx, v[rp]), rx ^= v[rp++];
                ans = max(ans, check(rx ^ rmx, 0));
                INSERT(rx, 1);
            }
        } else {
            mx = v[lp];
            while (rp <= r && v[rp] <= mx) {
                rmx = max(rmx, v[rp]), rx ^= v[rp++];
                ans = max(ans, check(rmx ^ rx, 0));
                INSERT(rx, 1);
            }
            while (lp >= l && v[lp] <= mx) {
                lmx = max(lmx, v[lp]), lx ^= v[lp--];
                ans = max(ans, check(lx ^ lmx, 1));
                INSERT(lx, 0);
            }
        }
    }
    dbg(l, r, a, b, ans);
    ans = max(ans, max(a, b));
    return ans;
}
signed main()
{
    ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; i++) cin >> v[i];
        cout << go(1, n) << "\n";
    }
}