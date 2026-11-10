import std;
// Двусвязные списки
// Node {
//	int val;
//	Node* next;
//	Node* prev;
//}

// Односвязные списки
// head -> value 1 элемент
// head -> next 2 эл-т
// head -> next next 3 эл-т и т.д.
// Node {
//	int val;
//	Node* next;
//  cur = cur -> next;
//}

// Task 1
struct Node 
{
	int _value;
	Node* _next;

	Node(int val, Node* next) : _value(val), _next(next) {}
};

void print_positive(Node* head)
{
	Node* cur = head;

	while (cur != nullptr)
	{
		if (cur -> _value > 0)
		{
			std::println("Положит знач: {}", cur -> _value);
		}
		cur = cur->_next;
	}
}

// Task 2
int count_even(Node* head)
{
	Node* cur = head;
	int result = 0;

	while (cur)
	{
		if (cur->_value % 2 == 0)
		{
			result += 1;
		}
		cur = cur->_next;
	}
	return result;
}

// Task 3
bool is_ordered(Node* head)
{
	if (!head)
	{
		return true;
	}

	Node* cur = head;
	while (cur->_next)
	{
		if (cur->_value < cur->_next->_value)
		{
			return true;
		}
		cur = cur->_next;
	}
	return true;
}

// Task 4
void Add(Node* head, int element)
{
	Node* n_element = new Node(element, nullptr);

	if (!head)
	{
		head = n_element;
		return;
	}
	Node* cur = head;
	while (cur ->_next)
	{
		cur = cur->_next;
	}
	
	cur->_next = n_element;
}

// Task 5
void remove(Node* head)
{
	if (!head)
	{
		return;
	}
	if (!(head->_next))
	{
		delete[] head;
		head = nullptr;
		return;
	}
	Node* cur = head;
	while (cur ->_next->_next)
	{
		cur = cur->_next;
	}
	delete[] cur->_next;
	cur->_next = nullptr;
}

// Task 6
int count_el(Node* head, int data)
{
	int counter = 0;
	Node* cur = head;

	while (cur)
	{
		if (cur->_value == data)
		{
			counter++;
		}
		cur = cur->_next;
	}
	return counter;
}

// Дз к доске 2 рандома 
// 1. Выч сред ариф списка
double average(Node* head)
{
	if (!head)
	{
		return 0.0;
	}
	double sum = 0;
	int counter = 0;
	Node* cur = head;

	while (cur->_next)
	{
		sum += cur->_value;
		counter++;
		cur = cur->_next;
	}
	return sum / counter;
}

// 2. вставка эл-та по произв индексу
void add_idx(Node* head, int value, int idx)
{
	if (idx < 0)
	{
		throw std::out_of_range("Index cannot be negative");
	}

	Node* new_value = new Node(value, nullptr);

	if (idx == 0)
	{
		new_value->_next = head;
		head = new_value;
		return;
	}

	Node* cur = head;
	int cur_index = 0;

	while (cur || cur_index < idx)
	{
		cur = cur->_next;
		cur_index++;
	}

	if (cur)
	{
		delete[] new_value;
	}

	new_value = cur->_next;
	cur->_next = new_value;
}

// 3. Удаление эл-та из произв индекса
void del(Node* head, int idx)
{
	if (idx < 0)
	{
		throw std::out_of_range("Index cannot be negative");
	}

	if (head == nullptr)
	{
		throw std::out_of_range("List is empty");
	}

	if (idx == 0)
	{
		Node* temp = head;
		head = head->_next;
		delete[] temp;
		return;
	}

	Node* cur = head;
	int cur_index = 0;
	while (cur || cur_index < idx - 1)
	{
		cur = cur->_next;
		cur_index++;
	}

	Node* del = head;
	head->_next = del;
	delete del;
}

int main() {
	return 0;
}