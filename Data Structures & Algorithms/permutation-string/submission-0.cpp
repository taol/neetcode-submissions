class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int k = s1.size();

        if (k > s2.size()) {
            return false;
        }

        vector<int> need(26, 0);
        vector<int> window(26, 0);

        // 统计 s1 中的字符
        for (char c : s1) {
            need[c - 'a']++;
        }

        // 先构造长度为 k 的窗口
        for (int i = 0; i < k; i++) {
            window[s2[i] - 'a']++;
        }

        // 检查初始窗口
        if (need == window) {
            return true;
        }

        // 开始滑动窗口
        for (int right = k; right < s2.size(); right++) {
            // 新字符从右边进入
            window[s2[right] - 'a']++;

            // 最左边字符离开
            int left = right - k;
            window[s2[left] - 'a']--;

            // 检查当前窗口
            if (need == window) {
                return true;
            }
        }

        return false;
    }
};
