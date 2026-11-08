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
            _tail->_next = new_node;
        }
        else
        {
            _head = new_node;
        }
        _tail = new_node;
        ++_size;
    }

    LinkedList() {};

    LinkedList(const LinkedList &other) : _head(nullptr), _tail(nullptr), _size(0)
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
            delete cur;
            cur->_next;
        }
    }

    LinkedList& LinkedList(const LinkedList& other)
    {
        if (*this == other)
        {
            return this;
        }

        return this;
    }

};