class Solution {
   public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1, r = ranges::max(piles);
        while(l<=r)
        {
            int m = midpoint(l, r);
            int hours = hoursNeeded(m, piles);
            if(hours > h)
            {
                l = m + 1;
            }
            else 
            {
                r = m - 1;
            }
        }

        return l;
    }

   private:
    long long hoursNeeded(int speed, vector<int>& piles) {
        long long res = 0;
        for (auto& pile : piles) {
            res += (pile / speed + (pile % speed != 0));
        }
        return res;
    }
};
