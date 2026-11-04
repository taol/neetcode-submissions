class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charLastseenIndexMap;
        int maxLen = 0;
        int left = 0;
        for(int right = 0; right < s.size(); ++right)
        {
            char c = s[right];
            if(charLastseenIndexMap.contains(c) && charLastseenIndexMap[c] >= left)
            {
                left = charLastseenIndexMap[c] + 1;
            }
            charLastseenIndexMap[c] = right;
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};
