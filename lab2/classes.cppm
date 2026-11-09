export module classes;
import std;

export template <typename T>
struct Node
{
    T _data{};
    Node* _next = nullptr;
    Node* _prev = nullptr;
    Node(T data, Node* next, Node* prev) : _data(data), _next(next), _prev(prev) {};
};

export template <typename T>
class LinkedList
{
private:
    Node<T>* _head = nullptr;
    Node<T>* _tail= nullptr;
    std::size_t _size = 0;
public:

    std::size_t size() const noexcept { return _size; }

    void push_back(const T& value)
    {
        Node<T>* new_Node = new Node<T>(value, nullptr, _tail);

        if (_tail != nullptr)
        {
            _tail->_next = new_Node;
        }
        else
        {
            _head = new_Node;
        }
        _tail = new_Node;
        ++_size;
    }

    LinkedList()=default;

    LinkedList(const LinkedList<T> &other) : _head(nullptr), _tail(nullptr), _size(0)
    {
        for (Node<T>* cur = other._head; cur != nullptr; cur = cur->_next)
        {
            push_back(cur->_data);
        }
    }

    ~LinkedList()
    {
        Node<T>* cur = _head;
        while (cur)
        {
            Node<T>* next = cur->_next;
            delete cur;
            cur = next;
        }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        Node<T>* cur = _head;
        while (cur)
        {
            Node<T>* next = cur->_next;
            delete cur;
            cur = next;
        }

        _head = nullptr;
        _tail = nullptr;
        _size = 0;

        for (Node<T>* tmp = other._head;tmp  != nullptr; tmp= tmp->_next)
        {
            push_back(tmp->_data);
        }

        return *this;
    }

    LinkedList<T>& push_tail(const T &value)
    {
        Node<T>* new_node = new Node<T>(value, nullptr, _tail);
        if (_tail != nullptr)
        {
            _tail->_next = new_node;
        }
        else
        {
            _head = new_node;
        }

        _tail = new_node;
        ++_size;
        return *this;
    }

    LinkedList<T>& push_tail(const LinkedList<T>& other);
    
    LinkedList<T>& push_head(const T& value)
    {
        Node<T>* new_node = new Node<T>(value, _head, nullptr);
        if (_head != nullptr)
        {
            _head->_prev = new_node;
        }
        else
        {
            _tail = new_node;
        }
        _head = new_node;
        ++_size;
        return *this;
    }

    LinkedList<T>& push_head(const LinkedList<T>& other);

    LinkedList<T>& pop_head()
    {
        if (_head == nullptr)
        {
            throw std::out_of_range("LinkedList::pop_head: empty list");
        }

        Node<T>* old_head = _head;
        _head = _head->_next;

        if (_head != nullptr)
        {
            _head->_prev = nullptr;
        }
        else
        {
            _tail = nullptr;
        }

        delete old_head;
        --_size;

        return *this;
    }

    LinkedList<T>& pop_tail()
    {
        if (_tail == nullptr)
        {
            throw std::out_of_range("LinkedList::pop_tail: empty list");
        }

        Node<T>* old_tail = _tail;
        _tail = _tail->_prev;

        if (_tail != nullptr)
        {
            _tail->_next = nullptr;
        }
        else
        {
            _head = nullptr;
        }

        delete old_tail;
        --_size;

        return *this;
    }

    LinkedList<T>& delete_specified(const T& delete_node)
    {
        if (_head == nullptr)
        {
            return *this;
        }

        Node<T>* cur = _head;
        while (cur)
        {
            Node<T>* next = cur->_next;
            if (cur->_data == delete_node)
            {
                if (cur->_prev != nullptr)
                {
                    cur->_prev->_next = cur->_next;
                }
                else
                {
                    _head = cur->_next;
                }
                if (cur->_next != nullptr)
                {
                    cur->_next->_prev = cur->_prev;
                }
                else
                {
                    _tail = cur->_prev;
                }
                delete cur;
                --_size;
            }
            cur = next;
        }
        return *this;
    }

    const T& read_by_idx(long long idx) const
    {
        if (_size == 0)
        {
            throw std::out_of_range("LinkedList index out of range");
        }
        long long n = static_cast<long long>(_size);
        long long r = idx % n;

        if (r < 0)
        {
            r += n;
        }

        Node<T>* cur = _head;
        for (long long i = 0; i < r; ++i)
        {
            cur = cur->_next;
        }
        return cur->_data;
    }

    T& write_by_idx(long long idx)
    {
        if (_size == 0)
        {
            throw std::out_of_range("LinkedList index out of range");
        }
        long long n = static_cast<long long>(_size);
        long long r = idx % n;

        if (r < 0)
        {
            r += n;
        }

        Node<T>* cur = _head;
        for (long long i = 0; i < r; ++i)
        {
            cur = cur->_next;
        }
        return cur->_data;
    }
};

template <typename T>
LinkedList<T>& LinkedList<T>::push_tail(const LinkedList<T>& other)
{
    for (Node<T>* tmp = other._head; tmp != nullptr; tmp = tmp->_next)
    {
        push_back(tmp->_data);
    }
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::push_head(const LinkedList<T>& other)
{
    if (this == &other)
    {
        return *this;
    }

    for (Node<T>* tmp = other._tail; tmp != nullptr; tmp = tmp->_prev)
    {
        push_head(tmp->_data);
    }

    return *this;
}

export template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
{
    for (std::size_t i = 0; i < list.size(); ++i)
    {
        if (i != 0) out << ' ';
        out << list.read_by_idx(i);
    }
    return out;
}

export template <typename T>
LinkedList<T> random_list(std::mt19937& generator, std::size_t count_nodes)
{
    return LinkedList<T>{};
}
template <>
LinkedList<int> random_list<int>(std::mt19937& generator, std::size_t count_nodes)
{
    std::uniform_int_distribution<int> distribution(0, 100);
    LinkedList<int> list;

    for (std::size_t i = 0; i < count_nodes; ++i)
    {
        int random_value = distribution(generator);
        list.push_tail(random_value);
    }
    return list;
}
template <>
LinkedList<double> random_list<double>(std::mt19937& generator, std::size_t count_nodes)
{
    std::uniform_real_distribution<double> distribution(0.0, 100.0);

    LinkedList<double> list;

    for (std::size_t i = 0; i < count_nodes; ++i)
    {
        double random_value = distribution(generator);
        list.push_tail(random_value);
    }

    return list;
}
template <>
LinkedList<short> random_list<short>(std::mt19937& generator, std::size_t count_nodes)
{
    std::uniform_int_distribution<short> distribution(0, 100);

    LinkedList<short> list;

    for (std::size_t i = 0; i < count_nodes; ++i)
    {
        short random_value = distribution(generator);
        list.push_tail(random_value);
    }

    return list;
}
template <>
LinkedList<float> random_list<float>(std::mt19937& generator, std::size_t count_nodes)
{
    std::uniform_real_distribution<float> distribution(0.0, 100.0f);

    LinkedList<float> list;

    for (std::size_t i = 0; i < count_nodes; ++i)
    {
        float random_value = distribution(generator);
        list.push_tail(random_value);
    }

    return list;
}