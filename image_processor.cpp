#include <exception>
#include <iostream>

#include "application.h"
#include "ultimate_tester.h"

const int NOT_HANDLED_STANDARD_EXCEPTION = -1;
const int NOT_HANDLED_CUSTOM_EXCEPTION = -2;

int Main2(int argc, char* argv[]) {
    Application app;
    app.Init();
    Application::Result result = app.Run(argc, argv);
    if (result != Application::Result::Success) {
        Print("Something went wrong and filters were not applied!");
        return 0;
    }
    Print("Filters applied!");
    return 0;
}

int main(int argc, char* argv[]) {
    // ХОХМОЧКА
    // runAllTests();

    try {
        Main2(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return NOT_HANDLED_STANDARD_EXCEPTION;
    } catch (...) {
        std::cerr << "unknown exception code.\n";
        return NOT_HANDLED_CUSTOM_EXCEPTION;
    }

    return 0;
}