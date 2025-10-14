#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <ranges>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <optional>

#include "linked_list.h"
#include "data.h"

using namespace std;

Node* priority_list;
unordered_map<string, Data> tasks;


void add_record_to_list(const Data& task) {
    Node* new_node = new Node(task);

    if (priority_list == nullptr) { // empty list
        priority_list = new_node; // add first node
        return;
    }

    Node* temp = priority_list;

    if (task.priority > temp->task.priority) { // if new task has highest priority
        insert_node_beginning(priority_list, task); // insert at beginning
        return;
    }

    while (temp->next != nullptr && task.priority <= temp->next->task.priority) { // insert before next highest priority task
        temp = temp->next;
    }

    new_node->next = temp->next;
    new_node->prev = temp;

    if (temp->next != nullptr) {
        temp->next->prev = new_node;
    }

    temp->next = new_node;

}

void add_record(const string &name, const string &description, const bool complete, // add data struct to hash map
                const int &priority, const time_t &due_date) {
    Data new_task;

    auto it = tasks.find(name);
    if (it != tasks.end()) {
        cout << "Name taken! choose a different name" << endl;
        return;
    }


    new_task.name = name;
    new_task.description = description;
    new_task.complete = complete;
    new_task.priority = priority;
    new_task.due_date = due_date;

    tasks[new_task.name] = new_task;
    add_record_to_list(new_task);

}

void delete_record(const string& query) {
    if (const auto search = tasks.find(query); search != tasks.end()) { // remove data struct from hash map
        cout << "Found: " << search->first << endl;
        cout << "Are you sure you want to delete? (Y/N): ";
        char choice;
        cin >> choice;
        choice = static_cast<char>(tolower(static_cast<unsigned char>(choice))); // converts char to lowercase with safety typecasting
        if (choice == 'y') {
            tasks.erase(search);
            delete_node_by_query(priority_list, query);
            cout << "Deleted Task" << endl;
        }
    }
}

optional<Data> search_records(const string& query) {
    if (const auto search = tasks.find(query); search != tasks.end()) { // store found container in search
        return search->second; // access data field
    }
    return nullopt;
}

optional<Node> list_records() {
    cout << "Listing tasks..." << endl;
    if (!tasks.empty()) {
        for (const auto &name: tasks | views::keys) {
            cout << name << endl;
        }
    }
    return nullopt;
}

optional<time_t> convert_time(const string& time) { // convert cin to time_t
    tm converted_time = {};
    istringstream ss(time);
    ss >> get_time(&converted_time, "%m/%d/%Y");

    if (ss.fail()) {
        return nullopt;
    }

    if (converted_time.tm_mon < 0 || converted_time.tm_mon > 11 || // validate format
        converted_time.tm_mday < 1 || converted_time.tm_mday > 31 ||
        converted_time.tm_year < 0) {
        return nullopt;
    }

    const time_t date = mktime(&converted_time);

    if (const tm* verified = localtime(&date); verified->tm_mday != converted_time.tm_mday || // verify time wasn't changed by mktime
                                               verified->tm_mon != converted_time.tm_mon ||
                                               verified->tm_year != converted_time.tm_year) {
        return nullopt;
    }


    return date;
}

void mark_complete(const string& query) { // complete tasks
    if (const auto search = tasks.find(query); search != tasks.end()) {
         search->second.complete = true;
    } else {
        cout << query << " Not Found!";
    }
}

void display_help() {
    cout << "Welcome to K-Task, Type:           \n"
            "--> add to add a task              \n"
            "--> del to delete a task           \n"
            "--> ser to search for a task       \n"
            "--> com to mark a task as complete \n"
            "--> list to list all tasks         \n";
}

[[noreturn]] int main() {
    display_help();
    string choice;
    while (true) {
        cout << "K-Task: ";
        cin >> choice;
        if (choice == "add") {
            cout << "Enter Task Name: ";
            string name;
            cin >> name;

            cout << "Enter Description: ";
            string description;
            cin >> description;

            cout << "Enter Priority: ";
            int priority;
            cin >> priority;

            cout << "Enter Date Due: ";
            string date;
            cin >> date;

            if (convert_time(date) != nullopt) {
                    time_t due_date = convert_time(date).value();
                    add_record(name, description, false, priority, due_date);
                    print_list_order(priority_list);

            } else {
                cerr << "Invalid Format For Date, Use MM/DD/YYYY" << endl;
            }

        } else if (choice == "del") {
            cout << "Enter Task To Delete: ";
            string choice_delete;
            cin >> choice_delete;

            delete_record(choice_delete);
            print_list_order(priority_list);

        } else if (choice == "ser") {
            cout << "Enter Task Name: ";
            string choice_search;
            cin >> choice_search;

            if (search_records(choice_search)  == nullopt) {
                cout << "No task found by that name!" << endl;
            } else {
                Data::print_data(*search_records(choice_search));
            }

        } else if (choice == "com") {
            cout << "Enter Task To Complete: ";
            string choice_complete;
            cin >> choice_complete;

            mark_complete(choice_complete);
            Data::print_data(*search_records(choice_complete));
            print_list_order(priority_list);

        } else if (choice == "list") {
            print_list_order(priority_list);
        }

        else if (choice == "help") {
            display_help();
        } else {
            cout << "Invalid Command, Type 'help' For Help" << endl;
        }




    }
}



