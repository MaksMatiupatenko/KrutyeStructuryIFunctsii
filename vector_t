template <typename T>
class vector_treap {
#define _VECTOR_TREAP_


public:
	using value_type = T;
	using reference = value_type&;
	using const_reference = const reference;
	using difference_type = ptrdiff_t;
	using size_type = size_t;
	using pointer = value_type*;
	using const_pointer = const pointer;

private:
	class Node {
	private:
		using rand_type = uint32_t;

		rand_type priority;
		size_type size;

		Node* left;
		Node* right;

#ifdef _SNS_
		rand_type rnd() {
			return sns::rnd();
		}
#else
		rand_type rnd() {
			return (rand() << 16) | rand();
		}
#endif // _SNS_

	public:
		value_type key;


		Node() {
			priority = rnd();
			size = 1;
			left = nullptr;
			right = nullptr;
		}
		Node(const Node& other) {
			key = other.key;
			priority = other.priority;
			size = other.size;
			left = _new(other.left);
			right = _new(other.right);
		}
		Node(value_type _key) {
			key = _key;
			priority = rnd();
			size = 1;
			left = nullptr;
			right = nullptr;
		}

		~Node() {
			delete left;
			delete right;
		}


		friend Node* _new(Node* root) {
			if (root) return new Node(root);
			return nullptr;
		}

		friend size_type getSize(Node* root) {
			if (root) return root->size;
			return 0;
		}
		friend void updateSize(Node*& root) {
			if (root)
				root->size = getSize(root->left) + getSize(root->right) + 1;
		}

		friend std::pair <Node*, Node*> split(Node* root, difference_type index) {
			if (!root) return { nullptr, nullptr };

			if (getSize(root->left) >= index) {
				std::pair <Node*, Node*> a = split(root->left, index);
				root->left = a.second;
				updateSize(root);

				return { a.first, root };
			}

			std::pair <Node*, Node*> a = split(root->right, index - getSize(root->left) - 1);
			root->right = a.first;
			updateSize(root);

			return { root, a.second };
		}
		friend Node* merge(Node* left, Node* right) {
			if (!left) return right;
			if (!right) return left;

			if (left->priority > right->priority) {
				left->right = merge(left->right, right);
				updateSize(left);

				return left;
			}

			right->left = merge(left, right->left);
			updateSize(right);

			return right;
		}
	};


	inline static Node* data;


	static Node* access(difference_type n) {
		auto a = split(data, n);
		auto b = split(a.second, 1);

		auto ans = b.first;

		data = merge(a.first, merge(b.first, b.second));

		return ans;
	}

#ifdef assert
	static void _check_range(difference_type index) {
#ifdef _VECTOR_TREAP_DEBUG
		assert(0 >= index && index < size());
#endif // _VECTOR_TREAP_DEBUG
	}
#else
	static void _check_range(difference_type index) {}
#endif // assert

public:
	class iterator {
	public:
		using difference_type = difference_type;
		using value_type = value_type;
		using reference = reference;
		using pointer = value_type*;
		using iterator_category = std::random_access_iterator_tag;

	private:
		difference_type index;
		Node* it_data;

		void update() {
			it_data = access(index);
		}

	public:
		iterator() {
			index = 0;
			it_data = nullptr;
		}
		iterator(iterator&& other) noexcept {
			index = other.index;
			it_data = other.it_data;
		}
		iterator(const iterator& other) {
			index = other.index;
			it_data = other.it_data;
		}


		void _set_to_begin() {
			index = 0;
			update();
		}
		void _set_to_end() {
			index = size();
			update();
		}


		bool operator==(const iterator& other) const {
			return index == other.index;
		}
		bool operator!=(const iterator& other) const {
			return index != other.index;
		}
		bool operator<(const iterator& other) const {
			return index < other.index;
		}
		bool operator>(const iterator& other) const {
			return index > other.index;
		}
		bool operator<=(const iterator& other) const {
			return index <= other.index;
		}
		bool operator>=(const iterator& other) const {
			return index >= other.index;
		}

		iterator& operator=(iterator&& other) {
			index = other.index;
			it_data = other.it_data;

			return *this;
		}
		iterator& operator=(const iterator& other) {
			index = other.index;
			it_data = other.it_data;

			return *this;
		}

		iterator& operator++() {
			++index;

			update();
			return *this;
		}
		iterator operator++(int32_t) {
			auto it = *this;

			++(*this);

			return it;
		}
		iterator& operator+=(difference_type n) {
			index += n;

			update();
			return *this;
		}
		iterator operator+(difference_type n) const {
			return iterator(*this) += n;
		}
		friend iterator operator+(difference_type n, const iterator& it) {
			return it + n;
		}

		iterator& operator--() {
			--index;

			update();
			return *this;
		}
		iterator operator--(int32_t) {
			auto it = *this;

			--(*this);

			return it;
		}
		iterator& operator-=(difference_type n) {
			return *this += (-n);
		}
		iterator operator-(difference_type n) const {
			return *this + (-n);
		}

