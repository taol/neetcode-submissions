class Solution {
public:
    int maxArea(vector<int>& heights) {
        int i=0, j=heights.size()-1, res=0;
        while(i<j)
        {
            int area = min(heights[i], heights[j])*(j-i);
            res = max(res, area);
            heights[i] < heights[j] ? ++i : --j;
        } 
        return res;   
    }
};
