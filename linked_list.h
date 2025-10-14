//
// Created by kylerk on 10/14/2025.
//
#include <iostream>

#include "data.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

using namespace std;

struct Node {
    Data task{};
    Node* next{};
    Node* prev{};

    explicit Node(Data task) {
        this->task = task;
        this->next = nullptr;
        this->prev = nullptr;

    }
};

inline void insert_node_beginning(Node*& head, Data task) {

    Node* new_node = new Node(task);

    if (head == nullptr) { // check if empty
        head = new_node;
        return;
    }
    new_node->next = head; // update next and prev pointers to insert the new node at the beginning
    head->prev = new_node;
    head = new_node;
}

inline void insert_node_end(Node*& head, Data task) {
    Node* new_node = new Node(task);

    if (head == new_node) {
        head = new_node;
        return;
    }

    Node* temp = head; // traverse to last node of list
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}

inline void insert_node_at_x(Node*& head, Data task, int x) {
    if (x < 1) { // if position is less than 1, node cannot be inserted
        cout << "Position must be >= 1" << endl;
        return;
    }
    if (x == 1) { // if position is 1, insert at beginning
        insert_node_beginning(head, task);
        return;
    }
    Node* new_node = new Node(task);
    Node* temp = head;

    for (int i = 1; temp != nullptr && i < x - 1; i++) { // traverse to node before specified position
        temp=temp->next;
    }

    if (temp == nullptr) {
        cout << "Position greater than number of nodes" << endl;
        return;
    }
    new_node->next = temp->next; // point new node's next to node's next (node B)
    new_node->prev = temp; // point new node's prev to temp (node A)
    if (temp->next != nullptr) { // if next node isn't empty
        temp->next->prev = new_node; // update next node to point to new node (b/t A and B)
    }
    temp->next = new_node; // actually attach new node to list
}

inline void delete_at_beginning(Node*& head) {
    if (head == nullptr) {
        cout << "List already empty..." << endl;
        return;
    }
    Node* temp = head;
    head = head->next; // move head to point to the next node in the list
    if (head != nullptr) { // if there is a new head node
        head->prev = nullptr; // clear prev pointer
    }
    delete temp;
}

inline void delete_at_end(Node*& head) {
    if (head == nullptr) {
        cout << "List already empty..." << endl;
        return;
    }

    Node* temp = head;

    if (temp->next == nullptr) { // if only one node in the list
        head = nullptr; // clear head
        delete temp;
        return;
    }
    while (temp->next != nullptr) { // traverse to end of list
        temp = temp->next;
    }

    temp->prev->next = nullptr; // move to second-to-last node and set next pointer to nullptr,
    delete temp; // making it the last node in the list
}

inline void delete_at_x(Node*& head, int x) {
    if (head == nullptr) {
        cout << "List already empty..." << endl;
        return;
    }

    Node* temp = head;

    if (x == 1) {
        delete_at_beginning(head);
        return;
    }

    for (int i = 1; temp != nullptr && i < x; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Position greater than number of nodes" << endl;
        return;
    }

    if (temp->next == nullptr) {
        delete_at_end(head);
        return;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev; // point next node to node before x
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next; // point previous node's next to x's next pointer
    }
    delete temp;
}

inline void delete_node_by_query(Node*& head, string query) {
    if (head == nullptr) {
        cout << "List already empty..." << endl;
        return;
    }

    Node* temp = head;

    for (int i = 1; temp != nullptr && temp->task.name != query; i++) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Task not found in list!" << endl;
    }

    if (temp->next == nullptr) {
        delete_at_end(head);
        return;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    delete temp;
}

inline void print_list_forward(Node* head) {
    Node* temp = head;
    cout << "Forward List: " << endl;
    while (temp != nullptr) {
        cout << temp->task << endl;
        temp = temp->next;
    }
    cout << "##################" << endl;
}

inline void print_list_order(Node* head) {
    Node* temp = head;
    if (temp == nullptr) {
        cout << "List Empty!" << endl;
        return;
    }

    while (temp->next != nullptr) {
        temp = temp->next;
    }

    cout << "Tasks Ordered By Priority: \n";
    while (temp != nullptr) {
        cout << temp->task << endl;
        temp = temp->prev;
    }
    cout << "##################" << endl;
}


#endif //LINKED_LIST_H