		difference_type operator-(const iterator& other) const {
			return index - other.index;
		}

		reference operator*() const {
			_check_range(index);

			return it_data->key;
		}
		pointer operator->() const {
			_check_range(index);

			return std::addressof(it_data->key);
		}
		reference operator[](difference_type n) const {
			return *(*this + n);
		}
	};
	class const_iterator {
	public:
		using difference_type = difference_type;
		using value_type = value_type;
		using reference = const reference;
		using pointer = const value_type*;
		using iterator_category = std::random_access_iterator_tag;

	private:
		difference_type index;
		Node* it_data;

		void update() {
			it_data = access(index);
		}

	public:
		const_iterator() {
			index = 0;
			it_data = nullptr;
		}
		const_iterator(const_iterator&& other) {
			index = other.index;
			it_data = other.it_data;
		}
		const_iterator(const const_iterator& other) {
			index = other.index;
			it_data = other.it_data;
		}
		const_iterator(const iterator& it) {
			*this = it - iterator() + const_iterator();
		}


		void _set_to_begin() {
			index = 0;
			update();
		}
		void _set_to_end() {
			index = size();
			update();
		}


		bool operator==(const const_iterator& other) const {
			return index == other.index;
		}
		bool operator!=(const const_iterator& other) const {
			return index != other.index;
		}
		bool operator<(const const_iterator& other) const {
			return index < other.index;
		}
		bool operator>(const const_iterator& other) const {
			return index > other.index;
		}
		bool operator<=(const const_iterator& other) const {
			return index <= other.index;
		}
		bool operator>=(const const_iterator& other) const {
			return index >= other.index;
		}

		const_iterator& operator=(const_iterator&& other) {
			index = other.index;
			it_data = other.it_data;

			return *this;
		}
		const_iterator& operator=(const const_iterator& other) {
			index = other.index;
			it_data = other.it_data;

			return *this;
		}

		const_iterator& operator++() {
			++index;

			update();
			return *this;
		}
		const_iterator operator++(int32_t) {
			auto it = *this;

			++(*this);

			return it;
		}
		const_iterator& operator+=(difference_type n) {
			index += n;

			update();
			return *this;
		}
		const_iterator operator+(difference_type n) const {
			return const_iterator(*this) += n;
		}
		friend const_iterator operator+(difference_type n, const const_iterator& it) {
			return it + n;
		}

		const_iterator& operator--() {
			--index;

			update();
			return *this;
		}
		const_iterator operator--(int32_t) {
			auto it = *this;

			--(*this);

			return it;
		}
		const_iterator& operator-=(difference_type n) {
			return *this += (-n);
		}
		const_iterator operator-(difference_type n) const {
			return *this + (-n);
		}

		difference_type operator-(const const_iterator& other) const {
			return index - other.index;
		}

		reference operator*() const {
			_check_range(index);

			return it_data->key;
		}
		pointer operator->() const {
			_check_range(index);

			return std::addressof(it_data->key);
		}
		reference operator[](difference_type n) const {
			return *(*this + n);
		}

	};
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;


	vector_treap() {
		data = nullptr;
	}
	vector_treap(size_type _size, const_reference value) {
		data = nullptr;
		assign(_size, value);
	}
	vector_treap(size_type _size) {
		data = nullptr;
		resize(_size);
	}
	template <typename _Iter>
	vector_treap(_Iter first, _Iter last) {
		data = nullptr;
		while (first != last) {
			push_back(*first);
			++first;
		}
	}
	vector_treap(vector_treap&& other) {
		data = other.data;
	}
	vector_treap(const vector_treap& other) {
		data = _new(other.data);
	}
	vector_treap(std::initializer_list <value_type> list) {
		assign(list);
	}

	~vector_treap() {
		delete data;
	}


