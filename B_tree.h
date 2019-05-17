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

    // constructor
    B_node() {count = 0;};
};

template<class Record, int order>
class B_tree {
public:

    void search_tree(Record &target);

    bool recursive_search_tree(B_node<Record, order> *current, Record &target);

    void insert(const Record &new_entry);

    // search node to see if the target is present in the current node
    bool search_node(B_node<Record, order> *current, const Record &target, int &position);

    bool push_down(B_node<Record, order> *current, const Record &new_entry,
                   Record &median, B_node<Record, order> *&right_branch);

    void push_in(B_node<Record, order> *current, const Record &entry, B_node<Record, order> *right_branch, int position);

    void split_node(B_node<Record, order> *current, const Record &extra_entry, B_node<Record, order> *extra_branch, int position, B_node<Record, order> *&right_half, Record &median);

    B_tree() { root = NULL;};

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
        present = search_node(current, target, position);
        if (!present)
            present = recursive_search_tree(current->branch[position], target);
        else
            target = current->data[position];
    }
    return present;
}

template<class Record, int order>
void B_tree<Record, order>::insert(const Record &new_entry) {
    Record median;
    B_node<Record, order> *right_branch, *new_root;
    bool result = push_down(root, new_entry, median, right_branch);
    if (result) {
        new_root = new B_node<Record, order>;
        new_root->count = 1;
        new_root->data[0] = median;
        new_root->branch[0] = root;
        new_root->branch[1] = right_branch;
        root = new_root;
        //result = success;
    }
    //return success;
}

template<class Record, int order>
bool B_tree<Record, order>::push_down(B_node<Record, order> *current, const Record &new_entry, Record &median,
                                      B_node<Record, order> *&right_branch) {
    bool overflow;
    int position;
    if (current == NULL) {
        median = new_entry;
        right_branch = NULL;
        overflow = true;
    }
    else {
        if (search_node(current, new_entry, position)) {
            std::cout << "Duplicate entry" << std::endl;
            overflow = false;
        }
        else {
            Record extra_entry;
            B_node<Record, order> *extra_branch;
            overflow = push_down(current->branch[position], new_entry, extra_entry, extra_branch);
            if (overflow) {
                if(current->count < order -1) {
                    // result = success
                    push_in(current, extra_entry, extra_branch, position);
                }
                else split_node(current, extra_entry, extra_branch, position, right_branch, median);
            }
        }
    }
    return overflow;
}

template<class Record, int order>
void
B_tree<Record, order>::push_in(B_node<Record, order> *current, const Record &entry, B_node<Record, order> *right_branch,
                               int position) {
    for (int i = current->count; i > position; i--) {
        current->data[i] = current->data[i-1];
        current->branch[i+1] = current->branch[i];
    }
    current->data[position] = entry;
    current->branch[position + 1] = right_branch;
    current->count++;
}

template<class Record, int order>
void B_tree<Record, order>::split_node(B_node<Record, order> *current, const Record &extra_entry,
                                       B_node<Record, order> *extra_branch, int position,
                                       B_node<Record, order> *&right_half, Record &median) {
    right_half = new B_node<Record, order>;
    int mid = order/2;
    if (position <= mid) {
        for (int i = mid; i < order-1 ; i++) {
            right_half->data[i-mid] = current->data[i];
            right_half->branch[i + 1 - mid] = current->branch[i+1];
        }
        current->count = mid;
        right_half->count = order-1-mid;
        push_in(current, extra_entry, extra_branch, position);
    }
    else {
        mid++;
        for (int i = mid; i < order-1; i++) {
            right_half->data[i-mid] = current->data[i];
            right_half->branch[i+1-mid] = current->branch[i+1];
        }
        current->count = mid;
        right_half->count = order-1-mid;
        push_in(right_half, extra_entry, extra_branch, position-mid);
    }
    median = current->data[current->count -1];
    right_half->branch[0] = current->branch[current->count];
    current->count--;
}

template<class Record, int order>
bool B_tree<Record, order>::search_node(B_node<Record, order> *current, const Record &target, int &position) {
    position = 0;
    while (position < current->count && target > current->data[position])
        position++;
    if (position < current->count && target == current->data[position])
        return true;
    else
        return false;
}

#endif //B_TREE_PROJECT_B_TREE_H


















