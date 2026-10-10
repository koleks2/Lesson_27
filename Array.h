#pragma once

template<typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;
public:
    explicit Array(int capacity);
    ~Array();
    Array(const Array& other);
    Array& operator=(const Array& other);
    Array(Array&& other);
    Array& operator=(Array&& other);

    T operator[](int index) const {
        return data[index];
    }
    T& operator[](int index) {
        return data[index];
    }

    int GetSize() const {
        return size;
    }

    void pushBack(T newElem);
    void pushFront(T value);
    void insertAt(int index, T value);
    void removeAt(int index);
    void clear() {
        size = 0;
    }

    void popBack() {
        if (size > 0) size--;
    }

    void popFront();
    void reserve(int newCapacity);

    bool empty() const {
        return size == 0;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Array<U>& arr) {
        os << "{";
        if (!arr.empty()) {
            os << " ";
            for (int i = 0; i < arr.size; ++i) {
                os << arr.data[i];
                if (i < arr.size - 1) {
                    os << ", ";
                }
            }
            os << " ";
        }
        os << "}";
        return os;
    }
};

template<typename T>
Array<T>::Array(int capacity) : capacity(capacity) {
    if (capacity == 0) data = nullptr;
    else data = new T[capacity];
    size = 0;
}

template<typename T>
Array<T>::~Array() {
    if (data != nullptr) delete[] data;
}

template<typename T>
Array<T>::Array(const Array& other) : size(other.size), capacity(other.capacity) {
    if (capacity == 0) data = nullptr;
    else {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this == &other) return *this;

    delete[] data;

    size = other.size;
    capacity = other.capacity;
    if (capacity == 0) data = nullptr;
    else {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
Array<T>::Array(Array&& other) {
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other) {
    if (this == &other) return *this;

    if (data != nullptr) delete[] data;

    data = other.data;
    size = other.size;
    capacity = other.capacity;
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;

    return *this;
}

template<typename T>
void Array<T>::pushBack(T newElem) {
    if (size == capacity) {
        int newCap = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCap);
    }

    data[size++] = newElem;
}

template<typename T>
void Array<T>::pushFront(T value) {
    if (size == capacity) {
        int newCap = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCap);
    }

    for (int i = size; i > 0; --i) {
        data[i] = data[i - 1];
    }

    data[0] = value;
    size++;
}

template<typename T>
void Array<T>::insertAt(int index, T value) {
    if (index < 0 || index > size) {
        std::cout << "Error: invalid index\n";
        return;
    }

    if (size == capacity) {
        int newCap = (capacity == 0) ? 1 : capacity * 2;
        reserve(newCap);
    }

    for (int i = size; i > index; --i) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    size++;
}

template<typename T>
void Array<T>::removeAt(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Error: invalid index\n";
        return;
    }

    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }

    size--;
}

template<typename T>
void Array<T>::reserve(int newCapacity) {
    if (newCapacity <= capacity) return;

    T* temp = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
        temp[i] = data[i];
    }

    delete[] data;
    data = temp;
    capacity = newCapacity;
}

template<typename T>
void Array<T>::popFront() {
    if (empty()) return;

    for (int i = 0; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }

    size--;
}