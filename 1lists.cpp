#include <iostream>
#include <cstdlib>
#include <list>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


struct Node
{
    int data;
    Node* next;
};

Node* createNode(int value) 
{
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Error: Memory is not allocated." << endl;
        exit(0);
    }
    newNode->data = value;
    newNode->next = nullptr;
    return newNode;
}

Node* inputUnorderedlist(int length)
{
    Node* head = nullptr;
    for (int i = 0; i < length; i++)
    {
        int value = rand() % 100;
        Node* newNode = createNode(value);

        newNode->next = head;
        head = newNode;
    }
    return head;
}

Node* inputorderedlist(int length) 
{
    Node* head = nullptr;
    for (int i = 0; i < length; i++) 
    {
        int value = rand() % 100;
        Node* newNode = createNode(value);
        if (head == nullptr || newNode->data < head->data)
        {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != nullptr && current->next->data < newNode->data) 
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    return head;
}

Node* mergeLists(Node* list1, Node* list2) 
{
    static Node dummy;
    Node* tail = &dummy;
    dummy.next = nullptr;

    while (list1 != nullptr && list2 != nullptr) 
    {
        if (list1->data <= list2->data) 
        {
            tail->next = list1;
            list1 = list1->next;
        }
        else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != nullptr)
        tail->next = list1;
    else
        tail->next = list2;

    return dummy.next;
}

void printList(Node* head) 
{
    Node* current = head;
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void deleteList(Node* head) 
{
    Node* current = head;
    while (current != nullptr) 
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void swapMinMax(Node* head) 
{
    if (head == nullptr || head->next == nullptr)
        return;

    Node* minNode = head;
    Node* maxNode = head;
    Node* current = head->next;

    while (current != nullptr) 
    {
        if (current->data < minNode->data)
            minNode = current;
        if (current->data > maxNode->data)
            maxNode = current;
        current = current->next;
    }

    swap(minNode->data, maxNode->data);
}

struct Stack 
{
    int value;
    Stack* next;
};

void stackOperations() 
{
    int length;
    cout << "Enter the number of items in the list: ";
    cin >> length;

    stack<int> stack;

    for (int i = 0; i < length; i++) 
    {
        int value = rand() % 100;
        stack.push(value);
        cout << "Element has been added " << value << " to the stack." << endl;
    }

    cout << "The intermediate state of the stack: ";
    std::stack<int> tempStack = stack;

    while (!tempStack.empty()) 
    {
        cout << tempStack.top() << " ";
        tempStack.pop();
    }

    cout << endl;
    
}

void insertionSortList(Node*& head) 
{
    if (head == nullptr || head->next == nullptr)
        return;

    Node* sortedList = nullptr;
    Node* current = head;

    while (current != nullptr) 
    {
        Node* nextNode = current->next;
        current->next = nullptr;

        if (sortedList == nullptr || current->data <= sortedList->data) 
        {
            current->next = sortedList;
            sortedList = current;
        }
        else 
        {
            Node* temp = sortedList;
            while (temp->next != nullptr && temp->next->data < current->data) 
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = nextNode;
    }

    head = sortedList;
}

void dfs(vector<vector<int>>& graph, int vertex, vector<bool>& visited, vector<int>& result) 
{
    visited[vertex] = true;
    result.push_back(vertex);
    for (int i = 0; i < graph.size(); i++) 
    {
        if (graph[vertex][i] && !visited[i]) 
        {
            dfs(graph, i, visited, result);
        }
    }
}

void bfs(vector<vector<int>>& graph, int startVertex, vector<int>& result) 
{
    vector<bool> visited(graph.size(), false);
    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty()) 
    {
        int currentVertex = q.front();
        q.pop();
        result.push_back(currentVertex);

        for (int i = 0; i < graph.size(); i++) 
        {
            if (graph[currentVertex][i] && !visited[i]) 
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void topologicalSort(vector<vector<int>>& graph, vector<int>& indegree) 
{
    int V = graph.size();
    vector<int> sortedOrder;
    queue<int> sources;

    for (int i = 0; i < V; i++) 
    {
        for (int j = 0; j < graph[i].size(); j++) 
        {
            indegree[graph[i][j]]++;
        }
    }
    for (int i = 0; i < V; i++) 
    {
        if (indegree[i] == 0)
            sources.push(i);
    }

    while (!sources.empty()) 
    {
        int vertex = sources.front();
        sources.pop();
        sortedOrder.push_back(vertex);
        for (int i = 0; i < graph[vertex].size(); i++) 
        {
            int child = graph[vertex][i];
            indegree[child]--;
            if (indegree[child] == 0)
                sources.push(child);
        }
    }

    if (sortedOrder.size() != V) 
    {
        cout << "The graph contains cycles!" << endl;
        return;
    }

    cout << "Topological sorting of the graph: ";
    for (int i = 0; i < sortedOrder.size(); i++) 
    {
        cout << sortedOrder[i] << " ";
    }
    cout << endl;
}

int main() 
{
    int choice;
    int length1, length2;

    while (true) 
    {
        cout << "Tasks:" << endl;
        cout << "1) Merging two ordered singly linked lists" << endl;
        cout << "2) Implementation of permutation of the maximum and minimum elements of the list" << endl;
        cout << "3) Stack implementation on a singly linked list" << endl;
        cout << "4) Implementation of sorting by simple insertion on a singly linked list" << endl;
        cout << "5) Traversing the graph \"in depth\" and \"in width\"" << endl;
        cout << "6) Topological sorting of graph vertices" << endl;
        cout << "7) Exit" << endl;
        cout << "Enter the task number: ";
        cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            cout << "Enter the lengths of the two ordered lists: ";
            cin >> length1 >> length2;
            Node* list1 = inputorderedlist(length1);
            Node* list2 = inputorderedlist(length2);
            cout << "The first list: ";
            printList(list1);
            cout << "The second list: ";
            printList(list2);
            Node* mergedList = mergeLists(list1, list2);
            cout << "Combined Ordered list: ";
            printList(mergedList);
            deleteList(mergedList);
            break;
        }
        case 2: 
        {
            cout << "Enter the length of the list: ";
            cin >> length1;
            Node* list = inputUnorderedlist(length1);
            cout << "The original list: ";
            printList(list);
            swapMinMax(list);
            cout << "A list with the maximum and minimum numbers rearranged: ";
            printList(list);
            deleteList(list);
            break;
        }
        case 3: 
        {
            stackOperations();
            break;
            
        }
        case 4: 
        {
            cout << "Enter the length of the list: ";
            cin >> length1;
            Node* list = inputorderedlist(length1);
            cout << "The original list: ";
            printList(list);
            insertionSortList(list);
            cout << "An ordered list: ";
            printList(list);
            deleteList(list);
            break;
        }
        case 5: 
        {
            int numVertices;
            cout << "Enter the number of vertices: ";
            cin >> numVertices;
            vector<vector<int>> graph(numVertices, vector<int>(numVertices));
            cout << "Enter the adjacency matrix of the graph:" << endl;
            for (int i = 0; i < numVertices; i++) 
            {
                for (int j = 0; j < numVertices; j++) 
                {
                    cin >> graph[i][j];
                }
            }
            vector<int> dfsResult, bfsResult;
            vector<bool> visited(graph.size(), false);
            dfs(graph, 0, visited, dfsResult);
            bfs(graph, 0, bfsResult);
            cout << "Graph, depth traversal: ";
            for (int vertex : dfsResult)
            {
                cout << vertex << " ";
            }
            cout << endl;
            cout << "Graph, width traversal: ";
            for (int vertex : bfsResult) 
            {
                cout << vertex << " ";
            }
            cout << endl;
            break;
        }
        case 6: 
        {
            int V;
            cout << "Enter the number of vertices: ";
            cin >> V;

            vector<vector<int>> graph(V, vector<int>());
            vector<int> indegree(V, 0);

            cout << "Enter the adjacency matrix of the graph:" << endl;
            for (int i = 0; i < V; i++) 
            {
                for (int j = 0; j < V; j++) 
                {
                    int value;
                    cin >> value;
                    if (value == 1)
                        graph[i].push_back(j);
                }
            }

            topologicalSort(graph, indegree);
            cout << endl;
            break;
        }
        case 7:
        {
            return 0;
        }
        default:
        {
            cout << "The task number is incorrect. Try again!" << endl;
            break;
        }
        }
        cout << endl;
    }
}
