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
    size_t _size = 0;
public:

    void push_back(const T& value)
    {
        Node* new_Node = new Node(value, _tail, nullptr);

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

    LinkedList() {};

    LinkedList(const LinkedList<T> &other) : _head(nullptr), _tail(nullptr), _size(0)
    {
        for (Node* cur = other._head; cur != nullptr; cur = cur->_next)
        {
            push_back(cur->_data);
        }
    }

    ~LinkedList()
    {
        Node* cur = _head;
        while (cur)
        {
            Node* next = cur->_next;
            delete cur;
            cur->next;
        }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        Node* cur = _head;
        while (cur)
        {
            Node* next = cur->_next;
            delete cur;
            cur->_next;
        }

        _head = nullptr;
        _tail = nullptr;
        _size = 0;

        for (Node* tmp = other._head;tmp  != nullptr; tmp= tmp->_next)
        {
            push_back(tmp->_data);
        }

        return *this;
    }

    LinkedList<T>& push_tail(const T &value)
    {
        Node* new_node = new Node(value, _tail, nullptr);
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
        Node* new_node = new Node(value, nullptr, _head);
        if (_head == nullptr)
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

    LinkedList<T>& pop_head(const T& value)
    {
        if (_head == nullptr)
        {
            return;
        }

        Node* cur = _head;


    }
};

template <typename T>
LinkedList<T>& LinkedList<T>::push_tail(const LinkedList<T>& other)
{
    for (Node* tmp = other._head; tmp != nullptr; tmp = tmp->_next)
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

    for (Node* tmp = other._tail; tmp != nullptr; tmp = tmp->_prev)
    {
        push_head(tmp->_data);
    }

    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
{
    for (const Node<T>* tmp = list._head; tmp != nullptr; tmp = tmp->_next)
    {
        out << tmp->_data << " ";
    }
    return out;
}