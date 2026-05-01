# Laboratory work III

Данная лабораторная работа посвещена изучению систем автоматизации сборки проекта на примере CMake.

Структура проекта
В ходе работы была создана модульная структура:

 `formatter_lib` — библиотека для форматирования строк.
 
 `formatter_ex_lib` — расширенная библиотека форматирования.
 
 `solver_lib` — библиотека для решения квадратных уравнений.
 
 `hello_world_application` — приложение для вывода приветствия.
 
 `solver_application` — приложение для решения уравнений.

<details>
<summary>Вывод</summary>

```bash
cat > formatter_lib/formatter.h <<EOF
#include <string>
std::string formatter(const std::string& message);
EOF

cat > formatter_lib/formatter.cpp <<EOF
#include "formatter.h"
std::string formatter(const std::string& message) {
    std::string res;
    res += "-------------------------------------\n";
    res += message + "\n";
    res += "-------------------------------------\n";
    return res;
}
EOF

cat > solver_lib/solver.h <<EOF
void solve(float a, float b, float c, float& x1, float& x2);
EOF

cat > solver_lib/solver.cpp <<EOF
#include "solver.h"
#include <stdexcept>
#include <cmath>

void solve(float a, float b, float c, float& x1, float& x2) {
    float d = (b * b) - (4 * a * c);
    if (d < 0) {
        throw std::logic_error("error: discriminant < 0");
    }
    x1 = (-b - std::sqrt(d)) / (2 * a);
    x2 = (-b + std::sqrt(d)) / (2 * a);
}
EOF

 cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.10)
project(formatter_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотеки
add_library(formatter STATIC formatter_lib/formatter.cpp)
add_library(solver STATIC solver_lib/solver.cpp)

# Подключаем заголовки
include_directories(formatter_lib solver_lib)

# Приложения
add_executable(hello_world hello_world_application/main.cpp) # Тут создадим пустой main пока
target_link_libraries(hello_world formatter)

add_executable(solver_app solver_application/main.cpp)
target_link_libraries(solver_app formatter solver)
EOF

cat > hello_world_application/main.cpp <<EOF
#include <iostream>
#include "formatter.h"

int main() {
    std::cout << formatter("hello, world") << std::endl;
    return 0;
}
EOF

cat > solver_application/main.cpp <<EOF
#include <iostream>
#include "formatter.h"
#include "solver.h"

int main() {
    float a = 1, b = -3, c = 2;
    float x1, x2;
    try {
        solve(a, b, c, x1, x2);
        std::string result = "x1 = " + std::to_string(x1) + ", x2 = " + std::to_string(x2);
        std::cout << formatter(result) << std::endl;
    } catch (const std::exception& e) {
        std::cout << formatter(e.what()) << std::endl;
    }
    return 0;
}
EOF

cat > formatter_ex_lib/formatter_ex.h <<EOF
#include <string>
#include <iostream>
void formatter_ex(const std::string& message, std::ostream& out);
EOF

cat > formatter_ex_lib/formatter_ex.cpp <<EOF
#include "formatter_ex.h"
#include "formatter.h"

void formatter_ex(const std::string& message, std::ostream& out) {
    out << formatter(message);
}
EOF

cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.10)
project(formatter_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотеки
add_library(formatter STATIC formatter_lib/formatter.cpp)
add_library(formatter_ex STATIC formatter_ex_lib/formatter_ex.cpp)
add_library(solver STATIC solver_lib/solver.cpp)

# Указываем пути к заголовкам для всех
include_directories(formatter_lib formatter_ex_lib solver_lib)

# Сборка Hello World
add_executable(hello_world hello_world_application/main.cpp)
target_link_libraries(hello_world formatter)

# Сборка Solver App
add_executable(solver_app solver_application/main.cpp)
target_link_libraries(solver_app formatter solver)
EOF
```
</details>

Подготовка проекта к сборке `cmake -B _build`

<details>
<summary>Вывод</summary>

```bash
-- The C compiler identification is AppleClang 17.0.0.17000013
-- The CXX compiler identification is AppleClang 17.0.0.17000013
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.5s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/aleksandrgolikov/workspace/projects/laba3/_build
```
</details>

Сборка проекта `cmake --build _build`

<details>
<summary>Вывод</summary>

```bash
[ 10%] Building CXX object CMakeFiles/formatter.dir/formatter_lib/formatter.cpp.o
[ 20%] Linking CXX static library libformatter.a
[ 20%] Built target formatter
[ 30%] Building CXX object CMakeFiles/formatter_ex.dir/formatter_ex_lib/formatter_ex.cpp.o
[ 40%] Linking CXX static library libformatter_ex.a
[ 40%] Built target formatter_ex
[ 50%] Building CXX object CMakeFiles/solver.dir/solver_lib/solver.cpp.o
[ 60%] Linking CXX static library libsolver.a
[ 60%] Built target solver
[ 70%] Building CXX object CMakeFiles/hello_world.dir/hello_world_application/main.cpp.o
[ 80%] Linking CXX executable hello_world
[ 80%] Built target hello_world
[ 90%] Building CXX object CMakeFiles/solver_app.dir/solver_application/main.cpp.o
[100%] Linking CXX executable solver_app
[100%] Built target solver_app
```
</details>

Запуск и проверка результатов `./_build/hello_world` `./_build/solver_app`

<details>
<summary>Вывод</summary>

```bash
% ./_build/hello_world
-------------------------------------
hello, world
-------------------------------------

 % ./_build/solver_app
-------------------------------------
x1 = 1.000000, x2 = 2.000000
-------------------------------------
```
</details>

Для фиксации итоговых результатов работы в системе контроля версий были выполнены команды индексации, компиляции изменений и их отправки в удаленный репозиторий GitHub:
`git add .`
`git commit -m "fixed"`
`git push origin main`

<details>
<summary>Вывод</summary>

```bash
[main fcae902] fixed
 12 files changed, 69 insertions(+), 21 deletions(-)
 delete mode 100644 examples/example1.cpp
 create mode 100644 formatter_ex_lib/formatter_ex.cpp
 create mode 100644 formatter_ex_lib/formatter_ex.h
 create mode 100644 formatter_lib/formatter.cpp
 create mode 100644 formatter_lib/formatter.h
 create mode 100644 hello_world_application/main.cpp
 delete mode 100644 include/print.hpp
 create mode 100644 solver_application/main.cpp
 create mode 100644 solver_lib/solver.cpp
 create mode 100644 solver_lib/solver.h
 delete mode 100644 sources/print.cpp

Перечисление объектов: 18, готово.
Подсчет объектов: 100% (18/18), готово.
При сжатии изменений используется до 12 потоков
Сжатие объектов: 100% (14/14), готово.
Запись объектов: 100% (16/16), 2.10 KiB | 2.10 MiB/s, готово.
Total 16 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To github.com:2dmpjv8fgy-commits/laba3.git
   6d43e38..fcae902  main -> main
```
</details>
