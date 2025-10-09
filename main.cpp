#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <ranges>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

class Data {
public:
    string name;
    string description;
    bool complete;
    string priority;
    time_t due_date;
    Data() {
        name = "";
        description = "";
        complete = false;
        priority = "0";
        due_date = time(nullptr);
    }

    static void print_data(const Data* passed_data) {
        const Data* data_to_print = passed_data;
        cout << "Name: " << data_to_print->name << endl;
        cout << "Description: " << data_to_print->description << endl;
        if (data_to_print->complete == 1) {
            cout << "Complete: True" << endl;
        } else {
            cout << "Complete: False" << endl;
        }

        cout << "Priority: " << data_to_print->priority << endl;
        cout << "Due Date: " << data_to_print->due_date << endl;
    }
};

unordered_map<string, Data> tasks;

void add_record(const string &name, const string &description, const bool complete, // add data struct to hash map
                const string &priority, const time_t &due_date) {
    Data new_task;
    new_task.name = name;
    new_task.description = description;
    new_task.complete = complete;
    new_task.priority = priority;
    new_task.due_date = due_date;

    tasks[new_task.name] = new_task;

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
            cout << "Deleted Task" << endl;
        }
    }
}

Data* search_records(const string& query) {
    if (const auto search = tasks.find(query); search != tasks.end()) { // store found container in search
        return &search->second; // access data field
    }
    return nullptr;
}

time_t convert_time(const string& time) {
    tm converted_time = {};
    istringstream ss(time);
    ss >> get_time(&converted_time, "%m/%d/%Y");

    if (ss.fail()) {
        cerr << "Invalid Format For Date, Use MM/DD/YYYY" << endl;
        return 1;
    }

    const time_t date = mktime(&converted_time);

    return date;
}

void display_help() {
    cout << "Welcome to K-Task, Type:     \n"
            "--> add to add a task        \n"
            "--> del to delete a task     \n"
            "--> ser to search for a task \n";
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
            string priority;
            cin >> priority;

            cout << "Enter Date Due: ";
            string date;
            cin >> date;
            time_t due_date = convert_time(date);

            add_record(name, description, false, priority, due_date);

            const Data* test_query = search_records(name);
            Data::print_data(test_query);


        } else if (choice == "del") {
            cout << "Enter Task To Delete: ";
            string choice_delete;
            cin >> choice_delete;

            delete_record(choice_delete);

        } else if (choice == "ser") {
            cout << "Enter Task Name: ";
            string choice_search;
            cin >> choice_search;

            Data::print_data(search_records(choice_search));


        } else if (choice == "help") {
            display_help();
        } else {
            cout << "Invalid Command, Type 'help' For Help" << endl;
        }




    }
}



