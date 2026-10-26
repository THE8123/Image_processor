#ifndef IMAGE_PROCESSOR_PARSER_H
#define IMAGE_PROCESSOR_PARSER_H

#include <vector>

#include "filter.h"

// FilterDescriptor может быть реализован прям тут, а может отдельно, если мы хотим его шарить куда-либо еще

// параметры можно передать либо в конструкторе, либо в отдельной функции, либо и там и там
// если есть конструктор по умолчанию, то можно сделать отложенную инициализацию и по простому добавить
// парсер в Application, иначе надо в конструктор Application
class Parser {
public:
    // перечисляем список возможных ответов парсеров
    enum class Result {
        Ok,  // Все хорошо распарсилось, можно пытаться конвертировать
        NoArguments,  // Аргументов не дали, надо вывести справку
        // и так далее, например NoOutputFile, NoFilterExpected(UnknownArgument)
        FewArguments,      // Недостаточно аргументов
        InvalidArguments,  // Неправильные аргументыe
    };

public:
    Parser();

public:
    Result Parse(int argc, char* argv[]);

    std::vector<FilterDescriptor> GetFilters() const {
        return filters_;
    }

    const char* GetInputName() const {
        return input_file_name_;
    }

    const char* GetOutputName() const {
        return output_file_name_;
    }

private:
    // детали возможной реализации
    const char* input_file_name_;
    const char* output_file_name_;
    std::vector<FilterDescriptor> filters_;
};

#endif
