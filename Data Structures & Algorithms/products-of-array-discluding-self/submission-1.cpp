class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> productOfAllLefts(nums.size(), 0);
        int product = 1;
        for(int i=0; i<nums.size(); ++i)
        {
            productOfAllLefts[i] = product;
            product *= nums[i];
        }
        int productOfAllRights = 1;
        for(int i=nums.size()-1; i>=0; --i)
        {
            productOfAllLefts[i] = productOfAllLefts[i]*productOfAllRights;
            productOfAllRights *= nums[i];
        }

        return productOfAllLefts;
    }
};
