namespace _Hash_ {
	const int k = 2;
	const int64 m[k] = { (int64)1e9 + 7, (int64)1e9 + 9 };

	class Hash {
	private:
		int64 x[k];

	public:
		Hash(int64 value = 0) {
			for (int i = 0; i < k; i++) {
				x[i] = (value % m[i] + m[i]) % m[i];
			}
		}
		Hash(const Hash& other) {
			for (int i = 0; i < k; i++) {
				x[i] = other.x[i];
			}
		}

		Hash operator+(const Hash& other) const {
			Hash ans;
			for (int i = 0; i < k; i++) {
				ans.x[i] = (x[i] + other.x[i]) % m[i];
			}
			return ans;
		}
		
		Hash operator-(const Hash& other) const {
			Hash ans;
			for (int i = 0; i < k; i++) {
				ans.x[i] = (x[i] - other.x[i] + m[i]) % m[i];
			}
			return ans;
		}
		
		Hash operator*(const Hash& other) const {
			Hash ans;
			for (int i = 0; i < k; i++) {
				long long a = x[i], b = other.x[i];
				ans.x[i] = (a * b) % m[i];
			}
			return ans;
		}

		bool operator==(const Hash& other) const {
			for (int i = 0; i < k; i++) {
				if (x[i] != other.x[i]) return false;
			}
			return true;
		}
		
		bool operator!=(const Hash& other) const {
			for (int i = 0; i < k; i++) {
				if (x[i] != other.x[i]) return true;
			}
			return false;
		}
		
		bool operator<(const Hash& other) const {
			for (int i = 0; i < k; i++) {
				if (x[i] < other.x[i]) return true;
				if (x[i] > other.x[i]) return false;
			}
			return false;
		}

		Hash& operator=(const Hash& other) {
			for (int i = 0; i < k; ++i)
				x[i] = other.x[i];
			return *this;
		}
	};

	const Hash p0 = 257;
	std::vector <Hash> p;

	class Hasher {
	private:
		std::vector <Hash> data;

	public:
		template <class Iter>
		Hasher(Iter begin, Iter end) {
			data.assign(end - begin + 1, 0);
			for (int i = 1; i < data.size(); ++i) {
				data[i] = data[i - 1] * p0 + *begin;
				++begin;
			}
			if (p.size() < data.size()) {
				int old = max((int)p.size(), 1);
				p.resize(data.size(), 1);
				for (int i = old; i < p.size(); ++i) {
					p[i] = p[i - 1] * p0;
				}
			}
		}

		Hash operator()(int l, int r) {
			return data[r] - data[l] * p[r - l];
		}
	};
}
using Hash = _Hash_::Hash;
using Hasher = _Hash_::Hasher;
