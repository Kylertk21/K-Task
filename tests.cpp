//
// Created by kylerk on 10/14/2025.
//

#define CATCH_CONFIG_MAIN

#include <sstream>
#include <ctime>
#include <iomanip>
#include <cctype>

#include "catch_amalgamated.hpp"
#include "catch_amalgamated.cpp"
#include "linked_list.h"
#include "data.h"

using namespace std;

TEST_CASE("Insert nodes correctly", "[insert]") {
    Node* head = nullptr;

    Data task1;
    task1.name = "name";
    task1.description = "desc";
    task1.complete = false;
    task1.priority = 1;
    task1.due_date = time(nullptr);

    insert_node_beginning(head, task1);
    REQUIRE(head->task.name == "name");
    REQUIRE(head->task.description == "desc");
    REQUIRE(head->task.complete == false);
    REQUIRE(head->task.priority == 1);
    REQUIRE(head->task.due_date == time(nullptr));

}
