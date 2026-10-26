//
// Created by Алексей on 18.10.2026.
//

#include "bmp_tests.h"
#include <cassert>

void CopyTest() {
    Bmp pic;
    pic.ReadBmp("../test_script/data/flag.bmp");
    pic.WriteBmp("../test_script/data/flag_copy.bmp");
}

void RotateTest() {
    Bmp pic;
    pic.ReadBmp("../test_script/data/flag.bmp");
    pic.WriteBmp("../test_script/data/flag_rotate.bmp");
}

void Test2() {
    Bmp pic;
    pic.ReadBmp("../test_script/data/lenna.bmp");
    pic.WriteBmp("../test_script/data/lenna_copy.bmp");
}

void RunBmpTests() {
    // CopyTest();
    // RotateTest();
    // test2();
}
