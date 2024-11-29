#!/bin/bash
chmod +x "$0"

DOCKER_WAS_INSTALLED=false

if ! command -v docker &> /dev/null; then
    curl -fsSL https://get.docker.com -o get-docker.sh
    sudo sh get-docker.sh
    sudo usermod -aG docker $USER
    sudo systemctl enable docker
    sudo systemctl start docker
    DOCKER_WAS_INSTALLED=true
fi

docker build -t rogue .
docker run --rm -it rogue
docker rmi rogue

if [ "$DOCKER_WAS_INSTALLED" = true ]; then
    sudo systemctl stop docker
    sudo systemctl disable docker
    sudo apt-get purge -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
    sudo rm -rf /var/lib/docker
    sudo rm -rf /var/lib/containerd
    sudo apt-get autoremove -y
fi