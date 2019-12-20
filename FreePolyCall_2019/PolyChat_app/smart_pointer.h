#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#endif // SMART_POINTER_H

// Класс умного указателя
template <typename T>
class smart_pointer {
    T *m_obj;
public:
    // Отдаем ему во владение некий объект
    smart_pointer(T *obj)
        : m_obj(obj)
    { }
    // По выходу из области видимости этот объект мы уничтожим
    ~smart_pointer() {
        delete m_obj;
    }
    // Перегруженные операторы<
    // Селектор. Позволяет обращаться к данным типа T посредством "стрелочки"
    T* operator->() { return m_obj; }
    // С помощью такого оператора мы можем разыменовать указатель и получить ссылку на
    // объект, который он хранит
    T& operator* () { return *m_obj; }
};
