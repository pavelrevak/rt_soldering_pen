#pragma once

namespace lib {

/** Circle buffer (FIFO) template class

Arguments:
    T: item type
    SIZE: maximum number of stored items
*/
template <class T, int SIZE>
class Fifo {
protected:
    T buffer[SIZE + 1];
    T *end;
    T *head;
    T *tail;

    T *next_item(T *ptr) {
        return (++ptr < end) ? ptr : buffer;
    }

public:
    Fifo() {
        end = &buffer[SIZE + 1];
        reset();
    }

    /** Reset FIFO
    Erase all data in FIFO and reset pointers
    */
    void reset() {
        head = buffer;
        tail = buffer;
    }

    /** Check if buffer is empty

    Return:
        true if buffer is empty
    */
    bool is_empty() const {
        return head == tail;
    }

    /** Check if buffer has any data

    Return:
        true if in buffer are any data
    */
    bool has_data() const {
        return head != tail;
    }

    /** Check if buffer is full

    Return:
        true if buffer is full
    */
    bool is_full() {
        return next_item(head) == tail;
    }

    /** Reading number of available items in buffer

    Return:
        number of free items in buffer
    */
    int get_free() const {
        if (head < tail) {
            return tail - head - 1;
        }
        return SIZE + tail - head;
    }

    /** Reading number of used items in buffer

    Return:
        number of used items in buffer
    */
    int get_used() const {
        if (head < tail) {
            return SIZE + 1 + head - tail;
        }
        return head - tail;
    }

    /** Push item into buffer

    Arguments:
        value item to push

    Return:
        true if push is success (buffer was not full)
    */
    bool push(T value) {
        if (is_full()) return false;
        *head = value;
        head = next_item(head);
        return true;
    }

    /** Pull item from buffer

    Arguments:
        value item where will be returned value from buffer

    Return:
        true if pull is success (was any item in buffer)
    */
    bool pull(T &value) {
        if (is_empty()) return false;
        value = *tail;
        tail = next_item(tail);
        return true;
    }
};

}
