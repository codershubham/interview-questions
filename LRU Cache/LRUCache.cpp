#include <unordered_map>
#include <list>

/*Idea is to keep a list of keys in order of their usage and 
a hash map mapping keys to their values and iterators in the list*/
class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1; // Key not found
        }
        // Move the accessed item to the front of the list (most recently used)
        items.splice(items.begin(), items, it->second.second);
        return it->second.first;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            // Key exists, update value and move to front
            it->second.first = value;
            items.splice(items.begin(), items, it->second.second);
        } else {
            // Key does not exist, insert new key-value pair
            if (cache.size() >= capacity) {
                // Evict the least recently used item
                int lruKey = items.back();
                items.pop_back();
                cache.erase(lruKey);
            }
            items.push_front(key);
            cache[key] = {value, items.begin()};
        }
    }
private:
    int capacity;
    std::unordered_map<int, std::pair<int, std::list<int>::iterator>> cache;
    std::list<int> items;
};

int main() {
    LRUCache lruCache(2); // Capacity of 2

    lruCache.put(1, 1); // Cache is {1=1}
    lruCache.put(2, 2); // Cache is {1=1, 2=2}
    lruCache.get(1);    // Returns 1, Cache is {2=2, 1=1}
    lruCache.put(3, 3); // Evicts key 2, Cache is {1=1, 3=3}
    lruCache.get(2);    // Returns -1 (not found)
    lruCache.put(4, 4); // Evicts key 1, Cache is {3=3, 4=4}
    lruCache.get(1);    // Returns -1 (not found)
    lruCache.get(3);    // Returns 3
    lruCache.get(4);    // Returns 4

    return 0;
}