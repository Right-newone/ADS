export module classes;
import std;

export template <typename T>
T randomvalue()
{
	T{};
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
	std::uniform_int_distribution<int> distribution(1, 100);
	return static_cast<char>(distribution(generator));
}
template<>
short randomvalue<short>(){
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_int_distribution<short> distribution(1, 100);
	return distribution(generator);
}
template<>
float randomvalue<float>(){
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_real_distribution<float> distribution(1, 100);
	return distribution(generator);
}

export template<typename T>
T invertedvalue(T value)
{
	return -value;
}
template<>
bool invertedvalue<bool>(bool value){
	return !value;
}

export template <typename T>
class image
{
private:
	int _rows = 0;
	int _cols = 0;
	T* _data = nullptr;
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
	template <typename T>
	image<T> mult(const image<T>& a) {
		if (a._rows != _rows || a._cols != _cols)
		{
			throw std::invalid_argument("Bool images must have the same size");
		}
		image<bool> result(_rows, _cols, false);

		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				result(i, j) = a(i, j) && (*this)(i, j);
			}
		}
		return result;
	}

	image<T> operator*(const image<T>& a)
	{
		if (a._cols != _rows) {
			throw std::invalid_argument("Cols must be the save size as the rows of the other matrix");
		}
		image<T> result(a._rows, _cols, false);
		for (int i = 0; i < a._rows; ++i) {
			for (int j = 0; j < _cols; ++j) {

				T sum = T{};

				for (int k = 0; k < a._cols; ++k) {
					sum += a(i, k) * (*this)(k, j);
				}
				result(i, j) = sum;
			}
		}
		return result;
	}

	image<T> operator+(const image<T>& a)
	{
		int max_rows = std::max(a._rows, _rows);
		int max_cols = std::max(a._cols, _cols);
		image<T> result(max_rows, max_cols, false);
		for (int i = 0; i < max_rows; ++i)
		{
			for (int j = 0; j < max_cols; ++j)
			{
				T first = T{};
				T second = T{};
				if (i < a._rows && j < a._cols)
				{
					first = a(i, j);
				}
				if (i < _rows && j < _cols)
				{
					second = (*this)(i, j);
				}
				result(i, j) = first + second;
			}
		}
		return result;
	}

	image<T> operator-(const image<T>& a)
	{
		int max_rows = std::max(a._rows, _rows);
		int max_cols = std::max(a._cols, _cols);
		image<T> result(max_rows, max_cols, false);
		for (int i = 0; i < max_rows; ++i) {
			for (int j = 0; j < max_cols; ++j) {
				T first = T{};
				T second = T{};

				if (i < a._rows && j < a._cols) {
					first = a(i, j);
				}
				if (i < _rows && j < _cols) {
					second = (i, j);
				}
				result(i, j) = first - second;
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
				result(i, j) = (i, j) * num;
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
				result(i, j) = (i, j) + num;
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
				result(i, j) = invertedvalue((i, j));
			}
		}
		return result;
	}
	template <typename T>
	bool equal(const T&a, const T& b, double epsilon) {
		return a == b;
	}
	bool equal(float a, float b, double epsilon) {
		return std::abs(a - b) <= epsilon;
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
std::ostream& operator<<(std::ostream& out, const image<T>& image)
{
	for (int i = 0; i < image.getrows(); ++i)
	{
		for (int j = 0; j < image.getcols(); ++j)
		{
			out << image(i, j) << " ";

		}
		out << "\n";
	}
	return out;
}