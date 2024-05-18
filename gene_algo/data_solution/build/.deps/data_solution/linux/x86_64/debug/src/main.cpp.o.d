{
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
            "-Iinclude"
        }
    },
    depfiles_gcc = "main.o: src/main.cpp include/rename.h\
",
    files = {
        "src/main.cpp"
    }
}