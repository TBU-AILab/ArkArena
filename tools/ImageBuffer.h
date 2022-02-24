//
// Created by Peter Janků on 11.02.2022.
//

#ifndef KILOBOTARENA_IMAGEBUFFER_H
#define KILOBOTARENA_IMAGEBUFFER_H
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QObject>
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
    T fetchLast(bool &result);

    T fetchCurrent();
    T fetchCurrent(bool &result);


    bool push(T value);


    bool pushOverride(T value);

protected:
    int incrementLastPointer();
    int incrementCurrentPointer();

    T buffer[size];             /**< memory array for the buffer storage */
    QMutex manipulationMutex;   /**< internal mutext */
    int last = -1;              /**< index of last added item */
    int current = -1;           /**< index of oldest item in buffer which was not fetched */
    int free = size;
};

/**
 * This function will correctly increment the buffer pointers.
 * @return
 */
template<class T, int size>
int ImageBuffer<T, size>::incrementLastPointer() {
    if (last == -1){
        last = 0;
        current = 0;
    }else{
        if ((++last) == size)  last = 0;
        if (last == current) {
            if ((++current) == size) current = 0 ;
        }
    }
    return  last;
}


//TODO: reipmlement the "free" space counter - current implementation is not working
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
    return current;
}

//TODO: Solve the error part of the program.
/**
 * Get the lastest added element from the buffer
 * @param result the last added element
 * @return true if success, false if no elements are in the buffer
 */
template<class T, int size>
T ImageBuffer<T, size>::fetchLast(bool &result) {
    QMutexLocker lock(&manipulationMutex);
    if (this->getLastIndex() != -1){
        result = true;
        return buffer[this->getLastIndex()];
    }
    else{
        result = false;
        //return nullptr;
    }
}
/**
 * Get the lastest added element from the buffer
 * @return true if success, false if no elements are in the buffer
 */
template<class T, int size>
T ImageBuffer<T, size>::fetchLast() {
    bool tmp;
    return fetchLast(tmp);
}

/**
 * Push new element at the top of the buffer and return true only if there is a space. If the buffer is full, element isn't pushed and return value is false.
 * @param value new value to be pushed
 * @return true if pushed, false if not
 */
template<class T, int size>
bool ImageBuffer<T, size>::push(T value) {
    QMutexLocker lock (&manipulationMutex);
    if (getFree() > 0) {
        incrementLastPointer();
        buffer[last]  = value;
        qDebug() << "New element in empty space...";
        return true;
    }
    return false;
}


/**
 * Push the new value at the top of the buffer even if old unprocessed image is already there.
 * @param value new value to be pushed
 * @return alvays true (planned for further use)
 */
template<class T, int size>
bool ImageBuffer<T, size>::pushOverride(T value) {
    QMutexLocker lock(&manipulationMutex);
    incrementLastPointer();
    buffer[last]  = value;
    qDebug() << "New element ...";
    return true;
}
/**
* Increment the current index. If there isn't unfetched element, both counters are reset to -1
 * @return Original value before increment.
 */
template<class T, int size>
int ImageBuffer<T, size>::incrementCurrentPointer() {
    int tmp = current;
    if (current > -1){
        if ((++current) == size) current = 0;
        if (tmp == last){
            current = -1;
            current = -1;
        }
    }
    return tmp;
}

template<class T, int size>
T ImageBuffer<T, size>::fetchCurrent() {
    bool tmp;
    return fetchCurrent(tmp);
}

//TODO: Solve the error part of the program.
template<class T, int size>
T ImageBuffer<T, size>::fetchCurrent(bool &result) {
    QMutexLocker lock(&manipulationMutex);
    int tmp = incrementCurrentPointer();
    if (tmp != -1){
        result = true;
        return buffer[tmp];
    }
    else{
        result = false;
        //return nullptr;
    }
}


#endif //KILOBOTARENA_IMAGEBUFFER_H
