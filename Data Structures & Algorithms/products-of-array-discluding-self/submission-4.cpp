class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 0);
        int product = 1;
        for(int i=0; i<nums.size(); ++i)
        {
            res[i] = product;
            product *= nums[i];
        }
        int productOfAllRights = 1;
        for(int i=(int)nums.size()-1; i>=0; --i)
        {
            res[i] *= productOfAllRights;
            productOfAllRights *= nums[i];
        }

        return res;
    }
};
