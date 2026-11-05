class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        // 找到第一个 >= x 的位置
        int right = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int left = right - 1;
        
        // 往左右扩展 k 次, 维护开区间 (left, right)
        while (k--) {
            if (left < 0) {
                right++;
            } else if (right >= n) {
                left--;
            } else if (x - arr[left] <= arr[right] - x) {
                left--;
            } else {
                right++;
            }
        }
        
        // 最终窗口是 [left + 1, right - 1], 转换成迭代器是左闭右开
        return vector<int>(arr.begin() + left + 1, arr.begin() + right);
    }
};