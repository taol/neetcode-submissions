/**
 * ============================================================================
 * [LRU Cache - C++17/20 极简面试定式与底层复盘笔记]
 * ============================================================================
 * 1. 核心架构与存储分工 (Dual-Data-Structure Invariant):
 *    - lru (std::list<int>): 仅存 key! 充当轻量级淘汰时序队列 (队头 begin 最新 MRU, 队尾 back 最老 LRU).
 *    - data (std::unordered_map): 真正的主存储, key -> {value, list<int>::iterator}.
 *      优势: 相比把 {key, value} 塞进 list, 这种设计在 get(key) 命中哈希表桶时直接拿到 value,
 *      减少一次跨堆节点的指针解引用, CPU Cache Locality 更好, 工程语义也更符合直觉.
 *
 * 2. 为什么 list::splice 是 strict O(1)?
 *    - std::list::iterator 属于 Bidirectional Iterator (不支持 +N 随机跳跃), 但底层封装的
 *      就是链表节点在堆上的绝对物理地址 (_List_node*), 且增删其他节点时迭代器永不失效.
 *    - unordered_map 提供 O(1) 哈希寻址直接拿到 lru_it (绕开链表顺序遍历), 随后双向链表利用
 *      节点自带的 prev/next 指针原地完成 6 次指针拆装, 零堆内存分配 (No new/delete).
 *
 * 3. splice 记忆法与参数口诀:
 *    - 词源: sp(Pointer) + lice -> 胶片/电线剪接, 只改指针不拷贝数据 (区别于 slice 切片).
 *    - 参数顺序 ("搬家三问": 去哪 -> 从哪来 -> 搬谁, 同 memcpy 目的在前、源在后):
 *      lru.splice(lru.begin(), lru, lru_it);
 *    - [忘词保底 Plan B]: 若面试紧张忘掉 splice, 可用 erase + push_front 替代(记得更新引用里的迭代器):
 *      lru.erase(lru_it); lru.push_front(key); lru_it = lru.begin();
 *
 * 4. C++ 现代特性与命名规范提醒:
 *    - 命名: 避免前置下划线 (_capacity 易触碰 ISO C++ 标准库保留标识符规则).
 *      算法轮用无下划线极简风 (cap, lru, data) 盲打最快; 工程/OOP 轮可用后置下划线 (capacity_).
 *    - 语法糖: 用 C++17 结构化绑定 `auto& [val, lru_it] = it->second;` 消除反人类的 `.second.first`.
 *      注意必须带引用 `&`, 否则 put 更新 `val = value` 时改的是局部拷贝!
 *    - 避坑: 切勿使用 C++20 `data.contains(key)`, 会导致 Double Lookup (算两次 Hash);
 *      统一用 `auto it = data.find(key)` 单次查找完成判断与读写.
 *
 * 5. Backend / Infra 常见 4 层 Follow-ups:
 *    - Concurrency: get() 也会调用 splice 修改链表指针, 因此 std::shared_mutex (读写锁) 会退化为串行锁!
 *      解法: Sharded LRU (按 Key Hash 分 16/64 个独立分片锁, 如 RocksDB) 或 RingBuffer 批量延迟提权.
 *    - Scan Resistance (防全表扫描污染): 引入 LRU-K、MySQL InnoDB Young/Old 双区或 W-TinyLFU.
 *    - TTL 过期清理: 惰性删除 (get 时检查过期) + 后台定期随机采样/时间轮清理.
 * ============================================================================
 */

#include <list>
#include <unordered_map>
#include <utility>
using namespace std;

class LRUCache {
private:
    int cap;
    list<int> lru; // 只存 key: front() 是最新访问(MRU), back() 是最久未用(LRU)
    unordered_map<int, pair<int, list<int>::iterator>> data; // key -> {value, lru_it}

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = data.find(key);
        if (it == data.end()) {
            return -1;
        }
        auto& [val, lru_it] = it->second;
        // 搬家三问: 去哪(lru.begin) -> 从哪来(lru) -> 搬谁(lru_it)
        lru.splice(lru.begin(), lru, lru_it);
        return val;
    }

    void put(int key, int value) {
        auto it = data.find(key);
        if (it != data.end()) {
            auto& [val, lru_it] = it->second; // 必须用 auto& 引用, 原地修改 data 里的 value
            val = value;
            lru.splice(lru.begin(), lru, lru_it);
            return;
        }
        
        lru.push_front(key);
        data[key] = {value, lru.begin()};
        if (data.size() > cap) {
            int old_key = lru.back();
            lru.pop_back();
            data.erase(old_key);
        }
    }
};