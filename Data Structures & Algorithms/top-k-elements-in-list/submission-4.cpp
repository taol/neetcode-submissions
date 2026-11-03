class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> numCountMap;
        for(auto num: nums)
        {
            numCountMap[num] += 1;
        }    
        vector<vector<int>> freqNumBuckets(nums.size() + 1);
        for(const auto& [num, count] : numCountMap)
        {
            freqNumBuckets[count].push_back(num);
        }
        vector<int> res;
        res.reserve(k);
        for(int i=freqNumBuckets.size()-1; i>=0; --i)
        {
            for(auto ele : freqNumBuckets[i])
            {
                res.push_back(ele);
                if(res.size()>=k)
                {
                    return res;
                }
            }
        }
        return res;
    }
};
