/*************************************************************************
	> File Name: test.cc
	> Author: wuxiangwei
	> Mail: wuxiangwei@corp.netease.com
	> Created Time: 六  2/24 16:33:36 2018
 ************************************************************************/

#include<iostream>
#include<cassert>


void swap(int& left, int& right) {
    left += right;
    right = left - right;
    left -= right;
}

int partition(int data[], int start, int end) {
    assert(end > start && start >= 0);
    if (data == NULL) {
        return 0;
    }

    int index = start + random() % (end - start + 1);
    swap(data[index], data[end]);

    int same = start - 1;
    for (int i = start; i < end; ++i) {
        if (data[i] < data[end]) {
            ++same;
            if (i != same) {
                swap(data[i], data[same]);
            }
        }
    }

    ++same;
    swap(data[same], data[end]);
    return same;
}


void quick_sort(int data[], int start, int end) {
    assert(start < end);
    assert(start >= 0 &&  end >= 0);
    if (data == nullptr) {
        return;
    }

    int index = partition(data, start, end);
    if (index-1 > start) {
        quick_sort(data, start, index-1);
    }

    if (index+1 < end) {
        quick_sort(data, index+1, end);
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
    int data[] = {4, 5, 6, 8, 2, 1, 7};

    int data_len = sizeof(data) / sizeof(data[0]);
    print_data(data, data_len);
    quick_sort(data, 0, data_len-1);
    print_data(data, data_len);

    return 0;
}
