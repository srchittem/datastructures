#include "iostream"
using namespace std;

class node
{
    int data;
    class node* next;
public:
    node(int i);
    ~node();
    int getData() {return data;}
    void setData(int i) {data = i;}
    node* getNext() {return next;}
    void setNext(node *newNext) {next = newNext;}
};


node::node(int i)
{
    data = i;
    next = NULL;
}

node::~node()
{

}


class list
{
    class node *Head;
    class node *Tail;
public:
    list();
    ~list();
    void appendAtEnd(node *newNode);
    void appendAtStart(node *newNode);
    void printList();
    void swapEvenOdd();
    void iterativeReverse();
};


list::list()
{
    Head = NULL;
    Tail = NULL;

}

list::~list()
{

}


void list::appendAtStart(node *newNode)
{
    if(Head == NULL)
    {
        Head = newNode;
    }
    else
    {
        newNode->setNext(Head);
        Head = newNode;
    }

}


void list::appendAtEnd(node *newNode)
{
    if(Head == NULL)
    {
        Head = newNode;
    }
    else
    {
        node *temp = Head;
        while(temp->getNext())
        {
            temp= temp->getNext();
        }

        temp->setNext(newNode);
    }
}


void list::printList()
{
    node *temp = Head;
    cout <<endl;
    while(temp)
    {
        cout << temp->getData() <<"->";
        temp = temp->getNext();
    }
    cout<< "N" << endl;
}

void list::iterativeReverse()
{
    node *cur = Head->getNext();
    while(cur->getNext())
    {
        Head->setNext(cur->getNext());
        cur->setNext(Head);
        node *temp = Head;
        Head = cur;
        cur = temp->getNext();
    }

}

void list::swapEvenOdd()
{
    node *odd = Head , *even = Head->getNext();
    while(even && even->getNext())
    {
        node *temp = odd->getNext();
        odd->setNext(even->getNext());
        even->setNext(odd->getNext()->getNext());
        odd->getNext()->setNext(temp);

        odd = odd->getNext();
        even = even->getNext();
    }

}


int main()
{
    list list1;
    node node1(1), node2(2), node3(3), node4(4), node5(5);
    node node6(6), node7(7), node8(8), node9(9);

    list1.appendAtStart(&node3);
    list1.appendAtStart(&node2);
    list1.appendAtStart(&node1);
    list1.appendAtEnd(&node4);
    list1.appendAtEnd(&node5);
    list1.appendAtEnd(&node6);
    list1.appendAtEnd(&node7);
    list1.appendAtEnd(&node8);
    list1.appendAtEnd(&node9);

    cout << "before reversing:";
    list1.printList();

    //list1.swapEvenOdd();

    list1.iterativeReverse();

    cout << "after swapping:";

    list1.printList();
}
