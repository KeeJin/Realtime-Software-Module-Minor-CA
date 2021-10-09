Write-Host "INFO: This script assumes that you are running from the \"scripts\" folder."
Write-Host "Creating..."

mkdir -p build/bin
cd build

Write-Host "Compiling..."
gcc -I ../include/ -c ../app/app_shape_database.c
gcc -DENV_WINDOWS -I ../include/ -c ../src/menu_components.c
gcc -I ../include/ -c ../src/linked_list_struct.c
gcc -I ../include/ -c ../src/graphical.c
Write-Host "Linking..."
gcc app_shape_database.o menu_components.o linked_list_struct.o graphical.o -o ./bin/app_main -lm
Write-Host "Executing..."
.\bin\app_main.exe