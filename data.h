//
// Created by kylerk on 10/14/2025.
//
#pragma once
#include <iomanip>
#include <ctime>

using namespace std;

#ifndef DATA_H
#define DATA_H

class Data {
public:
    string name;
    string description;
    bool complete;
    int priority;
    time_t due_date;
    Data() {
        name = "";
        description = "";
        complete = false;
        priority = 0;
        due_date = time(nullptr);
    }

    static void print_data(const Data& passed_data) { // print records
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

    friend ostream& operator<<(ostream& os, const Data& data) {
        // convert due_date to readable time
        streambuf* old_buf = cout.rdbuf(os.rdbuf()); // redirect cout's buffer to given output stream
        print_data(data);
        cout.rdbuf(old_buf); // restore cout's original buffer

        return os;
    }
};








#endif //DATA_H