# Laboratory work III

Данная лабораторная работа посвещена изучению систем автоматизации сборки проекта на примере CMake.

Структура проекта
В ходе работы была создана модульная структура:

 `formatter_lib` — статическая библиотека для форматирования строк. Содержит локальный CMakeLists.txt для сборки цели formatter.
 
 `formatter_ex_lib` — расширенная библиотека, зависящая от formatter. Содержит локальный CMakeLists.txt.
 
 `solver_lib` — библиотека для решения уравнений. Содержит локальный CMakeLists.txt для сборки цели solver.
 
 `hello_world_application` — приложение, использующее библиотеку formatter.
 
 `solver_application` — приложение для решения уравнений, использующее библиотеки formatter и solver.

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

cat > formatter_lib/CMakeLists.txt <<EOF
add_library(formatter STATIC formatter.cpp)
EOF

cat > formatter_ex_lib/CMakeLists.txt <<EOF
add_library(formatter_ex STATIC formatter_ex.cpp)
target_link_libraries(formatter_ex formatter)
EOF

cat > solver_lib/CMakeLists.txt <<EOF
add_library(solver STATIC solver.cpp)
EOF

cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.10)
project(formatter_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(formatter_lib formatter_ex_lib solver_lib)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)

add_executable(hello_world hello_world_application/main.cpp)
target_link_libraries(hello_world formatter)

add_executable(solver_app solver_application/main.cpp)
target_link_libraries(solver_app formatter solver)
EOF

```
</details>

Подготовка проекта к сборке `cmake -B _build`

<details>
<summary>Вывод</summary>

```bash
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/aleksandrgolikov/workspace/projects/laba3/_build
```
</details>

Сборка проекта `cmake --build _build`

<details>
<summary>Вывод</summary>

```bash
[ 10%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 20%] Linking CXX static library libformatter.a
[ 20%] Built target formatter
[ 30%] Linking CXX executable hello_world
[ 40%] Built target hello_world
[ 50%] Building CXX object solver_lib/CMakeFiles/solver.dir/solver.cpp.o
[ 60%] Linking CXX static library libsolver.a
[ 60%] Built target solver
[ 70%] Linking CXX executable solver_app
[ 80%] Built target solver_app
[ 90%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[100%] Linking CXX static library libformatter_ex.a
[100%] Built target formatter_ex
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

Для завершения работы проект был переведен на модульную систему сборки, а все изменения зафиксированы в Git и синхронизированы с удаленным репозиторием GitHub:

`git add .`

`git commit -m "added modular cmake structure"`

<details>
<summary>Вывод</summary>

```bash
[main 0bfc51a] added modular cmake structure
 4 files changed, 8 insertions(+), 8 deletions(-)
 create mode 100644 formatter_ex_lib/CMakeLists.txt
 create mode 100644 formatter_lib/CMakeLists.txt
 create mode 100644 solver_lib/CMakeLists.txt
```
</details>

`git pull origin main --no-rebase`

<details>
<summary>Вывод</summary>

```bash
Из github.com:2dmpjv8fgy-commits/laba3
 * branch            main       -> FETCH_HEAD
Merge made by the 'ort' strategy.
 README.md | 247 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 247 insertions(+)
```
</details>

`git push origin main`

<details>
<summary>Вывод</summary>

```bash
Перечисление объектов: 21, готово.
Подсчет объектов: 100% (17/17), готово.
При сжатии изменений используется до 12 потоков
Сжатие объектов: 100% (9/9), готово.
Запись объектов: 100% (11/11), 1.18 KiB | 1.18 MiB/s, готово.
```
</details>
