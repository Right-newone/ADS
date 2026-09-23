import std;
export module classes;

export template <typename T>
T randomvalue()
{
	std::random_device seed;
	std::mt19937 generator(seed());

	if constexpr (std::is_same_v<T, bool>)
	{
		std::bernoulli_distribution distribution(0.5);
		return distribution(generator);
	}
	else if constexpr (std::is_same_v<T, char>)
	{
		std::uniform_int_distribution<int> distribution(1, 100);
		return static_cast<char>(distribution(generator));
	}
	else if constexpr (std::is_same_v<T, short>)
	{
		std::uniform_int_distribution<short> distribution(1, 100);
		return distribution(generator);
	}
	else if constexpr (std::is_same_v<T, float>)
	{
		std::uniform_real_distribution<float> distribution(1, 100);
		return distribution(generator);
	}
	return T{};
}
export template <typename T>
class image 
{
private:
	int _rows = 0;
	int _cols = 0;
	T* _data = nullptr;
public:
	static constexpr double epsilon = 1e-6;
	image(int rows, int cols, bool randomfill) : _rows(rows), _cols(cols) 
	{
		if (rows <= 0 || cols <= 0)
		{
			throw std::invalid_argument("image dimensions must be positive");
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

	image(const image& other) : _rows(other._rows),	_cols(other._cols),	_data(new T[other._rows * other._cols])
	{
		for (int i = 0; i < _rows * _cols; ++i)
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

	~image()
	{
		delete[] _data;
	}
};
export template <typename T>
std::ostream& operator<<(std::ostream& out, const image<T>& image)
{
	for (int i = 0; i < image.getrows(); ++i)
	{
		for (int j = 0; j < image.getcols(); ++j)
		{
			if constexpr (std::is_same_v<T, char>)
			{
				out << static_cast<int>(image(i, j)) << " ";
			}
			else
			{
				out << image(i, j) << " ";
			}
		}
		out << "\n";
	}
	return out;
}
export template <typename T>
image<T> operator*(const image<T>& a, const image<T>& b)
{
	if constexpr (std::is_same_v<T, bool>)
	{
		if (a.getrows() != b.getrows() || a.getcols() != b.getcols())
		{
			throw std::invalid_argument("Bool images must have the same size");
		}
		image<T> result(a.getrows(), a.getcols(), false);

		for (int i = 0; i < a.getrows(); ++i)
		{
			for (int j = 0; j < a.getcols(); ++j)
			{
				result(i, j) = a(i, j) && b(i, j);
			}
		}
		return result;
	}
	else {
		if (a.getcols() != b.getrows()) {
			throw std::invalid_argument("Cols must be the save size as the rows of the other matrix");
		}
		image<T> result(a.getrows(), b.getcols(), false);
		for (int i = 0; i < a.getrows(); ++i) {
			for (int j = 0; j < b.getcols(); ++j) {

				T sum = T{};

				for (int k = 0; k < a.getcols(); ++k) {
					sum += a(i, k) * b(k, j);
				}
				result(i, j) = sum;
			}
		}
		return result;
	}
}
export template <typename T>
image<T> operator+(const image<T>& a, const image<T>& b)
{
		int max_rows = std::max(a.getrows(), b.getrows());
		int max_cols = std::max(a.getcols(), b.getcols());
		image<T> result(max_rows, max_cols, false);
		for (int i = 0; i < max_rows; ++i) {
			for (int j = 0; j < max_cols; ++j) {
				T first = T{};
				T second = T{};
				if (i < a.getrows() && j < a.getcols()) {
					first = a(i, j);
				}
				if (i < b.getrows() && j < b.getcols()) {
					second = b(i, j);
				}
				result(i, j) = first + second;
			}
		}
		return result;
}
export template <typename T>
image<T> operator-(const image<T>& a, const image<T>& b)
{
	int max_rows = std::max(a.getrows(), b.getrows());
	int max_cols = std::max(a.getcols(), b.getcols());
	image<T> result(max_rows, max_cols, false);
	for (int i = 0; i < max_rows; ++i) {
		for (int j = 0; j < max_cols; ++j) {
			T first = T{};
			T second = T{};

			if (i < a.getrows() && j < a.getcols()) {
				first = a(i, j);
			}
			if (i < b.getrows() && j < b.getcols()) {
				second = b(i, j);
			}
			result(i, j) = first - second;
		}
	}
	return result;
}
export template <typename T>
image<T> operator*(const image<T>& a, const int& num)
{
	image<T> result(a.getrows(), a.getcols(), false);
	for (int i = 0; i < a.getrows(); ++i)
	{
		for (int j = 0; j < a.getcols(); ++j)
		{
			result(i, j) = a(i, j) * num;
		}
	}
	return result;
}
export template <typename T>
image<T> operator+(const image<T>& a, const int& num)
{
	image<T> result(a.getrows(), a.getcols(), false);

	for (int i = 0; i < a.getrows(); ++i)
	{
		for (int j = 0; j < a.getcols(); ++j)
		{
			result(i, j) = a(i, j) + num;
		}
	}
	return result;
}
export template <typename T>
T invertedvalue(T value)
{
	if constexpr (std::is_same_v<T, bool>)
	{
		return !value;
	}
	else if constexpr (std::is_same_v<T, char>)
	{
		return -value;
	}
	return value;
}
export template <typename T>
image<T> operator!(const image<T>& a)
{
	image<T> result(a.getrows(), a.getcols(), false);
	for (int i = 0; i < a.getrows(); ++i)
	{
		for (int j = 0; j < a.getcols(); ++j)
		{
			result(i, j) = invertedvalue(a(i, j));
		}
	}
	return result;
}
export template <typename T>
bool operator==(const image<T>& a, const image<T>& b)
{
	if (a.getrows() != b.getrows() || a.getcols() != b.getcols())
	{
		return false;
	}
	for (int i = 0; i < a.getrows(); ++i)
	{
		for (int j = 0; j < a.getcols(); ++j)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				if (std::abs(a(i, j) - b(i, j)) > image<T>::epsilon)
				{
					return false;
				}
			}
			else
			{
				if (a(i, j) != b(i, j))
				{
					return false;
				}
			}
		}	
	}
	return true;
}
export template <typename T>
bool operator!=(const image<T>& a, const image<T>& b)
{
	return !(a == b);
}