export module functions;
import std;
import classes;

export void generation_list1(std::mt19937& generator, std::size_t& count_nodes)
{
	unsigned int seed;
	std::cout << "Enter your seed for list 1: ";
	std::cin >> seed;

	generator.seed(seed);

	std::cout << "Enter your ammount of nodes for list 1: ";
	std::cin >> count_nodes;
}
export void generation_list2(std::mt19937& generator2, std::size_t& count_nodes2)
{
	unsigned int seed2;
	std::cout << "Enter your seed for list 2: ";
	std::cin >> seed2;

	generator2.seed(seed2);

	std::cout << "Enter your ammount of nodes for list 2: ";
	std::cin >> count_nodes2;
}
export void assign()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);

	std::mt19937 generator2;
	std::size_t count_nodes2 = 0;
	generation_list2(generator2, count_nodes2);

	LinkedList<int> list2 = random_list<int>(generator2, count_nodes2);

	std::cout << "list: " << list << std::endl;
	std::cout << "list2: " << list2 << std::endl;
	list = list2;
	std::cout << "After assignment" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void push_tail_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);
	std::cout << "list: " << list << std::endl;
	
	int value = 0;
	std::cout << "Enter your value: ";
	std::cin >> value;

	list.push_tail(value);

	std::cout << "After push_tail" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void push_tail_list_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);
	
	LinkedList<int> list = random_list<int>(generator, count_nodes);
	
	std::mt19937 generator2;
	std::size_t count_nodes2 = 0;
	generation_list2(generator2, count_nodes2);

	LinkedList<int> list2 = random_list<int>(generator2, count_nodes2);

	std::cout << "list2: " << list2 << std::endl;
	std::cout << "list: " << list << std::endl;

	list.push_tail(list2);

	std::cout << "After push_tail_list" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void push_head_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);
	std::cout << "list: " << list << std::endl;

	int value = 0;
	std::cout << "Enter your value: ";
	std::cin >> value;

	list.push_head(value);

	std::cout << "After push_head" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void push_head_list_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);

	std::mt19937 generator2;
	std::size_t count_nodes2 = 0;
	generation_list2(generator2, count_nodes2);

	LinkedList<int> list2 = random_list<int>(generator2, count_nodes2);

	std::cout << "list2: " << list2 << std::endl;
	std::cout << "list: " << list << std::endl;

	list.push_tail(list2);

	std::cout << "After push_head_list" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void pop_head_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);
	std::cout << "list: " << list << std::endl;

	list.pop_head();

	std::cout << "After pop_head" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void pop_tail_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);
	std::cout << "list: " << list << std::endl;

	list.pop_tail();

	std::cout << "After pop_tail" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void delete_node_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);
	std::cout << "list: " << list << std::endl;

	int value = 0;
	std::cout << "Enter your value to delete: ";
	std::cin >> value;
	list.delete_specified(value);

	std::cout << "After delete_specified" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void read_by_idx_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);

	long long idx = 0;
	std::cout << "Enter your idx to read from: ";
	std::cin >> idx;

	int value = list.read_by_idx(idx);
	std::cout << "Value at index" << idx << " is: " << value << '\n';

	std::cout << "Full list: " << list << '\n';
}

export void write_by_idx_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);

	std::cout << "Initial list: " << list << std::endl;

	long long idx = 0;
	std::cout << "Enter your idx to write to: ";
	std::cin >> idx;

	int new_value = 0;
	std::cout << "Enter new value to put at this index: ";
	std::cin >> new_value;
	
	list.write_by_idx(idx) = new_value;

	std::cout << "After write_by_idx" << std::endl;
	std::cout << "list: " << list << std::endl;
}

export void output_demo()
{
	std::mt19937 generator;
	std::size_t count_nodes = 0;
	generation_list1(generator, count_nodes);

	LinkedList<int> list = random_list<int>(generator, count_nodes);

	std::cout << "output of the list: " << list << std::endl;
}