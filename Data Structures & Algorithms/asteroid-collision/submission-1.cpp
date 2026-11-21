class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st; // 直接把最终结果数组当栈用
        st.reserve(asteroids.size()); // 极致优化：先占好坑
        
        for (int ast : asteroids) {
            if (ast > 0) {
                st.push_back(ast);
            } else {
                // 用 -ast 代替 abs(ast)，省去一次函数调用开销
                while (!st.empty() && st.back() > 0 && st.back() < -ast) {
                    st.pop_back(); 
                }
                
                if (!st.empty() && st.back() == -ast) {
                    st.pop_back(); // 质量相等，同归于尽，当前行星也陨落
                } else if (st.empty() || st.back() < 0) {
                    // 幸存的唯一条件：前方一片虚空 (empty)，或者前面的老哥也是向左飞的 (< 0)
                    st.push_back(ast);
                }
            }
        }
        return st;
    }
};