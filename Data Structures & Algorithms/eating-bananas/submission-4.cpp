class Solution {
   public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int minSpeed = 1, maxSpeed = ranges::max(piles);
        while (minSpeed <= maxSpeed) {
            long long speed = midpoint(minSpeed, maxSpeed);
            if (hoursNeeded(speed, piles) > h) {
                minSpeed = speed + 1;
            } else {
                maxSpeed = speed - 1;
            }
        }

        return minSpeed;
    }

   private:
    long long hoursNeeded(int speed, const vector<int>& piles) {
        long long totalHours = 0;
        for (auto& pile : piles) {
            totalHours += (pile / speed + (pile % speed != 0));
        }
        return totalHours;
    }
};
