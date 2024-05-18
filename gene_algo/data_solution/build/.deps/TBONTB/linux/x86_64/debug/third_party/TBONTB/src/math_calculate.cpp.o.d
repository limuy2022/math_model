{
    files = {
        "third_party/TBONTB/src/math_calculate.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-Wall",
            "-Wextra",
            "-Weffc++",
            "-O0",
            "-std=c++20",
            "-I/home/omo/文档/code_space/cpp_code/math_model/data_solution/third_party/TBONTB/include",
            "-isystem",
            "/home/omo/文档/code_space/cpp_code/math_model/data_solution/build/.packages/g/googletest/latest/4e0143c97b65425b855ad5fd03038b6a/include",
            "-fprofile-arcs",
            "-ftest-coverage"
        }
    },
    depfiles_gcc = "math_calculate.o: third_party/TBONTB/src/math_calculate.cpp  /home/omo/文档/code_space/cpp_code/math_model/data_solution/third_party/TBONTB/include/TBONTB/math_calculate.h  /home/omo/文档/code_space/cpp_code/math_model/data_solution/third_party/TBONTB/include/TBONTB/rename_type.h\
"
}