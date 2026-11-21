class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> nonIncreaseSt;
        // 极致优化：预分配内存，做到 0 次动态内存申请
        nonIncreaseSt.reserve(temperatures.size());
        vector<int> res(temperatures.size(), 0);
        for(int i=0; i<temperatures.size(); ++i)
        {
            while(!nonIncreaseSt.empty() && temperatures[nonIncreaseSt.back()] < temperatures[i])
            {
                res[nonIncreaseSt.back()] = i-nonIncreaseSt.back();
                nonIncreaseSt.pop_back();
            }
            nonIncreaseSt.push_back(i);
        }    

        return res;
    }
};
