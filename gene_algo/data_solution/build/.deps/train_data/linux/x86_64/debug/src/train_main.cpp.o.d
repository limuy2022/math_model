{
    files = {
        "src/train_main.cpp"
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
            "-Iinclude",
            "-isystem",
            "/home/omo/.xmake/packages/e/eigen/3.4.0/c95d81810dbc45229e675130ada7d4c7/include",
            "-isystem",
            "/home/omo/.xmake/packages/e/eigen/3.4.0/c95d81810dbc45229e675130ada7d4c7/include/eigen3"
        }
    },
    depfiles_gcc = "train_main.o: src/train_main.cpp include/rename.h\
"
}