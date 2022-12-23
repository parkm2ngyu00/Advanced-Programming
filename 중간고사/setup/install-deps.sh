#!/bin/bash

sudo apt-get update
sudo apt-get -y install net-tools iproute2 # ifconfig, ip

sudo apt-get -y install build-essential # gcc, make
sudo apt-get -y install libpcap-dev # libpcap

sudo apt-get -y install python3-pip # python3
sudo pip3 install flask requests # flask, requests
