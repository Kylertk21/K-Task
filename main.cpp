#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <random>
#include <ranges>

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
};

unordered_map<string, Data> tasks;

void add_record(const string &name, const string &description, const bool complete,
                const int priority, const string &due_date) {
    Data new_task;
    new_task.name = name;
    new_task.description = description;
    new_task.complete = complete;
    new_task.priority = priority;
    new_task.due_date = due_date;

    tasks[new_task.name] = new_task;

}

void delete_record(string query) {

}

Data* search_records(string query) {
    if (auto search = tasks.find(query); search != tasks.end()) {
        return &search->second;
    }
    return nullptr;
}

chrono::system_clock::time_point convert_time(string time) {

    return chrono::system_clock::now();
}

int main() {
    add_record("test", "desc", true, 2, "12/02/2022");
    const Data *query_data = search_records("test");
    cout << "Name: " << query_data->name << endl;
    cout << "Description: " << query_data->description << endl;
    cout << "Complete: " << query_data->complete << endl;
    cout << "Priority: " << query_data->priority << endl;
    cout << "Due Date: " << query_data->due_date << endl;

    return 0;
}



