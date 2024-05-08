#include <iostream>
#include <vector>
#include <list>
#include <functional>

template<typename T>
class GoofyHashSet {
private:
    std::vector<std::list<T>> buckets;
    std::hash<T> hash_function;
    size_t size;
    const double load_factor = 0.75; // Adjust as needed

    void rehash() {
        std::vector<std::list<T>> new_buckets(buckets.size() * 2);
        for (const auto& bucket : buckets) {
            for (const auto& item : bucket) {
                size_t new_index = hash_function(item) % new_buckets.size();
                new_buckets[new_index].push_back(item);
            }
        }
        buckets = std::move(new_buckets);
    }

public:
    GoofyHashSet(size_t initial_capacity = 16) : buckets(initial_capacity), size(0) {}

    void insert(const T& item) {
        if ((static_cast<double>(size) / buckets.size()) > load_factor) {
            rehash();
        }
        size_t index = hash_function(item) % buckets.size();
        auto& bucket = buckets[index];
        for (const auto& value : bucket) {
            if (value == item) {
                return; // Already exists, no need to insert again
            }
        }
        bucket.push_back(item);
        size++;
    }

    bool contains(const T& item) const {
        size_t index = hash_function(item) % buckets.size();
        const auto& bucket = buckets[index];
        for (const auto& value : bucket) {
            if (value == item) {
                return true;
            }
        }
        return false;
    }

    void remove(const T& item) {
        size_t index = hash_function(item) % buckets.size();
        auto& bucket = buckets[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == item) {
                bucket.erase(it);
                size--;
                return;
            }
        }
    }

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};
