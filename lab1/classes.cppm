export module classes;
import std;

export template <typename T>
T randomvalue()
{
	return T{};
}
template <>
bool randomvalue<bool>() {
	std::random_device seed;
	std::mt19937 generator(seed());
	std::bernoulli_distribution distribution(0.5);
	return distribution(generator);
}
template <>
char randomvalue<char>() {
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_int_distribution<int> distribution(std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
	return static_cast<char>(distribution(generator));
}
template<>
short randomvalue<short>() {
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_int_distribution<short> distribution(std::numeric_limits<short>::min(), std::numeric_limits<short>::max());
	return distribution(generator);
}template<>
float randomvalue<float>() {
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_real_distribution<float> distribution(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
	return distribution(generator);
}

export template<typename T>
T invertedvalue(T value)
{
	return -value;
}
template<>
bool invertedvalue<bool>(bool value) {
	return !value;
}

export template <typename T>
class image
{
private:
	int _rows = 0;
	int _cols = 0;
	T* _data = nullptr;
	
	template <typename T>
	bool equal(const T& a, const T& b, double epsilon) {
		return a == b;
	}
	bool equal(float a, float b, double epsilon) {
		return std::abs(a - b) <= epsilon;
	}
public:
	const double epsilon = 1e-6;
	image(int rows, int cols, bool randomfill) : _rows(rows), _cols(cols)
	{
		if (rows <= 0 || cols <= 0)
		{
			throw std::invalid_argument("image size must be positive");
		}
		_data = new T[_rows * _cols]{};

		if (randomfill)
		{
			for (int i = 0; i < _rows * _cols; ++i)
			{
				_data[i] = randomvalue<T>();
			}
		}
	}

	image(const image& other) : _rows(other._rows), _cols(other._cols), _data(new T[other._rows * other._cols])
	{
		for (int i = 0; i < other._rows * other._cols; ++i)
		{
			_data[i] = other._data[i];
		}
	}

	image& operator=(const image& other)
	{
		if (this == &other)
		{
			return *this;
		}
		T* new_data = new T[other._rows * other._cols];

		for (int i = 0; i < other._rows * other._cols; ++i)
		{
			new_data[i] = other._data[i];
		}

		delete[] _data;

		_data = new_data;
		_rows = other._rows;
		_cols = other._cols;

		return *this;
	}

	int getrows() const
	{
		return _rows;
	}

	int getcols() const
	{
		return _cols;
	}

	T& operator()(int row, int col)
	{
		if (row < 0 || row >= _rows || col < 0 || col >= _cols)
		{
			throw std::out_of_range("Index out of range");
		}

		return _data[row * _cols + col];
	}

	const T& operator()(int row, int col) const
	{
		if (row < 0 || row >= _rows || col < 0 || col >= _cols)
		{
			throw std::out_of_range("Index out of range");
		}

		return _data[row * _cols + col];
	}

	double ratio() const
	{
		double sum = 0;
		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				sum += (*this)(i, j);
			}
		}

		double cells = _rows * _cols;
		double maxvalue = static_cast<double>(std::numeric_limits<T>::max());
		double result = (sum / (cells * maxvalue));
		return result;
	}
	
	template <typename T>
	image<T> multy(const image<T>& a) const
	{
		if (a.getrows() != getrows() || a.getcols() != getcols())
		{
			throw std::invalid_argument("Images must have the same size");
		}

		image<T> result(getrows(), getcols(), false);
		for (int i = 0; i < getrows(); ++i)
		{
			for (int j = 0; j < getcols(); ++j)
			{
				T x = (*this)(i, j);
				T y = a(i, j);

				if (std::numeric_limits<T>::is_integer && std::numeric_limits<T>::digits > 1)
				{
					if (x != 0 && y != 0)
					{
						if (std::numeric_limits<T>::is_signed)
						{
							if (x == -1 && y == std::numeric_limits<T>::min()) throw std::overflow_error("overflow in multy");
							if (y == -1 && x == std::numeric_limits<T>::min()) throw std::overflow_error("overflow in multy");

							if (x > 0)
							{
								if (y > 0 && x > std::numeric_limits<T>::max() / y) throw std::overflow_error("overflow in multy");
								if (y < 0 && y < std::numeric_limits<T>::min() / x) throw std::overflow_error("overflow in multy");
							}
							else if (x < 0)
							{
								if (y > 0 && x < std::numeric_limits<T>::min() / y) throw std::overflow_error("overflow in multy");
								if (y < 0 && x < std::numeric_limits<T>::max() / y) throw std::overflow_error("overflow in multy");
							}
						}
						else
						{
							if (x > std::numeric_limits<T>::max() / y) throw std::overflow_error("overflow in multy");
						}
					}
				}
				else if (!std::numeric_limits<T>::is_integer)
				{
					if (std::isinf(static_cast<double>(x) * static_cast<double>(y)))
						throw std::overflow_error("overflow in multy");
				}

				result(i, j) = x * y;
			}
		}
		return result;
	}

	image<T> operator*(const image<T>& a) 
	{
		return multy(a);
	}
	
	template <typename T>
	image<T> sum(const image<T>& a) 
	{
		int max_rows = std::max(a.getrows(), getrows());
		int max_cols = std::max(a.getcols(), getcols());
		image<T> result(max_rows, max_cols, false);
		for (int i = 0; i < max_rows; ++i)
		{
			for (int j = 0; j < max_cols; ++j)
			{
				T first = T{};
				T second = T{};
				if (i < a.getrows() && j < a.getcols()) first = a(i, j);
				if (i < getrows() && j < getcols()) second = (*this)(i, j);

				if (std::numeric_limits<T>::digits == 1)
				{
					result(i, j) = first || second;
				}
				else
				{
					if (std::numeric_limits<T>::is_integer)
					{
						if (std::numeric_limits<T>::is_signed)
						{
							if (second > 0 && first > std::numeric_limits<T>::max() - second)
								throw std::overflow_error("overflow in sum");
							if (second < 0 && first < std::numeric_limits<T>::min() - second)
								throw std::overflow_error("overflow in sum");
						}
						else
						{
							if (first > std::numeric_limits<T>::max() - second)
								throw std::overflow_error("overflow in sum");
						}
					}
					else
					{
						if (std::isinf(static_cast<double>(first) + static_cast<double>(second)))
							throw std::overflow_error("overflow in sum");
					}

					result(i, j) = first + second;
				}
			}
		}
		return result;
	}

	template <>
	image<bool> sum(const image<bool>& a)
	{
		int max_rows = std::max(a.getrows(), getrows());
		int max_cols = std::max(a.getcols(), getcols());
		image<bool> result(max_rows, max_cols, false);
		for (int i = 0; i < max_rows; ++i)
		{
			for (int j = 0; j < max_cols; ++j)
			{
				bool first = false;
				bool second = false;

				if (i < a.getrows() && j < a.getcols())
					first = a(i, j);

				if (i < getrows() && j < getcols())
					second = (*this)(i, j);

				result(i, j) = first || second;
			}
		}
		return result;
	}

	image<T> operator+(const image<T>& a) 
	{
		return sum(a);
	}

	image<T> operator-(const image<T>& a) const
	{
		int max_rows = std::max(a._rows, _rows);
		int max_cols = std::max(a._cols, _cols);
		image<T> result(max_rows, max_cols, false);
		for (int i = 0; i < max_rows; ++i) {
			for (int j = 0; j < max_cols; ++j) {
				T first = T{};
				T second = T{};

				if (i < a._rows && j < a._cols) first = a(i, j);
				if (i < _rows && j < _cols) second = (*this)(i, j);

				if (std::numeric_limits<T>::is_integer && std::numeric_limits<T>::digits > 1)
				{
					if (std::numeric_limits<T>::is_signed)
					{
						if (second > 0 && first < std::numeric_limits<T>::min() + second)
							throw std::overflow_error("overflow in subtraction");
						if (second < 0 && first > std::numeric_limits<T>::max() + second)
							throw std::overflow_error("overflow in subtraction");
					}
					else
					{
						if (first < second)
							throw std::overflow_error("overflow in subtraction");
					}
				}
				else if (!std::numeric_limits<T>::is_integer)
				{
					if (std::isinf(static_cast<double>(first) - static_cast<double>(second)))
						throw std::overflow_error("overflow in subtraction");
				}

				result(i, j) = second - first;
			}
		}
		return result;
	}

	image<T> operator*(const int& num)
	{
		image<T> result(_rows, _cols, false);
		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				result(i, j) = (*this)(i, j) * num;
			}
		}
		return result;
	}

	image<T> operator+(const int& num)
	{
		image<T> result(_rows, _cols, false);

		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				result(i, j) = (*this)(i, j) + num;
			}
		}
		return result;
	}

	image<T> operator!()
	{
		image<T> result(_rows, _cols, false);
		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				result(i, j) = invertedvalue((*this)(i, j));
			}
		}
		return result;
	}

	bool operator==(const image<T>& a)
	{
		if (a._rows != _rows || a._cols != _cols)
		{
			return false;
		}
		for (int i = 0; i < a._rows; ++i)
		{
			for (int j = 0; j < a._cols; ++j)
			{
				if (!equal(a(i, j), (*this)(i, j), epsilon))
				{
					return false;
				}
			}
		}
		return true;
	}	

	~image()
	{
		delete[] _data;
	}
};
export template <typename T>
std::ostream& operator<<(std::ostream& out, const image<T>& img)
{
	for (int i = 0; i < img.getrows(); ++i)
	{
		for (int j = 0; j < img.getcols(); ++j)
		{
			out << img(i, j) << " ";

		}
		out << "\n";
	}
	return out;
}