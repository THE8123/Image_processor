#include "parser.h"

Parser::Result Parser::Parse(int argc, char* argv[]) {
    if (argc == 1) {
        return Result::NoArguments;
    }
    if (argc < 3) {
        return Result::FewArguments;
    }
    input_file_name_ = argv[1];
    output_file_name_ = argv[2];
    if (argc == 3) {
        return Result::Ok;
    }
    if (argv[3][0] != '-') {
        return Result::InvalidArguments;
    }
    for (size_t i = 3; i < argc; i++) {
        if (argv[i][0] == '-') {
            filters_.emplace_back();
            filters_.back().name = argv[i] + 1;
        } else {
            filters_.back().args.emplace_back(argv[i]);
        }
    }
    return Result::Ok;
}

Parser::Parser() : input_file_name_(""), output_file_name_(""), filters_() {
}
