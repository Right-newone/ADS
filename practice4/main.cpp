import std;

struct {
    int _value = 0;
    Node* _next = nullptr;
    Node(int value, Node* next) : _value(value), _next(next){};
};

void add_idx(Node* head, int idx, int value)
{
    if (idx < 0)
    {
        return;
    }

    if (idx == 0)
    {
        Node* new_Node = new Node(value, nullptr);
        head = new_Node;
        return;
    }

    Node* cur = head;
    int cur_idx = 0;
    while(cur_idx < idx - 1 && cur->_next != nullptr)
    {
        cur = cur->_next;
        cur_idx++;        
    }

    Node* new_Node = new Node(value, nullptr);
    new_Node->_next = cur->_next;
    cur->_next = new_Node;
}

//Двусвязные списки

//Task 1
void print(Node* head)
{
    if (!head)
    {
        return;
    }
    Node* cur = head;

    while (cur)
    {  
        Node* r = cur->_next;
        while (r)
        {
            if (cur->_value == r->_value) {
                std::cout << cur->_value << "\n";
            }
            r = r->_next;
        }
        cur = cur->_next;
    }
    return;
}

//Task 2
//10->15->20->30->nullptr
//<-10 15->20->30->nullptr
//<-10<-15 20->30->nullptr
void reverse(Node* head) {
    Node* cur = head;
    Node* prev = nullptr;

    while (cur)
    {
        Node* next = cur->_next;
        cur->_next = prev;
        prev = cur;
        cur = cur->_next;
    }
    head = prev;
}

//Task 3
void copyright(Node* head) {
    Node* new_Node = new Node(head->_value, nullptr);
    Node* cur = head;
    while (cur)
    {
        Node next = new_Node(cur->_next->_value);
        tail-> - next;
        cur = cur->_next;
        tail = next;
    }
    return new_Node;
}
int main () {
    std::cout << "Hello world";
}