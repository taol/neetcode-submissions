// Custom-coded by user
// LFU Cache: O(1) avg time for get/put via keyMap + freqMap (list per freq, front=MRU, back=LRU)
class LFUCache {
   private:
    struct Node {
        int key, val, freq;
        Node(int k, int v) : key(k), val(v), freq(1) {}
    };

    using NodeIter = list<Node>::iterator;

    int cap, minFreq;
    unordered_map<int, NodeIter> keyMap;      // key -> iterator in freqMap[freq]
    unordered_map<int, list<Node>> freqMap;  // freq -> doubly linked list ordered by recency

    // Promote node by 1 freq via O(1) splice (keeps iterator valid); advance minFreq if old min bucket empties
    void touch(NodeIter it) {
        int f = it->freq;
        it->freq += 1;
        freqMap[f + 1].splice(freqMap[f + 1].begin(), freqMap[f], it);
        if (freqMap[f].empty()) {
            freqMap.erase(f);
            if (minFreq == f) {
                ++minFreq;
            }
        }
    }

   public:
    LFUCache(int capacity) {
        cap = capacity;
        minFreq = 0;
    }

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

        // Evict LRU node from minFreq bucket when at capacity
        if (keyMap.size() == cap) {
            int leastFreqKey = freqMap[minFreq].back().key;
            freqMap[minFreq].pop_back();
            if (freqMap[minFreq].empty()) {
                freqMap.erase(minFreq);
            }
            keyMap.erase(leastFreqKey);
        }

        // New entries always start at freq = 1 (front = MRU)
        freqMap[1].emplace_front(key, value);
        keyMap[key] = freqMap[1].begin();
        minFreq = 1;
    }
};