# my docker ubuntu14.04
FROM ubuntu:14.04
LABEL version='1.0'
MAINTAINER alick97
# apt update and install package
RUN apt-get update && apt-get install -y \
gcc \
g++ \
python3 \
ssh \
vim
# add default user
RUN /bin/bash -c 'groupadd -r -g 1000 alick;\
useradd -r -u 1000 -g alick alick -m -s /bin/bash;\
echo "alick:0"|chpasswd;\
usermod -aG sudo alick'
USER alick
WORKDIR /home/alick