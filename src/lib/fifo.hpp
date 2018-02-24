#pragma once

/**
 * @class Circle buffer (FIFO) template class
 *
 * @param T item type
 * @param SIZE maximum number of stored items
 */
template <class T, int SIZE>
class Fifo {
protected:
    T buffer[SIZE + 1];
    T *end;
    T *head;
    T *tail;

    inline T *next_item(T *ptr) {
        return (++ptr < end) ? ptr : buffer;
    }

public:
    Fifo() {
        end = &buffer[SIZE + 1];
        reset();
    }

    /**
     * @brief Reset FIFO
     * @details Erase all data in FIFO and reset pointers
     */
    inline void reset() {
        head = buffer;
        tail = buffer;
    }

    /**
     * @brief Check if buffer is empty
     * @return true if buffer is empty
     */
    inline bool is_empty() const {
        return head == tail;
    }

    /**
     * @brief Check if buffer has any data
     * @return true if in buffer are any data
     */
    inline bool has_data() const {
        return head != tail;
    }

    /**
     * @brief Check if buffer is full
     * @return true if buffer is full
     */
    inline bool is_full() {
        return next_item(head) == tail;
    }

    /**
     * @brief Reading number of available items in buffer
     * @return number of free items in buffer
     */
    inline int get_free() const {
        if (head < tail) {
            return tail - head - 1;
        }
        return SIZE + tail - head;
    }

    /**
     * @brief Reading number of used items in buffer
     * @return number of used items in buffer
     */
    inline int get_used() const {
        if (head < tail) {
            return SIZE + 1 + head - tail;
        }
        return head - tail;
    }

    /**
     * @brief Push item into buffer
     *
     * @param value item to push
     * @return true if push is success (buffer was not full)
     */
    inline bool push(T value) {
        if (is_full()) return false;
        *head = value;
        head = next_item(head);
        return true;
    }

    /**
     * @brief Pull item from buffer
     *
     * @param value item where will be returned value from buffer
     * @return true if pull is success (was any item in buffer)
     */
    inline bool pull(T &value) {
        if (is_empty()) return false;
        value = *tail;
        tail = next_item(tail);
        return true;
    }
};
