# How to compile and run the code

## Tested on ubuntu 18.04, gcc 7.5.0:
1. Clone the repository: 
```
git clone https://github.com/KeeJin/Realtime-Software-Module-Project.git
```
2. Checkout the correct branch:
```
git checkout feature-code_integration
```
3. Run the bash script from within the 'scripts' folder:
```
cd scripts
./build_app_shape_database.sh
```
### If the bash script fails to run, you might not have the necessary execute permissions (check with ```ls -la```). If this is the issue, run: 
```
sudo chmod +x build_app_shape_database.sh
```