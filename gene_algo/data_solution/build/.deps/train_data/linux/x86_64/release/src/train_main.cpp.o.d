{
    files = {
        "src/train_main.cpp"
    },
    depfiles_gcc = "train_main.o: src/train_main.cpp include/rename.h\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-Wall",
            "-Wextra",
            "-Weffc++",
            "-O3",
            "-std=c++20",
            "-Iinclude",
            "-isystem",
            "/home/limuy/.xmake/packages/e/eigen/3.4.0/c95d81810dbc45229e675130ada7d4c7/include",
            "-isystem",
            "/home/limuy/.xmake/packages/e/eigen/3.4.0/c95d81810dbc45229e675130ada7d4c7/include/eigen3",
            "-DNDEBUG"
        }
    }
}