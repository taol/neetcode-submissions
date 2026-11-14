class LRUCache {
   private:
    list<int> _lru;
    unordered_map<int, pair<int, list<int>::iterator>> _map;
    int _capacity;

   public:
    LRUCache(int capacity) : _capacity(capacity) {}

    int get(int key) {
        auto it = _map.find(key);
        if (it == _map.end()) {
            return -1;
        }
        auto [val, lru_it] = it->second;
        _lru.splice(_lru.begin(), _lru, lru_it);
        return val;
    }

    void put(int key, int value) {
        auto it = _map.find(key);
        if (it != _map.end()) {
            auto& [val, lru_it] = it->second;
            val = value;
            _lru.splice(_lru.begin(), _lru, lru_it);
            return;
        }
        if (_map.size() == _capacity) {
            int old_key = _lru.back();
            _lru.pop_back();
            _map.erase(old_key);
        }
        _lru.push_front(key);
        _map[key] = {value, _lru.begin()};
    }
};
