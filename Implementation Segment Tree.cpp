#include <bits/stdc++.h>
using namespace std;
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(a)   a.begin(),a.end()
#define rev(a)   reverse(all(a))
#define reva(a,n) reverse(a,a+n)
#define MOD 1000000007

typedef long long ll;
typedef pair<ll, ll> pl;
typedef vector<ll>  vl;
typedef vector<vl> vvl;
typedef vector<pl> vpl;
const long double PI = 3.1415926535897932384626433832795;

class SegTemplate
{
    vector<vector<ll>>seg;
    vector<ll>lazy;
public:
    SegTemplate(int n, int k)
    {
        seg.resize(4 * n + 1, vector<ll>(k, 0));
        lazy.resize(4 * n + 1, 0);
    }
    void print(int i, int k)
    {
        for (int j = 0; j < k; j++)
        {
            cout << seg[i][j] << " ";
        }
        cout << '\n';
    }
    void PrevUpdate(int idx, int low, int high, int l, int r, int k)
    {
        // update the prev update
        if (lazy[idx] != 0)
        {
            int temp[k] = {0};
            for (int i = 0; i < k; i++)
            {
                if (seg[idx][i] == 0)
                    continue;
                if (i + lazy[idx] < k)
                {
                    temp[i + lazy[idx]] += seg[idx][i];
                    seg[idx][i] = 0;
                }
                else
                {
                    int id = (i + lazy[idx]) % k;
                    temp[id] += seg[idx][i];
                    seg[idx][i] = 0;
                }
            }
            for (int i = 0; i < k; i++)
            {
                seg[idx][i] += temp[i];
            }
            // propagate downwards
            if (low != high)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }
    void build(int idx, int low, int high, ll arr[], int k)
    {
        if (low == high)
        {
            seg[idx][arr[low]]++;
            return; // return
        }
        int mid = (low + high) / 2;
        build(2 * idx + 1, low, mid, arr, k);
        build(2 * idx + 2, mid + 1, high, arr, k);

        for (int i = 0; i < k; i++)
        {
            seg[idx][i] = seg[2 * idx + 1][i];
            seg[idx][i] += seg[2 * idx + 2][i];
        }
    }
    void update(int idx, int low, int high, int l, int r, ll val, int k)
    {

        PrevUpdate(idx, low, high, l, r, k);
        // no overlap
        if (high<l or low>r)
        {
            return;
        }

        // complete overlap
        if (low >= l and high <= r)
        {
            int temp[k] = {0};
            for (int i = 0; i < k; i++)
            {
                if (i + val < k)
                {
                    temp[i + val] += seg[idx][i];
                    seg[idx][i] = 0;
                }
                else
                {
                    int id = (i + val) % k;
                    temp[id] += seg[idx][i];
                    seg[idx][i] = 0;
                }
            }
            for (int i = 0; i < k; i++)
            {
                seg[idx][i] += temp[i];
            }
            if (low != high) // if children exists
            {
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
            return;
        }

        // partial overlap
        int mid = (low + high) / 2;
        update(2 * idx + 1, low, mid, l, r, val, k);
        update(2 * idx + 2, mid + 1, high, l, r, val, k);
        for (int i = 0; i < k; i++)
        {
            seg[idx][i] = seg[2 * idx + 1][i];
            seg[idx][i] += seg[2 * idx + 2][i];
        }


    }
    vector<ll> rangeQuery(int idx, int low, int high, int l, int r, int k)
    {

        PrevUpdate(idx, low, high, l, r, k);
        // no overlap
        vector<ll>sum(k, 0);
        if (high<l or low>r)
        {
            return sum;
        }

        // complete overlap
        if (low >= l and high <= r)
        {
            return seg[idx];
        }

        // partial overlap
        int mid = (low + high) / 2;
        vector<ll>left = rangeQuery(2 * idx + 1, low, mid, l, r, k);
        vector<ll>right = rangeQuery(2 * idx + 2, mid + 1, high, l, r, k);

        for (int i = 0; i < k; i++)
        {
            sum[i] = left[i] + right[i];
        }
        return sum;
    }

};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w" , stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n , k, q;
    cin >> n >> k >> q;
    ll arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        arr[i] %= k;
    }
    SegTemplate sgt(n, k);

    sgt.build(0, 0, n - 1, arr, k);

    while (q--)
    {
        int a;
        cin >> a;
        if (a == 1)
        {
            int b, c, d;
            cin >> b >> c >> d;
            b--;
            c--;
            d %= k;
            sgt.update(0, 0, n - 1, b, c, d, k);
        }
        else
        {
            int b, c;
            cin >> b >> c;
            b--;
            c--;
            vector<ll>v = sgt.rangeQuery(0, 0, n - 1, b, c, k);
            sort(v.begin(), v.end(), greater<ll>());
            ll sum = 0;
            for (int i = 1; i < k; i++)
            {
                sum += v[i];
            }
            cout << sum << '\n';
        }
    }
    return 0;
}