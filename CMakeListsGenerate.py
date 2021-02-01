import os

content = "cmake_minimum_required(VERSION 3.0)\nproject(my_solutions_to_hackerrank)\nset(CMAKE_CXX_STANDARD 17)\n\n"

cppfiles = [x for x in os.listdir() if x.endswith(".cpp")]

exec_cmd = ["add_executable({}  {})\n".format(x[:-4], x) for x in cppfiles]

with open("CMakeLists.txt", "w") as f:
    f.write(content)
    for x in exec_cmd:
        f.write(x)


