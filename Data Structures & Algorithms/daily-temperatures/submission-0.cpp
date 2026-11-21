class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> nonIncreaseSt;
        vector<int> res(temperatures.size(), 0);
        for(int i=0; i<temperatures.size(); ++i)
        {
            while(!nonIncreaseSt.empty() && temperatures[nonIncreaseSt.top()] < temperatures[i])
            {
                res[nonIncreaseSt.top()] = i-nonIncreaseSt.top();
                nonIncreaseSt.pop();
            }
            nonIncreaseSt.push(i);
        }    

        return res;
    }
};
