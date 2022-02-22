//
// Created by Peter Janků on 11.02.2022.
//

#ifndef KILOBOTARENA_IMAGEBUFFER_H
#define KILOBOTARENA_IMAGEBUFFER_H
#include <QMutex>
#include <QMutexLocker>

/**
 * Template class for storing set of continuous data.
 * The data are stored in array - the class is working like a circular buffer. The data in buffer can be be overwrite
 * when the buffer is full or the push function can be blocking.
 * @tparam T Data type of stored values
 * @tparam size Size of circular buffer. (Default value size is 2)
 */
template<class T, int size = 2>
class ImageBuffer {
public:
    /**
     * Return the size of circular buffer
     * @return Size of buffer (elemnets of T type)
     */
    int getSize() { return size; }

    /**
     * Return number of free elements in buffer
     * @return Number of free elements
     */
    int getFree();


    int getLastIndex();


    int getCurrentIndex();

    T fetchLast();

    bool push();

    bool pushOverride(T value);


protected:
    T buffer[size];
    QMutex manipulationMutex;
    int last = -1;
    int curent = -1;
    int free = size;
};

/**
 * Return amount of free (non used) elements in buffer
 * @return Number of free elements
 */
template<class T, int size>
int ImageBuffer<T, size>::getFree() {
    return free;
}

template<class T, int size>
int ImageBuffer<T, size>::getLastIndex() {
    return last;
}

template<class T, int size>
int ImageBuffer<T, size>::getCurrentIndex() {
    return 0;
}

template<class T, int size>
T ImageBuffer<T, size>::fetchLast() {
    QMutexLocker lock(&manipulationMutex);
    return buffer[this->getLastIndex()];
}

template<class T, int size>
bool ImageBuffer<T, size>::push() {
    return false;
}

template<class T, int size>
bool ImageBuffer<T, size>::pushOverride(T value) {
    QMutexLocker lock(&manipulationMutex);
    if ((++last) == size)  last = 0;
    buffer[last]  = value;
    return false;
}


#endif //KILOBOTARENA_IMAGEBUFFER_H
