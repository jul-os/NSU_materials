#add_executable(main main.cpp naming.h BitArray.cpp tests.cpp)

#add_executable(print_recursive main.cpp module1.h module1.cpp module2.h module2.cpp)
#the basic и он работает

cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Проверка версии CMake.
										# Если версия установленой программы
										# старее указаной, произайдёт аварийный выход.

project(namespaces)			# Название проекта

set(SOURCE_EXE main.cpp)		# Установка переменной со списком исходников для исполняемого файла

set(SOURCE_LIB BitArray.cpp tests.cpp)			# Тоже самое, но для библиотеки

add_library(BitArray STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

target_link_libraries(main BitArray)		# Линковка программы с библиотекой


enable_testing()

# Find any installed Google Test.
find_package(GTest REQUIRED)

# Add an executable target for the source file.
add_executable(tests tests.cpp)

# Link the target to the gtest_main library.
target_link_libraries(tests GTest::Main)

# Discover tests in the target and add them to the project.
# This function (as well as gtest_add_tests()) is intended to replace add_test()
# when using Google Test.
gtest_discover_tests(tests)