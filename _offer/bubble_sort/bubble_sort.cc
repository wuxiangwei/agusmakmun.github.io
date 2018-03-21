/*************************************************************************
	> File Name: bubble_sort.cc
	> Author: wuxiangwei
	> Mail: wuxiangwei@corp.netease.com
	> Created Time: 日  2/25 09:03:21 2018
 ************************************************************************/

#include <iostream>
#include <cassert>

void swap(int& left, int& right) {
    left += right;
    right = left - right;
    left -= right;
}

void bubble_sort(int data[], int len) {
    if (data == nullptr) {
        return;
    }

    assert(len > 0);

    int count = len - 1;
    while (count > 1) {
        for (int j = 0; j < count; ++j) {
            if(data[j] > data[j+1]) {
                swap(data[j], data[j+1]);
            }
        }

        --count;
    }
}


void print_data(int data[], int len) {
    if (data == nullptr) {
        return;
    }

    for (int index = 0; index < len; ++index) {
        std::cout << data[index] << " ";
    }
    std::cout << std::endl;
}


int main(int argc, char *argv[]) {

    int data[] = {7, 4, 8, 2, 3, 6};
    int data_len = sizeof(data) / sizeof(data[0]);

    print_data(data, data_len);
    bubble_sort(data, data_len);
    print_data(data, data_len);

    return 0;
}
