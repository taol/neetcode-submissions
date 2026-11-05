class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int minLen = INT_MAX, back = 0, sum = 0;
        for(int front = 0; front < nums.size(); ++front)
        {
            sum += nums[front];
            while(sum >= target)
            {
                minLen = min(minLen, front - back + 1);
                sum -= nums[back];
                ++back;
            }
        }    

        return minLen == INT_MAX ? 0 : minLen;
    }
};