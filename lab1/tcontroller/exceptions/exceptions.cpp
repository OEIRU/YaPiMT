#include "exceptions.h"

// Конструктор класса variable_exception
// Принимает сообщение об ошибке (msg) и формирует полное сообщение, добавляя префикс
variable_exception::variable_exception(const string& msg) {
    message = PREFIX + ": " + msg;  // Формируем сообщение, объединяя префикс и текст ошибки
}

// Переопределение метода what() для возврата сообщения об ошибке
// Метод возвращает указатель на C-style строку (const char*), содержащую сообщение об ошибке
const char* variable_exception::what() const throw () {
    return message.c_str();  // Преобразуем std::string в C-style строку и возвращаем её
}
