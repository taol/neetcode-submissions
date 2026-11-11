class TimeMap {
   private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> store;

   public:
    TimeMap() {}

    void set(string key, string value, int timestamp) { store[key].emplace_back(timestamp, value); }

    string get(string key, int timestamp) {
        auto it_map = store.find(key);
        if (it_map == store.end()) return "";

        const auto& vec = it_map->second;
        // 找到第一个 timestamp_prev > timestamp 的位置 (upper_bound)
        auto it = std::ranges::upper_bound(vec, timestamp, {}, &std::pair<int, std::string>::first);

        // 如果第一个元素就 > timestamp, 说明没有 <= timestamp 的合法值
        if (it == vec.begin()) return "";

        // 往前退一格, 就是最大的 <= timestamp 的元素 (即你的模板 3 right_bound)
        return std::prev(it)->second;
    }
};
