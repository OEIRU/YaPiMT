#pragma once

#include <string>

using namespace std;

// Класс variable_exception наследуется от стандартного класса exception
class variable_exception : public exception {
    public:
        // Конструктор принимает сообщение об ошибке (msg) и формирует полное сообщение с префиксом
        variable_exception(const string& msg);
    
        // Метод объявлен как const и гарантирует, что он не выбрасывает исключений (throw())
        const char* what() const throw ();
    
    private:
        string message;  // Поле для хранения полного сообщения об ошибке
    
        // Префикс, добавляемый к каждому сообщению об ошибке
        // Указывает, что ошибка связана с переменной
        const string PREFIX = "Variable error";
    };