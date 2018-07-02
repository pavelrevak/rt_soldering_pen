#pragma once

namespace lib {

/** Circle buffer (FIFO) template class

Arguments:
    T: item type
    SIZE: maximum number of stored items
*/
template <class T, size_t SIZE>
class Fifo {

    static_assert(!(SIZE & (SIZE + 1)), "Template parameter must be a power of two minus 1 (3, 7, 15, 31, 63, ...).");

protected:

    T buffer[SIZE + 1];
    volatile size_t head;
    volatile size_t tail;

    size_t next_item(size_t index) {
        return (++index) & SIZE;
    }

public:

    Fifo() {
        reset();
    }

    /** Reset FIFO
    Erase all data in FIFO and reset pointers
    */
    void reset() {
        head = 0;
        tail = 0;
    }

    /** Check if buffer is empty

    Return:
        true if buffer is empty
    */
    bool is_empty() const {
        if (SIZE == 0) return true;
        return head == tail;
    }

    /** Check if buffer has any data

    Return:
        true if in buffer are any data
    */
    bool has_data() const {
        if (SIZE == 0) return false;
        return head != tail;
    }

    /** Check if buffer is full

    Return:
        true if buffer is full
    */
    bool is_full() {
        if (SIZE == 0) return true;
        return next_item(head) == tail;
    }

    /** Reading number of available items in buffer

    Return:
        number of free items in buffer
    */
    size_t get_free() const {
        if (SIZE == 0) return 0;
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
        if (SIZE == 0) return 0;
        if (head < tail) {
            return SIZE + 1 + head - tail;
        }
        return head - tail;
    }

    /** Push item into buffer

    Arguments:
        value: item to push

    Return:
        true if push is success (buffer was not full)
    */
    bool push(const T value) {
        if (is_full()) return false;
        buffer[head] = value;
        head = next_item(head);
        return true;
    }

    /** Push items into buffer

    Arguments:
        data: pointer to list of items
        size: number of items

    Return:
        true if push is success (buffer was not full)
    */
    bool push_data(const T *data, int size) {
        if (get_free() < size) return false;
        while (size--) {
            buffer[head] = *data++;
            head = next_item(head);
        }
        return true;
    }

    /** Pull item from buffer

    Arguments:
        value: item where will be returned value from buffer

    Return:
        true if pull is success (was any item in buffer)
    */
    bool pull(T &value) {
        if (is_empty()) return false;
        value = buffer[tail];
        tail = next_item(tail);
        return true;
    }

    /** Pull items from buffer

    Arguments:
        data: pointer to list of items
        size: number of items to read from FIFO

    Return:
        true if pull is success (was any item in buffer)
    */
    bool pull_data(T *data, int size) {
        if (get_used() < size) return false;
        while (size--) {
            *data++ = buffer[tail];
            tail = next_item(tail);
        }
        return true;
    }
};

}
