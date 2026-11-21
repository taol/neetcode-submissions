class MinStack {
private:
    vector<pair<int,int>> st;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        int current_min = st.empty() ? val : min(val, st.back().second);
        st.emplace_back(val, current_min);
    }
    
    void pop() {
        st.pop_back();
    }
    
    int top() {
        return st.back().first;
    }
    
    int getMin() {
        return st.back().second;
    }
};
