#include <iostream>
#include <memory>
#include <assert.h>

using namespace std;

class Node
{
public:
    Node(const int v) :
        next(nullptr),
        value(v)
    {}
    Node(Node &other){
        next = move(other.next);
        value = other.value;
    }

    unique_ptr<Node> next;
    int value;
};

class List
{
public:
    List();
    void add(unique_ptr<Node> node);
    unique_ptr<Node> get(const int value);
    void print();

private:
    unique_ptr<Node> first;
};

List::List() :
    first(nullptr)
{}

void List::add(unique_ptr<Node> node)
{
    if(first == nullptr)
    {
        first = move(node);
    }
    else
    {
        Node * current = first.get();
        while(current->next)
        {
            current = current->next.get();
        }
        current->next = move(node);
    }
}

unique_ptr<Node> List::get(const int value)
{
    if(first == nullptr)
    {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    else
    {
        Node * current = first.get();
        do
        {
            if(current->value == value)
            {
                cout << "Found value " << current->value << endl;
                return make_unique<Node>(*current);
            }
            else
            {
                cout << "Going through " << current->value << endl;
                current = current->next.get();
            }
        } while(current);
        cout << "Not found: value " << value << endl;
        return nullptr;
    }
}

void List::print(void)
{
    cout << __func__ << ": " << endl;
    Node * current = first.get();
    while(current)
    {
        cout << "ptr: " << current << ", value: " << current->value << endl;
        current = current->next.get();
    }
}

int main()
{
    auto node4 = make_unique<Node>(4);
    auto node5 = make_unique<Node>(5);
    auto node6 = make_unique<Node>(6);
    auto node7 = make_unique<Node>(7);

    List lista;
    lista.add(move(node4));
    lista.add(move(node5));
    lista.add(move(node6));
    lista.add(move(node7));
    lista.print();
    auto node = lista.get(1);

    if (node)
        cout << node->value << '\n';

    return 0;
}

