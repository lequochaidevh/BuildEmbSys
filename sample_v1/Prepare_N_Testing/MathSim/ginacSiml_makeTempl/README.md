sudo apt update
sudo apt install libginac-dev -y

g++ ginac_ex.cpp -o ginac_ex -I/usr/include -L/usr/lib -lginac -lcln