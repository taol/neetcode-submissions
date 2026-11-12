#include <numeric>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1;

        // Step 1: 完全复用 Find Minimum in Rotated Sorted Array 的二段性模板
        // 左侧 > nums.back() (False), 右侧 <= nums.back() (True), 找第一个 True
        while (left <= right) {
            int mid = std::midpoint(left, right);
            if (nums[mid] <= nums.back()) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        int pivot = left;  // 此时 left 就是旋转数组的最小值索引

        // Step 2: 确定 target 在哪一段纯升序区间, 直接调标准二分模板 (或 std::lower_bound)
        auto [l, r] = (target <= nums.back()) ? pair{pivot, n - 1} : pair{0, pivot - 1};

        auto it = std::lower_bound(nums.begin() + l, nums.begin() + r + 1, target);
        if (it != nums.begin() + r + 1 && *it == target) {
            return distance(nums.begin(), it);
        }
        return -1;
    }
};