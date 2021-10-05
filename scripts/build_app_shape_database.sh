# Simple script to automate compilation and execution
echo "INFO: This script assumes that you are running from the \"scripts\" folder."
echo "Compiling..."

# Check if a directory does not exist
# if [ -d "/test_bed/build" ]
# then
#     echo "Build folder exists." 
# else
#     echo "Creating build folder..." 
mkdir -p ../build
# fi

cd ../build

# Compilation
cc -I ../include/ -c ../app/app_shape_database.c
cc -I ../include/ -c ../src/menu_components.c
cc -I ../include/ -c ../src/linked_list_struct.c
cc -I ../include/ -c ../src/graphical.c

# Linking
cc app_shape_database.o menu_components.o linked_list_struct.o graphical.o -o app_main -lm

# Execution
./app_main
