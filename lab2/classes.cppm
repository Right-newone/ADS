    export module classes;
    import std;

    export template <typename T>
    struct Node
    {
        T _data = T();
        Node* _next = nullptr;
        Node* _prev = nullptr;
        Node(const T& data, Node* next, Node* prev) : _data(data), _next(next), _prev(prev) {};
    };

    export template <typename T>
    class LinkedList
    {
    private:
        Node<T>* _head = nullptr;
        Node<T>* _tail= nullptr;
        std::size_t _size = 0;
    public:

        std::size_t size() const noexcept
        {
            return _size; 
        }

        Node<T>* get_head() const noexcept
        {
            return _head;
        }

        Node<T>* get_tail() const noexcept
        {
            return _tail;
        }

        LinkedList<T>& push_tail(const T& value)
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
            _tail->_next = _head;
            _head->_prev = _tail;
            ++_size;
            return *this;
        }

        LinkedList()=default;

        LinkedList(const LinkedList<T> &other) : _head(nullptr), _tail(nullptr), _size(0)
        {
            Node<T>* cur = other._head;
            for (std::size_t i = 0; i < other._size; ++i)
            {
                push_tail(cur->_data);
                cur = cur->_next;
            }
        }

        ~LinkedList()
        {
            Node<T>* cur = _head;
            for (std::size_t i = 0; i < _size; ++i)
            {
                Node<T>* next = cur->_next;
                delete cur;
                cur = next;
            }
            _head = nullptr;
            _tail = nullptr;
            _size = 0;
        }

        LinkedList<T>& operator=(const LinkedList<T>& other)
        {
            if (this == &other)
            {
                return *this;
            }

            Node<T>* cur = _head;
            for (std::size_t i = 0; i < _size; ++i)
            {
                Node<T>* next = cur->_next;
                delete cur;
                cur = next;
            }

            _head = nullptr;
            _tail = nullptr;
            _size = 0;

            Node<T>* tmp = other._head;
            for (std::size_t i = 0; i < other._size; ++i)
            {
                push_tail(tmp->_data);
                tmp = tmp->_next;
            }

            return *this;
        }

        LinkedList<T>& push_tail(const LinkedList<T>& other);
    
        LinkedList<T>& push_head(const T& value)
        {
            Node<T>* new_node = new Node<T>(value, _head, _tail);
            if (_head != nullptr)
            {
                _head->_prev = new_node;
            }
            else
            {
                _tail = new_node;
            }
            _head = new_node;
            _tail->_next = _head;
            _head->_prev = _tail;
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

            if (_size == 1)
            {
                delete _head;
                _head = nullptr;
                _tail = nullptr;
                --_size;
                return *this;
            }

            Node<T>* old_head = _head;
            _head = _head->_next;

            _head->_prev = _tail;
            _tail->_next = _head;

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
            if (_size == 1)
            {
                delete _head;
                _head = nullptr;
                _tail = nullptr;
                --_size;
            }

            else
            {
                Node<T>* old_tail = _tail;
                _tail = _tail->_prev;

                _head->_prev = _tail;
                _tail->_next = _head;
                delete old_tail;
                --_size;
            }

            return *this;
        }

        LinkedList<T>& delete_specified(const T& delete_node)
        {
            if (_head == nullptr)
            {
                return *this;
            }

            std::size_t initial_size = _size;
            Node<T>* cur = _head;
            for (std::size_t i = 0; i < initial_size && _head != nullptr; ++i)
            {
                Node<T>* next = cur->_next; 

                if (cur->_data == delete_node)
                {
                    if (_size == 1)
                    {
                        delete cur;
                        _head = nullptr;
                        _tail = nullptr;
                        _size = 0;
                        break;
                    }
                    cur->_prev->_next = cur->_next;
                    cur->_next->_prev = cur->_prev;

                    if (cur == _head)
                    {
                        _head = cur->_next;
                    }
                    if (cur == _tail)
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

        LinkedList<T>& reversed_list()
        {
            if (_head == nullptr)
            {
                return *this;
            }

            Node<T>* cur = _head;
            Node<T>* tmp= nullptr;
            do
            {
                std::swap(cur->_next, cur->_prev);
                cur = cur->_prev;
            } while (cur != _head);
            std::swap(_head, _tail);
            return *this;
        }
    };

    template <typename T>
    LinkedList<T>& LinkedList<T>::push_tail(const LinkedList<T>& other)
    {
        std::size_t count = other.size();
        Node<T>* tmp = other.get_head();
        for (std::size_t i = 0; i < count; ++i)
        {
            push_tail(tmp->_data);
            tmp = tmp->_next;
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
        std::size_t count = other.size();
        Node<T>* tmp = other.get_tail();
        for (std::size_t i = 0; i < count; ++i)
        {
            push_head(tmp->_data);
            tmp = tmp->_prev;
        }

        return *this;
    }

    export template <typename T>
    std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
    {
        if (list.get_head() == nullptr && list.get_tail() == nullptr)
        {
            out << "[]";
            return out;
        }

        Node<T>* cur = list.get_head();
        do
        {
            out << cur->_data << " ";
            cur = cur->_next;
        } while (cur != list.get_head());
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