#include <iostream>
#include <vector>
#include <cmath>

template <typename K, typename V>
class HashMopp {
protected:
    K key;
    V value;

public:
    HashMopp(K key, V value) : key(key), value(value) {}
};

template <typename K, typename V>
class InnerHashMopp : public HashMopp<K, V> {
private:
    std::vector<std::vector<HashMopp<K, V>>> buckets;
    int capacity;
    int size;
    static constexpr double LOAD_FACTOR = 0.15;

public:
    InnerHashMopp(int initialcapacity) : HashMopp<K, V>(K(), V()), capacity(initialcapacity), size(0) {
        buckets.resize(capacity);
        for (int index = 0; index < capacity; index++) {
            buckets[index] = std::vector<HashMopp<K, V>>();
        }
    }

    int hash(K key) {
        return std::abs(std::hash<K>{}(key) % capacity);
    }

    void put(K key, V value) {
        if ((static_cast<double>(size + 1) / capacity) > LOAD_FACTOR) {
            resize();
        }
        int index = hash(key);
        auto& bucket = buckets[index];

        for (auto& pair : bucket) {
            if (pair.key == key) {
                pair.value = value;
                return;
            }
        }

        bucket.emplace_back(key, value);
        size++;
    }

    V get(K key) {
        int index = hash(key);
        auto& bucket = buckets[index];

        for (auto& pair : bucket) {
            if (pair.key == key) {
                return pair.value;
            }
        }

        return V();
    }

    void remove(K key) {
        int index = hash(key);
        auto& bucket = buckets[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                size--;
                return;
            }
        }
    }

    void resize() {
        capacity *= 2;
        std::vector<std::vector<HashMopp<K, V>>> newBuckets(capacity);

        for (const auto& bucket : buckets) {
            for (const auto& pair : bucket) {
                int index = std::abs(std::hash<K>{}(pair.key) % capacity);
                newBuckets[index].push_back(pair);
            }
        }

        buckets = std::move(newBuckets);
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }
};
