class Solution {
   public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> positive;
        vector<int> negative;
        for (auto& asteroid : asteroids) {
            if (asteroid > 0) {
                positive.push_back(asteroid);
            } else {
                while (!positive.empty() && positive.back() < abs(asteroid)) {
                    positive.pop_back();
                }
                if(!positive.empty() && positive.back() == abs(asteroid))
                {
                    positive.pop_back();
                }
                if (positive.empty()) {
                    negative.push_back(asteroid);
                }
            }
        }
        negative.insert(negative.end(), positive.begin(), positive.end());
        return negative;
    }
};