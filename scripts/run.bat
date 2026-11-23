@echo off

:: Поднимаемся из папки scripts в корень проекта
cd ..

:: Создаем папку build, если ее еще нет
if not exist build mkdir build

:: Переходим в созданную папку сборки
cd build

:: Генерируем конфигурационные файлы CMake
cmake ..

:: Запускаем саму компиляцию (сборку) проекта
cmake --build . --config Debug

:: Если сборка успешна (код ошибки 0), открываем решение VS
if %errorlevel% equ 0 start DataStructure.sln

:: Держим окно открытым, чтобы увидеть результат
pause