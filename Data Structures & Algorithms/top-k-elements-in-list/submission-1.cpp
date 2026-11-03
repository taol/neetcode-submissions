class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> numCountMap;
        for(auto num: nums)
        {
            numCountMap[num] += 1;
        }    
        vector<vector<int>> freqNumBuckets(nums.size() + 1);
        for(auto [num, count] : numCountMap)
        {
            freqNumBuckets[count].push_back(num);
        }
        vector<int> res;
        for(int i=freqNumBuckets.size()-1; i>=0; --i)
        {
            if(res.size()<k)
            {
                for(auto ele : freqNumBuckets[i])
                {
                    res.push_back(ele);
                }
            }
            else
            return res;
        }
    }
};
