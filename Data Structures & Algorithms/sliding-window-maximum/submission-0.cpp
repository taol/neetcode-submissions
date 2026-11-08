class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> decDeque;
    
        for(int i=0; i<nums.size(); ++i)
        {
            while(!decDeque.empty() && decDeque.back()<nums[i])
            {
                decDeque.pop_back();
            }
            decDeque.push_back(nums[i]);
            if(decDeque.size()>k)
            {
                decDeque.pop_front();
            }
            if(i>=k-1)
            {
                res.push_back(decDeque.front());
            }
        }    
        return res;
    }
};
