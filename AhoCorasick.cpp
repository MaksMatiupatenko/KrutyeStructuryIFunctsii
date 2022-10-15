class Bor {
private:
    const static int alfSize = 26;

    struct Node {
        Node *child[alfSize];
        vector<int> term;
        Node *suff;
        Node *superSuff;
        Node *parent;
        int chr;

        Node() {
            for (auto & i : child) {
                i = nullptr;
            }
            suff = nullptr;
            superSuff = nullptr;
            parent = nullptr;
            chr = -1;
        }
    };

    Node *root;
    Node *curNode;
public:
    Bor() {
        root = new Node();
        curNode = root;
    }

    void add(const string &s, int sInd) {
        Node *cur = root;
        for (int i = 0; i < s.size(); ++i) {
            if (cur->child[s[i] - 'a'] == nullptr) {
                cur->child[s[i] - 'a'] = new Node();
                cur->child[s[i] - 'a']->parent = cur;
                cur->child[s[i] - 'a']->chr = s[i] - 'a';
            }
            cur = cur->child[s[i] - 'a'];
        }
        cur->term.push_back(sInd);
    }

    void build() {
        deque < Node * > q = {root};
        while (!q.empty()) {
            Node *cur = q.front();
            q.pop_front();
            for (auto ch: cur->child) {
                if (ch != nullptr) {
                    q.push_back(ch);
                }
            }
            if (cur == root) {
                for (auto &i: cur->child) {
                    if (i == nullptr) {
                        i = cur;
                    }
                }
                cur->suff = cur;
            } else {
                cur->suff = cur->parent->suff->child[cur->chr];
                if (cur->suff == cur) {
                    cur->suff = root;
                }
                for (int i = 0; i < alfSize; ++i) {
                    if (cur->child[i] == nullptr) {
                        cur->child[i] = cur->suff->child[i];
                    }
                }
                if (!cur->suff->term.empty()) {
                    cur->superSuff = cur->suff;
                } else {
                    cur->superSuff = cur->suff->superSuff;
                }
            }
        }
    }

    vector<int> move(char c) {
        curNode = curNode->child[c - 'a'];
        Node *cur = curNode;
        vector<int> ans;
        while (cur != nullptr) {
            for (auto x: cur->term) {
                ans.push_back(x);
            }
            cur = cur->superSuff;
        }

        return ans;
    }
};
