class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLen = 0;
        for(auto & num : numSet)
        {
            if(!numSet.contains(num-1))
            {
                int curr = num;
                int len = 1;
                while(numSet.contains(curr+1))
                {
                    ++curr;
                }
                maxLen = max(maxLen, curr - num + 1);
            }
        }    
        return maxLen;
    }
};
