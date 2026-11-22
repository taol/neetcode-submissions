class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        vector<int> st;
        st.push_back(-1);
        heights.push_back(0);
        for(int i=0; i<heights.size(); ++i)
        {
            while(st.back() != -1 && heights[st.back()]>= heights[i])
            {
                int height = heights[st.back()];
                st.pop_back();
                int width = i - st.back() - 1;
                maxArea = max(maxArea, width * height);
            }
            st.push_back(i);
        }
        return maxArea;
    }
};
