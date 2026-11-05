class Solution {
public:
    int characterReplacement(string s, int k) {
        int count[26] = {0};
        int left = 0;
        int maxFreq = 0;
        int maxLen = 0;

        for (int right = 0; right < s.size(); ++right) {
            // 1. 扩大右边界, 更新当前字符频次和历史最高频次
            maxFreq = max(maxFreq, ++count[s[right] - 'A']);

            // 2. 如果当前窗口需要替换的字符数 > k, 左边界右移1位(平移窗口)
            if ((right - left + 1) - maxFreq > k) {
                --count[s[left] - 'A'];
                ++left;
            }

            // 3. 记录最大合法窗口长度
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};