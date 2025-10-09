#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <random>
#include <ranges>
#include <cctype>

using namespace std;

class Data {
public:
    string name;
    string description;
    bool complete;
    int priority;
    string due_date; // TODO: convert to chrono::time
    Data() {
        name = "";
        description = "";
        complete = false;
        priority = 0;
        due_date = "";
    }

    static void print_data(const Data* passed_data) {
        const Data* data_to_print = passed_data;
        cout << "Name: " << data_to_print->name << endl;
        cout << "Description: " << data_to_print->description << endl;
        cout << "Complete: " << data_to_print->complete << endl;
        cout << "Priority: " << data_to_print->priority << endl;
        cout << "Due Date: " << data_to_print->due_date << endl;
    }
};

unordered_map<string, Data> tasks;

void add_record(const string &name, const string &description, const bool complete, // add data struct to hash map
                const int priority, const string &due_date) {
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
        }
    }
}

Data* search_records(const string& query) {
    if (const auto search = tasks.find(query); search != tasks.end()) { // store found container in search
        return &search->second; // access data field
    }
    return nullptr;
}

chrono::system_clock::time_point convert_time(string time) {

    return chrono::system_clock::now();
}

int main() {
    add_record("test", "desc", true, 2, "12/02/2022");
    const Data *query_data = search_records("test");
    Data::print_data(query_data);

    delete_record("test");
    Data::print_data(query_data);


    return 0;
}



