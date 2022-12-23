#!/bin/bash

sudo apt-get update
sudo apt-get -y install build-essential # gcc, make
sudo apt-get -y install net-tools iproute2 iputils-ping # ifconfig, ip, ping
sudo apt-get -y install tcpdump # tcpdump
sudo apt-get -y install libpcap-dev # libpcap
sudo apt-get -y install libssl-dev # openssl
