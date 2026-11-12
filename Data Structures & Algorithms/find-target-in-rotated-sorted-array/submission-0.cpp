#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1;

        // 二段性判定 (check): 判断 nums[mid] 是否在 target 的右侧 (或等于 target)
        // 满足条件返回 true (缩右边界 right = mid - 1), 否则返回 false (缩左边界 left = mid + 1)
        auto is_on_right = [&](int mid) -> bool {
            bool target_in_left_part = (target > nums.back());
            bool mid_in_left_part = (nums[mid] > nums.back());

            if (mid_in_left_part == target_in_left_part) {
                // 1. mid 和 target 落在同一个递增区间内 -> 直接比大小
                return nums[mid] >= target;
            }
            // 2. 不在同一个区间:
            // 如果 target 在左半段(大值区), mid 在右半段(小值区) -> mid 在 target 右边 (true)
            // 如果 target 在右半段(小值区), mid 在左半段(大值区) -> mid 在 target 左边 (false)
            return target_in_left_part;
        };

        // 完全复用你习惯的 lower_bound 闭区间二段论模板
        while (left <= right) {
            int mid = std::midpoint(left, right);
            if (is_on_right(mid)) {
                right = mid - 1; // mid 可能是答案或在答案右侧, 往左缩
            } else {
                left = mid + 1;  // mid 在答案左侧, 往右缩
            }
        }

        // 循环结束时, left 停在第一个使得 is_on_right(left) 为 true 的位置
        return (left < n && nums[left] == target) ? left : -1;
    }
};