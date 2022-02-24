//
// Created by xu on 2022/2/22.
//

#include "container.h"

template <typename T>
container<T>::container(const T &arg):element(arg) {

}

template <typename T> T container<T>::increase() {
    return ++element;
}