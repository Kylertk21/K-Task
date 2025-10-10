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

    static void print_data(const Data& passed_data) {
        const Data& data_to_print = passed_data;
        cout << "Name: " << data_to_print.name << endl;
        cout << "Description: " << data_to_print.description << endl;
        if (data_to_print.complete == 1) {
            cout << "Complete: True" << endl;
        } else {
            cout << "Complete: False" << endl;
        }

        cout << "Priority: " << data_to_print.priority << endl;

        char buffer[80];
        const tm* timeinfo = localtime(&data_to_print.due_date);
        strftime(buffer, sizeof(buffer), "%m/%d/%Y", timeinfo);
        cout << "Due Date: " << buffer << endl;
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

optional<Data> search_records(const string& query) {
    if (const auto search = tasks.find(query); search != tasks.end()) { // store found container in search
        return search->second; // access data field
    }
    return nullopt;
}

optional<time_t> convert_time(const string& time) {
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

    if (const tm* verified = localtime(&date); verified->tm_mday != converted_time.tm_mday ||
                                               verified->tm_mon != converted_time.tm_mon ||
                                               verified->tm_year != converted_time.tm_year) {
        return nullopt;
    }


    return date;
}

void mark_complete(const string& query) {
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
            "--> com to mark a task as complete \n";
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

            if (convert_time(date) != nullopt) {
                time_t due_date = convert_time(date).value();
                add_record(name, description, false, priority, due_date);
            } else {
                cerr << "Invalid Format For Date, Use MM/DD/YYYY" << endl;
            }

        } else if (choice == "del") {
            cout << "Enter Task To Delete: ";
            string choice_delete;
            cin >> choice_delete;

            delete_record(choice_delete);
            Data::print_data(*search_records(choice_delete));

        } else if (choice == "ser") {
            cout << "Enter Task Name: ";
            string choice_search;
            cin >> choice_search;

            Data::print_data(*search_records(choice_search));

        } else if (choice == "com") {
            cout << "Enter Task To Complete: ";
            string choice_complete;
            cin >> choice_complete;

            mark_complete(choice_complete);
            Data::print_data(*search_records(choice_complete));

        }



        else if (choice == "help") {
            display_help();
        } else {
            cout << "Invalid Command, Type 'help' For Help" << endl;
        }




    }
}



