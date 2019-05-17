//
// Created by Nasratullah Sultany on 2019-05-16.
//

#ifndef B_TREE_PROJECT_B_TREE_H
#define B_TREE_PROJECT_B_TREE_H
/* This class implements a B-tree, which is used to implement quicker
 * file accesses. This is useful when you wish to access data that is
 * not stored internally in high speed memory. The template class Record
 * is used to specify the type of record the user wishes to store in the
 * tree, and the integer order represents the order of the B-tree.*/

template<class Record, int order>
struct B_node {
    // data members

    /* number of records in the B_node
    if nonzero, node has count + 1 children */
    int count;

    /* holds the keys, in sorted order of the node */
    Record data[order-1];

    /* branch[0] points to subtree containing records with keys less than
    // that in data[0]. Then. for each value of position from 1 to count-1,
    // branch[position] points to the subtree with keys strictly between
    // those of data[position-1] and data[position]. branch[count] points
    // to the subtree with keys greater than that of data[count-1]. */
    B_node<Record, order> *branch[order];

    // search node to see if the target is present in the current node
    void search_node(B_node<Record, order> *current, const Record &target, int &position);
    // constructor
    B_node();
};

template<class Record, int order>
class B_tree {
public:

    void search_tree(Record &target);

    bool recursive_search_tree(B_node<Record, order> *current, Record &target);

private:
    B_node<Record, order> *root;
};

template<class Record, int order>
void B_tree<Record, order>::search_tree(Record &target) {
    bool present = recursive_search_tree(root,target);
}

template<class Record, int order>
bool B_tree<Record, order>::recursive_search_tree(B_node<Record, order> *current, Record &target) {
    bool present = false;
    int position;
    if (current != NULL) {
        search_node(current, target, position);
        if (!present)
            present = recursive_search_tree(current->branch[position], target);
        else
            target = current->data[position];
    }
    return present;
}
#endif //B_TREE_PROJECT_B_TREE_H


















