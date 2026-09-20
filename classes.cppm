import std;
export module classes;

export template <typename T>
T randomValue()
{
	std::random_device seed;
	std::mt19937 generator(seed());

	if (std::is_same_v<T, bool>)
	{
		std::bernoulli_distribution distribution(0.5);
		return distribution(generator);
	}
	else if (std::is_same_v<T, char>)
	{
		std::uniform_int_distribution<int> distribution(1, 100);
		return static_cast<char>(distribution(generator));
	}
	else if (std::is_same_v<T, short>)
	{
		std::uniform_int_distribution<short> distribution(1, 100);
		return distribution(generator);
	}
	else if (std::is_same_v<T, float>)
	{
		std::uniform_real_distribution<float> distribution(1, 100);
		return distribution(generator) / 100.0f;
	}
	return T{};
}

export template <typename T>
T invertedValue(T value)
{
	return -value;
}

export template <typename T>
class Image 
{
private:
	int _rows = 0;
	int _cols = 0;
	T* _data = nullptr;
public:
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

	Image<T> operator*(const Image<T>& other)
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			if (_rows != other._rows || _cols != other._cols)
			{
				throw std::invalid_argument(
					"Bool images must have the same size"
				);
			}
			Image<T> result(_rows, _cols, false);

			for (int i = 0; i < _rows; ++i)
			{
				for (int j = 0; j < _cols; ++j)
				{
					result(i, j) = (*this)(i, j) && other(i, j);
				}
			}
			return result;
		}
		else {
			if (_cols != other._rows) {
				throw std::invalid_argument(
					"Cols must be the save size as the rows of the other matrix");
			}
			Image<T> result(_rows, other._cols, false);

			for (int i = 0; i < _rows; ++i) {
				for (int j = 0; j < other._cols; ++j) {

					T sum = T{};

					for (int k = 0; k < _cols; ++k) {
						sum += (*this)(i, k) * other(k, j);
					}
					result(i, j) = sum;
				}
			}
			return result;
		}
	}

	Image<T> operator+(const Image<T>& other) const
	{
		int max_rows = std::max(_rows, other._rows);
		int max_cols = std::max(_cols, other._cols);

		Image<T> result(max_rows, max_cols, false);

		for (int i = 0; i < max_rows; ++i) {
			for (int j = 0; j < max_cols; ++j) {
				T first = T{};
				T second = T{};

				if (i < _rows && j < _cols) {
					first = (*this)(i, j);
				}
				if (i < other._rows && j < other._cols) {
					second = other(i, j);
				}
				result(i, j) = first + second;
			}
		}
		return result;
	}

	Image<T> operator-(const Image<T>& other) const
	{
		int max_rows = std::max(_rows, other._rows);
		int max_cols = std::max(_cols, other._cols);

		Image<T> result(max_rows, max_cols, false);

		for (int i = 0; i < max_rows; ++i) {
			for (int j = 0; j < max_cols; ++j) {
				T first = T{};
				T second = T{};

				if (i < _rows && j < _cols) {
					first = (*this)(i, j);
				}
				if (i < other._rows && j < other._cols) {
					second = other(i, j);
				}
				result(i, j) = first - second;
			}
		}
		return result;
	}

	Image<T> operator*(const int& num) 
	{
		Image<T> result(_rows, _cols, false);

		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				result(i, j) = (*this)(i, j) * num;
			}
		}
		return result;
	}

	Image<T> operator+(const int& num)
	{
		Image<T> result(_rows, _cols, false);

		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				result(i, j) = (*this)(i, j) + num;
			}
		}
		return result;
	}

	Image<T> operator!() const 
	{
		Image<T> result(_rows, _cols, false);

		for (int i = 0; i < _rows; ++i) 
		{
			for (int j = 0; j < _cols; ++j) 
			{
				 result(i, j) = invertedValue((*this)(i, j));
			}
		}
		return result;
	}

	const double ratio(int _rows, int _cols) const {
		int sum = 0;
		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				sum += (*this)(i, j);
			}
		}

		float cells = _rows * _cols;
		float maxvalue = static_cast<float>(std::numeric_limits<T>::max());
		float result = (sum / (cells * maxvalue));
		return result;
	}

	~Image()
	{
		delete[] _data;
	}
};