	iterator begin() {
		iterator it;
		it._set_to_begin();

		return it;
	}
	const_iterator cbegin() {
		return const_iterator(begin());
	}
	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}
	const_reverse_iterator crbegin() {
		return const_reverse_iterator(cend());
	}

	iterator end() {
		iterator it;
		it._set_to_end();

		return it;
	}
	const_iterator cend() {
		return const_iterator(end());
	}
	reverse_iterator rend() {
		return reverse_iterator(begin());
	}
	const_reverse_iterator crend() {
		return const_reverse_iterator(cbegin());
	}

	static size_type size() {
		return getSize(data);
	}
	size_type max_size() {
		return std::numeric_limits<difference_type>::max();
	}
	bool empty() {
		return data == nullptr;
	}

	void swap(vector_treap& other) {
		swap(data, other.data);
	}
	friend void swap(vector_treap& a, vector_treap& b) {
		swap(a.data, b.data);
	}

	void clear() {
		if (data) {
			data->~Node();
			data = nullptr;
		}
	}

	void assign(std::initializer_list <value_type> list) {
		clear();
		for (const auto& x : list)
			push_back(x);
	}
	void assign(size_type _size, const value_type& value) {
		clear();
		for (size_type i = 0; i < _size; i++)
			push_back(value);
	}
	template <typename _Iter>
	void assign(_Iter _begin, _Iter _end) {
		clear();
		while (_begin != _end) {
			push_back(*_begin);
			++_begin;
		}
	}

	iterator insert(const_iterator it, const_reference value) {
		difference_type pos = it - cbegin();

		auto a = split(data, pos);

		data = merge(merge(a.first, new Node(value)), a.second);
		return begin() + pos;
	}
	iterator insert(const_iterator it, value_type&& value) {
		difference_type pos = it - cbegin();

		auto a = split(data, pos);

		data = merge(merge(a.first, new Node(value)), a.second);
		return begin() + pos;
	}
	iterator insert(const_iterator it, size_type count, const_reference value) {
		difference_type pos = it - cbegin();

		auto a = split(data, pos);

		Node* _New = nullptr;
		for (size_type i = 0; i < count; i++)
			_New = merge(_New, new Node(value));

		data = merge(merge(a.first, _New), a.second);
		return begin() + pos;
	}
	iterator insert(const_iterator it, const vector_treap <value_type>& other) {
		difference_type pos = it - cbegin();

		auto a = split(data, pos);

		data = merge(merge(a.first, other.data), a.second);
		return begin() + pos;
	}
	template <typename _Iter>
	iterator insert(const_iterator it, _Iter _begin, _Iter _end) {
		difference_type pos = it - cbegin();

		auto a = split(data, pos);

		Node* _New = nullptr;
		while (_begin != _end) {
			_New = merge(_New, new Node(*_begin));
			++_begin;
		}

		data = merge(merge(a.first, _New), a.second);
		return begin() + pos;
	}
	iterator insert(const_iterator it, std::initializer_list <value_type> list) {
		difference_type pos = it - cbegin();

		auto a = split(data, pos);

		Node* _New = nullptr;
		for (const auto& x : list)
			_New = merge(_New, new Node(x));

		data = merge(merge(a.first, _New), a.second);
		return begin() + pos;
	}

	template <class... Args>
	iterator emplace(const_iterator it, Args&&... args) {
		return insert(it, value_type(args...));
	}

	iterator erase(const_iterator it) {
		difference_type pos = it - begin();

		auto a = split(data, pos);
		auto b = split(a.second, 1);

		delete b.first;

		data = merge(a.first, b.second);
		return begin() + pos;
	}
	iterator erase(const_iterator first, const_iterator last) {
		difference_type pos1 = first - begin();
		difference_type pos2 = last - begin();

		auto a = split(data, pos2);
		auto b = split(a.first, pos1);

		delete b.second;

		data = merge(b.first, a.second);
		return begin() + pos1;
	}

	void push_back(const value_type& value) {
		data = merge(data, new Node(value));
	}
	void push_back(value_type&& value) {
		data = merge(data, new Node(value));
	}

	template <class... Args>
	reference emplace_back(Args&&... args) {
		push_back(value_type(args...));

		return back();
	}

	void pop_back() {
		data = split(data, size() - 1).first;
	}

	void resize(size_type _size) {
		if (size() > _size) {
			erase(cbegin() + _size, cend());
		}
		else {
			for (int i = size(); i < _size; i++)
				data = merge(data, new Node());
		}
	}
	void resize(size_type _size, const_reference value) {
		if (size() > _size) {
			erase(cbegin() + _size, cend());
		}
		else {
			for (int i = size(); i < _size; i++)
				data = merge(data, new Node(value));
		}
	}

	reference at(difference_type n) {
#ifdef assert
		assert(n >= 0 && n < size());
#endif

		return access(n)->key;
	}
	reference front() {
		_check_range(0);

		return access(0)->key;
	}
	reference back() {
		_check_range(size() - 1);

		return access(size() - 1);
	}


	bool operator==(const vector_treap& other) {
		if (size() != other.size()) return false;

		for (const_iterator it1 = cbegin(), it2 = other.cbegin(); it1 != cend(); it1++, it2++)
			if (*it1 != *it2) return false;

		return true;
	}
	bool operator!=(const vector_treap& other) {
		return !(*this == other);
	}

	vector_treap <value_type>& operator=(vector_treap&& other) {
		data = other.data;
	}
	vector_treap <value_type>& operator=(const vector_treap& other) {
		data = _new(other.data);
	}
	vector_treap <value_type>& operator=(std::initializer_list <value_type> list) {
		assign(list);
	}

	reference operator[](difference_type n) {
		_check_range(n);

		return access(n)->key;
	}

#ifdef _SNS_IO_
	friend std::istream& operator>>(std::istream& is, vector_treap <value_type>& v) {
		return sns::io::readContainer(is, v);
	}
	friend std::ostream& operator<<(std::ostream& os, const vector_treap <value_type>& v) {
		return sns::io::printContainer(os, v);
	}
#endif // _SNS_IO_

};
