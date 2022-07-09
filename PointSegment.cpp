class SegTemplate
{
    vector<ll>seg;
public:
    SegTemplate(int n)
    {
        seg.resize(4 * n + 1);
    };
    void build(int idx, int low, int high, ll arr[])
    {
        if (low == high) // Base Case
        {
            seg[idx] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);
        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
    ll query(int idx, int low, int high, int l, int r)
    {
        if (high<l or low>r)
        {
            return INT_MAX;
        }
        else if (low >= l and high <= r)
        {
            return seg[idx];
        }
        else
        {
            int mid = (low + high) / 2;
            ll left = query(2 * idx + 1, low, mid, l, r);
            ll right = query(2 * idx + 2, mid + 1, high, l, r);
            return min(left, right);
        }
    }
    void pointUpdate(int idx, int low, int high, int i, ll val)
    {
        if (low == high)
        {
            seg[idx] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (i <= mid)
            pointUpdate(2 * idx + 1, low, mid, i, val);
        else
            pointUpdate(2 * idx + 2, mid + 1, high, i, val);
        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }


};
