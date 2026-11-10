import std;

/*int count_Sym(char* s, char a)
{
	int counter = 0;

	for (int i = 0; i != '/0'; ++i)
	{
		if (s[i] == a)
		{
			counter++;
		}
	}
	return counter;
}
*/

/*bool palindrome(char* s)
{
	int size = 0;
	for (int i = 0; i != '/0'; ++i)
	{
		size++;
	}

	for (int i = 0; i < size/2; ++i)
	{
		if (s[i] != s[size-1-i])
		{
			return false;
		}
	}
	return true;
}*/

/*void length(const char* s)
{
	int size = 12;
    int max_counter = 0;
	
	for (int i = 0; i < size; ++i) 
	{
		int counter = 0;

		for (int j = 0; j < size; ++j)
		{
			if (s[i] == s[j])
			{
				counter++;
			}
		}
		if (max_counter < counter)
		{
			max_counter = counter;
		}
	}
	std::cout << max_counter;
}*/

/*void unique(const char* s) {
	int size = 0;

	for (int i = 0; s[i] != '\0'; ++i)
	{
		size++;
	}

	for (int i = 0; i < size; ++i)
	{
		int counter = 0;
		for (int j = 0; j < size; ++j) {
			if (s[i] == s[j])
			{
				counter++;
			}
		}
		if (counter == 1)
		{
			std::cout << s[i];
			break;
		}
	}
}*/
/*
int max_sub(char* s)
{
	int size = 0;
	int max = 0;
	int counter = 0;
	for (int i = 0; s[i] != '\0'; ++i)
	{
		size++;
	}

	for (int i = 0; s[i] != '\n'; ++i)
	{
		if (s[i] != ' ' || s[i + 1] != '\0')
		{
			counter++;
		}
		else
		{
			if (counter > max)
			{
				max = counter;
			}
			counter = 0;
		}
	}
	return max;
}*/

struct Pair {
	std::string key = "";
	int value = 0;
};

class Map {
private:
	Pair* _data = nullptr;
	int _size = 0;
	int _capacity = 0;
public:
	Map(int size) : _size(size), _data(new Pair[size]), _capacity(size * 2) {};
	Map(const Map& other) : _size(other._size), _capacity(other._capacity), _data(new Pair[other._size]) {
		for (int i = 0; i < other._size; ++i) {
			_data[i] = other._data[i];
		}
	}
	
	Map() {}

	~Map() {
		delete[] _data;
	}

	Map& operator=(const Map& other)
	{
		if (this == &other){
			return *this;
		}

		delete[] _data;
		_size = other._size;
		_capacity = other._capacity;
		_data = new Pair[other._size];

		for (int i = 0; i < other._size; ++i)
		{
			_data[i] = other._data[i];
		}
		return *this;
	}

	int operator[](std::string index)
	{
		for (int i = 0; i < _size; ++i)
		{
			if (_data[i].key == index)
			{
				return _data[i].value;
			}
		}
		throw std::out_of_range("такого ключа нет");
	}

	Map& operator+=(const Pair& p)
	{
		for (int i = 0; i < _size; ++i)
		{
			if (_data[i].key == p.key)
			{
				return *this;
			}
		}
		if (_size < _capacity)
		{
			_data[_size] = p;
		}
		else
		{
			_capacity *= 2;
			Pair* new_data = new Pair[_capacity];
			for (int i = 0; i < _size; ++i)
			{
				new_data[i] = _data[i];
			}
			delete[] _data;
			new_data[_size] = p;
			_data = new_data;
			_size++;
		}
		return *this;
	}

	Map operator+(const Map& other)
	{
		Map summ(_size + other._size);
		for (int i = 0; i < _size; i++)
		{
			summ._data[i] = _data[i];
		}
		int cnt{};
		for (int j = 0; j < other._size; ++j)
		{
			for (int k = 0; k < _size; ++k)
			{
				if (other._data[j] == _data[k]) 
				{
					cnt++;
					break;
				}
				summ._data[_size + j] = other._data[j];
			}
		}
		_size -= cnt;
	}

};



int main() {
	const char* str = "aaabbcddefeee";
	return 0;
}