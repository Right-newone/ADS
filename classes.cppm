import std;
export module classes;

export template <typename T>
T randomValue()
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
		return distribution(generator) / 100.0f;
	}
	return T{};
}

export template <typename T>
class Image 
{
private:
	int _rows = 0;
	int _cols = 0;
	T* _data = nullptr;
public:
	static constexpr double EPSILON = 1e-6;
	Image(int rows, int cols, bool randomFill) : _rows(rows), _cols(cols) 
	{
		if (rows <= 0 || cols <= 0)
		{
			throw std::invalid_argument("Image dimensions must be positive");
		}
		_data = new T[_rows * _cols]{};

		if (_data == nullptr)
		{
			throw std::bad_alloc();
		}

		if (!randomFill)
		{
			for (int i = 0; i < _rows * _cols; ++i)
			{
				_data[i] = T{};
			}
		}

		else 
		{
			for (int i = 0; i < _rows * _cols; ++i)
			{
				_data[i] = randomValue<T>();
			}
		}
	}

	Image(const Image& other)
		: _rows(other._rows),
		_cols(other._cols),
		_data(new T[other._rows * other._cols])
	{
		for (int i = 0; i < _rows * _cols; ++i)
		{
			_data[i] = other._data[i];
		}
	}

	Image& operator=(const Image& other)
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

	int get_rows() const
	{
		return _rows;
	}

	int get_cols() const
	{
		return _cols;
	}

	T& operator()(int row, int col)
	{
		if (row < 0 || row >= _rows ||
			col < 0 || col >= _cols)
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

	~Image()
	{
		delete[] _data;
	}
};

export template <typename T>
T invertedValue(T value)
{
	return -value;
}

export template <typename T>
std::ostream& operator<<(std::ostream& out, const Image<T>& image)
{
	for (int i = 0; i < image.get_rows(); ++i)
	{
		for (int j = 0; j < image.get_cols(); ++j)
		{
			out << image(i, j) << " ";
		}

		out << "\n";
	}

	return out;
}

export template <typename T>
Image<T> operator*(const Image<T>& a, const Image<T>& b)
{
	if constexpr (std::is_same_v<T, bool>)
	{
		if (a.get_rows() != b.get_rows() || a.get_cols() != b.get_cols())
		{
			throw std::invalid_argument(
				"Bool images must have the same size"
			);
		}
		Image<T> result(a.get_rows(), b.get_cols(), false);

		for (int i = 0; i < a.get_rows(); ++i)
		{
			for (int j = 0; j < a.get_cols(); ++j)
			{
				result(i, j) = a(i, j) && b(i, j);
			}
		}
		return result;
	}
	else {
		if (a.get_cols() != b.get_rows()) {
			throw std::invalid_argument(
				"Cols must be the save size as the rows of the other matrix");
		}
		Image<T> result(a.get_rows(), b.get_cols(), false);

		for (int i = 0; i < a.get_rows(); ++i) {
			for (int j = 0; j < b.get_cols(); ++j) {

				T sum = T{};

				for (int k = 0; k < a.get_cols(); ++k) {
					sum += a(i, k) * b(k, j);
				}
				result(i, j) = sum;
			}
		}
		return result;
	}
}

export template <typename T>
Image<T> operator+(const Image<T>& a, const Image<T>& b)
{
	int max_rows = std::max(a.get_rows(), b.get_rows());
	int max_cols = std::max(a.get_cols(), b.get_cols());

	Image<T> result(max_rows, max_cols, false);

	for (int i = 0; i < max_rows; ++i) {
		for (int j = 0; j < max_cols; ++j) {
			T first = T{};
			T second = T{};

			if (i < a.get_rows() && j < a.get_cols()) {
				first = a(i, j);
			}
			if (i < b.get_rows() && j < b.get_cols()) {
				second = b(i, j);
			}
			result(i, j) = first + second;
		}
	}
	return result;
}

export template <typename T>
Image<T> operator-(const Image<T>& a, const Image<T>& b)
{
	int max_rows = std::max(a.get_rows(), b.get_rows());
	int max_cols = std::max(a.get_cols(), b.get_cols());

	Image<T> result(max_rows, max_cols, false);

	for (int i = 0; i < max_rows; ++i) {
		for (int j = 0; j < max_cols; ++j) {
			T first = T{};
			T second = T{};

			if (i < a.get_rows() && j < a.get_cols()) {
				first = a(i, j);
			}
			if (i < b.get_rows() && j < b.get_cols()) {
				second = b(i, j);
			}
			result(i, j) = first - second;
		}
	}
	return result;
}

export template <typename T>
Image<T> operator*(const Image<T>& a, const int& num)
{
	Image<T> result(a.get_rows(), a.get_cols(), false);

	for (int i = 0; i < a.get_rows(); ++i)
	{
		for (int j = 0; j < a.get_cols(); ++j)
		{
			result(i, j) = a(i, j) * num;
		}
	}
	return result;
}

export template <typename T>
Image<T> operator+(const Image<T>& a, const int& num)
{
	Image<T> result(a.get_rows(), a.get_cols(), false);

	for (int i = 0; i < a.get_rows(); ++i)
	{
		for (int j = 0; j < a.get_cols(); ++j)
		{
			result(i, j) = a(i, j) + num;
		}
	}
	return result;
}

export template <typename T>
Image<T> operator!(const Image<T>& a)
{
	Image<T> result(a.get_rows(), a.get_cols(), false);

	for (int i = 0; i < a.get_rows(); ++i)
	{
		for (int j = 0; j < a.get_cols(); ++j)
		{
			result(i, j) = invertedValue(a(i, j));
		}
	}
	return result;
}

export template <typename T>
bool operator==(const Image<T>& a, const Image<T>& b)
{
	if (a.get_rows() != b.get_rows() ||
		a.get_cols() != b.get_cols())
	{
		return false;
	}

	for (int i = 0; i < a.get_rows(); ++i)
	{
		for (int j = 0; j < a.get_cols(); ++j)
		{
			if constexpr (std::is_floating_point_v<T>)
			{
				if (std::abs(a(i, j) - b(i, j)) > Image<T>::EPSILON)
					return false;
			}
			else
			{
				if (a(i, j) != b(i, j))
					return false;
			}
		}	
	}

	return true;
}

export template <typename T>
bool operator!=(const Image<T>& a, const Image<T>& b)
{
	return !(a == b);
}