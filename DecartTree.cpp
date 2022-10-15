class DecartTree {
private:
    struct Node {
        int size;
        int key;
        uint priority;
        int64 sum;
        Node* left;
        Node* right;
        Node(int key) :key(key), size(1), sum(key), priority(rnd()), left(nullptr), right(nullptr) {}
    };

    int getSize(Node* node) {
        if (node == nullptr) return 0;
        return node->size;
    }

    int64 getSum(Node* node) {
        if (node == nullptr) return 0;
        return node->sum;
    }

    void update(Node* node) {
        node->size = 1 + getSize(node->left) + getSize(node->right);
        node->sum = node->key + getSum(node->left) + getSum(node->right);
    }

    std::pair <Node*, Node*> split(Node* node, int size) {
        if (node == nullptr) return { nullptr, nullptr };
        if (getSize(node->left) >= size) {
            auto p = split(node->left, size);
            node->left = p.second;
            update(node);
            return { p.first, node };
        }
        auto p = split(node->right, size - getSize(node->left) - 1);
        node->right = p.first;
        update(node);
        return { node, p.second };
    }

    Node* merge(Node* left, Node* right) {
        if (right == nullptr) return left;
        if (left == nullptr) return right;
        if (left->priority < right->priority) {
            left->right = merge(left->right, right);
            update(left);
            return left;
        }
        right->left = merge(left, right->left);
        update(right);
        return right;
    }

    void print(Node* node) {
        if (node == nullptr) return;
        print(node->left);
        std::cout << node->key << ' ';
        print(node->right);
    }

    void _delete(Node* node) {
        if (node == nullptr) return;
        _delete(node->left);
        _delete(node->right);
        delete node;
    }

    Node* _copy(Node* node) {
        if (node == nullptr) return nullptr;
        Node* nd = new Node(*node);
        nd->left = _copy(nd->left);
        nd->right = _copy(nd->right);
        return nd;
    }

    Node* root;

public:
    DecartTree() {
        root = nullptr;
    }
    ~DecartTree() {
        _delete(root);
    }


    void push_back(int key) {
        Node* nd = new Node(key);
        root = merge(root, nd);
    }

    void print(int l, int r) {
        auto [nl, nr] = split(root, r);
        auto [nll, nlr] = split(nl, l);
        print(nlr);
        root = merge(nll, nlr);
        root = merge(root, nr);
    }

    void move(int l, int r, int pos) {
        if (l <= pos && pos <= r) return;
        auto [nl, nr] = split(root, r);
        auto [nll, nlr] = split(nl, l);
        root = merge(nll, nr);
        if (pos < l) {
            auto [nl1, nr1] = split(root, pos);
            root = merge(merge(nl1, nlr), nr1);
        }
        else {
            auto [nl1, nr1] = split(root, pos - (r - l));
            root = merge(merge(nl1, nlr), nr1);
        }
    }

    size_t size() {
        return getSize(root);
    }
};
