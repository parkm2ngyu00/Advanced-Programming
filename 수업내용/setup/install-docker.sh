#!/bin/bash

# update repo
sudo apt-get update

# add GPG key
sudo apt-get install -y curl
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

# add Docker repository
sudo apt-get install -y software-properties-common
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"

# update repo
sudo apt-get update

# install Docker
sudo apt-get install -y docker-ce

# start Docker
sudo systemctl enable docker
sudo systemctl restart docker

# wait for a while
sleep 1

# add user to Docker
if [[ -d /home/vagrant ]]; then
    sudo usermod -aG docker vagrant
else
    sudo usermod -aG docker $USER
fi

# allow non-root user to access docker.sock
sudo chmod 666 /var/run/docker.sock

# install docker-compose
sudo curl -sL https://github.com/docker/compose/releases/download/1.29.2/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
