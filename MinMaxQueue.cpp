template<typename T>
class MinMaxQueue {
    deque <T> q{}, mn{}, mx{};
public:
    MinMaxQueue() = default;
    
    MinMaxQueue(const initializer_list<T>& lst) {
        for (const auto& i : lst) {
            push(i);
        }
    }
    
    void push(T a) {
        q.push_back(a);
        while (!mn.empty() && mn.back() > a) {
            mn.pop_back();
        }
        mn.push_back(a);
        while (!mx.empty() && mx.back() < a) {
            mx.pop_back();
        }
        mx.push_back(a);
    }

    void pop() {
        if (mn.front() == q.front()) {
            mn.pop_front();
        }
        if (mx.front() == q.front()) {
            mx.pop_front();
        }
        q.pop_front();
    }

    const T& front() {
        return q.front();
    }

    const T& back() {
        return q.back();
    }

    const T& min() {
        return mn.front();
    }
    
    T max() {
        return mx.front();
    }

    size_t size() {
        return q.size();
    }

    void clear() {
        q.clear();
        mn.clear();
        mx.clear();
    }
    
    void shrink_to_fit() {
        q.shrink_to_fit();
        mn.shrink_to_fit();
        mx.shrink_to_fit();
    }

    bool empty() {
        return q.size() == 0;
    }
};
