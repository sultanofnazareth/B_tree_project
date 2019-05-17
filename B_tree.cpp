//
// Created by Nasratullah Sultany on 2019-05-16.
//
#include <iostream>
#include "B_tree.h"

template<class Record, int order>
B_node<Record, order>::B_node() {
    count = 0;
}

template<class Record, int order>
void B_node<Record, order>::search_node(B_node<Record, order> *current, const Record &target, int &position) {
    position = 0;
    while (position < current->count && target > current->data[position])
        position++;
    if (position < current->count && target == current->data[position])
        std::cout << "Found" << std::endl;
    else
        std::cout << "Not found" << std::endl;
}
