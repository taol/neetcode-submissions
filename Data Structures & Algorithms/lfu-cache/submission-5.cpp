class LFUCache {
   private:
    struct Node {
        int key, val, freq;
        Node(int k, int v) : key(k), val(v), freq(1) {}
    };

    int minFreq, cap;
    unordered_map<int, list<Node>> freqMap;
    using NodeIter = list<Node>::iterator;
    unordered_map<int, NodeIter> keyMap;

    void touch(NodeIter it) {
        int f = it->freq;

        freqMap[f + 1].splice(freqMap[f + 1].begin(), freqMap[f], it);
        it->freq += 1;
        if (freqMap[f].empty()) {
            freqMap.erase(f);
            if (minFreq == f) {
                ++minFreq;
            }
        }
    }

   public:
    LFUCache(int capacity) : cap(capacity), minFreq(0) {}

    int get(int key) {
        auto it = keyMap.find(key);
        if (it == keyMap.end()) {
            return -1;
        }

        touch(it->second);
        return it->second->val;
    }

    void put(int key, int value) {
        auto it = keyMap.find(key);
        if (it != keyMap.end()) {
            it->second->val = value;
            touch(it->second);
            return;
        }

        if (keyMap.size() == cap) {
            int leastKey = freqMap[minFreq].back().key;
            freqMap[minFreq].pop_back();
            if (freqMap[minFreq].empty()) {
                freqMap.erase(minFreq);
            }
            keyMap.erase(leastKey);
        }

        freqMap[1].emplace_front(key, value);
        keyMap[key] = freqMap[1].begin();
        minFreq = 1;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */