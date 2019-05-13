//
// Created by Alexander Urbanyak on 2/21/2018.
//

#include "set.h"
#include <cassert>

set::set() {
    head_ptr = NULL;
    used = 0;
}

set::~set() {
    list_clear(head_ptr);
    used = 0;
}

set::set(const set &source) {
    node *tail_ptr;
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    used = source.used;
}

set& set::operator = (const set &source) {
    node *tail_ptr;

    if (this == &source)
        return *this;

    list_clear(head_ptr);
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    used = source.used;

    return *this;
}

void set::insert(const value_type &entry) {
    list_head_insert(head_ptr, entry);
    used++;
}

void set::remove(const value_type &entry) {
    assert(contains(entry));
    if (head_ptr ->data() == entry) {
        list_head_remove(head_ptr);
    }
    else {
        for (node *temp = head_ptr; temp != NULL; temp = temp ->link( )) {
            if (temp ->data() == entry) {
                list_remove(temp);
                break;
            }
        }
    }
    used--;
}

set::size_type set::size() const {
    return used;
}

bool set::contains(const value_type &entry) const {
    return list_search(head_ptr, entry) != NULL;
}

set set_union(const set &s1, const set &s2) {
    set s3;
    for (node *temp = s1.head_ptr; temp != NULL; temp = temp ->link( )) {
        s3.insert(temp ->data());
    }
    for (node *temp = s2.head_ptr; temp != NULL; temp = temp ->link( )) {
        s3.insert(temp ->data());
    }
    return s3;
}

set set_intersection(const set &s1, const set &s2) {
    set s3;
    set largest;
    set smaller;
    if(s1.size() > s2.size()) {
        largest = s1;
        smaller = s2;
    }
    else {
        largest = s2;
        smaller = s1;
    }

    for (node *temp = smaller.head_ptr; temp != NULL; temp = temp ->link( )) {
        if(largest.contains(temp ->data())) {
            s3.insert(temp ->data());
        }
    }
    return s3;
}

set set_difference(const set &s1, const set &s2) {
    set s3;

    for (node *temp = s1.head_ptr; temp != NULL; temp = temp ->link( )) {
        if(!s2.contains(temp ->data())) {
            s3.insert(temp ->data());
        }
    }
    return s3;
}

bool is_subset(const set &s1, const set &s2) {
    for (node *temp = s1.head_ptr; temp != NULL; temp = temp ->link( )) {
        if(!s2.contains(temp ->data())) {
            return false;
        }
    }
    return true;
}

bool operator == (const set &s1, const set &s2) {
    return is_subset(s1, s2) && is_subset(s2, s1);
}

std::ostream& operator << (std::ostream& output, const set& s) {
    for (node *temp = s.head_ptr; temp != NULL; temp = temp ->link( )) {
        output << temp ->data() << " ";
    }
    return output;
}