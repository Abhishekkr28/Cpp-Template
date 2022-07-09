class SegTemplate
{
    vector<ll>seg, lazy;
public:
    SegTemplate(int n)
    {
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }
    void PrevUpdate(int idx, int low, int high, int l, int r)
    {
        // update the prev update
        if (lazy[idx] != 0)
        {
            seg[idx] += (lazy[idx] * (high - low + 1));
            // propagate downwards
            if (low != high)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }
    void build(int idx, int low, int high, ll arr[])
    {
        if (low == high)
        {
            seg[idx] = arr[low];
            return; // return
        }
        int mid = (low + high) / 2;
        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 1, mid + 1, high, arr);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    }
    void update(int idx, int low, int high, int l, int r, ll val)
    {

        PrevUpdate(idx, low, high, l, r);
        // no overlap
        if (high<l or low>r)
        {
            return;
        }

        // complete overlap
        if (low >= l and high <= r)
        {
            seg[idx] += (val * (high - low + 1));
            if (low != high) // if children exists
            {
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
            return;
        }

        // partial overlap
        int mid = (low + high) / 2;
        update(2 * idx + 1, low, mid, l, r, val);
        update(2 * idx + 2, mid + 1, high, l, r, val);
        seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];


    }
    ll rangeQuery(int idx, int low, int high, int l, int r)
    {

        PrevUpdate(idx, low, high, l, r);
        // no overlap
        if (high<l or low>r)
        {
            return 0;
        }

        // complete overlap
        if (low >= l and high <= r)
        {
            return seg[idx];
        }

        // partial overlap
        int mid = (low + high) / 2;
        ll left = rangeQuery(2 * idx + 1, low, mid, l, r);
        ll right = rangeQuery(2 * idx + 2, mid + 1, high, l, r);
        return left + right;
    }

};