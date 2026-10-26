#ifndef IMAGE_PROCESSOR_APPLICATION_H
#define IMAGE_PROCESSOR_APPLICATION_H

#include "filter_factory.h"
#include "parser.h"

#include <iostream>

extern const char* const IMAGE_PROCESSOR_HELP;

extern const char* const SEE_HELP;

inline void Print(const char* string) {
    std::cout << string << std::endl;
}

class Application {
public:
    void Init();

    enum class Result {
        Success,         // успешное завершение программы
        PipelineFailed,  // что то сломалось в пайплайне
        ReadFailed,      // ошибка во время чтения файла
        WriteFailed,     // ошибка во время открытия файла
        Failed,          // иная причина ошибки
    };

    Result Run(int argc, char* argv[]);

    void Help() const {
        Print(IMAGE_PROCESSOR_HELP);
    }

    void FewArgs() const {
        Print("Not enough arguments");
        Print(SEE_HELP);
    }

    void InvalidArgs() const {
        Print("Invalid arguments");
        Print(SEE_HELP);
    }

private:
    Parser parser_;
    FilterFactory factory_;
};

#endif