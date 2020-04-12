# my docker ubuntu14.04
FROM ubuntu:18.04

ARG USER_NAME=alick
ARG USER_PASSWORD=1

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
RUN /bin/bash -c "groupadd -r -g 1000 $USER_NAME;\
useradd -r -u 1000 -g $USER_NAME $USER_NAME -m -s /bin/bash;\
echo \"${USER_NAME}:${USER_PASSWORD}\"|chpasswd;\
usermod -aG sudo $USER_NAME"

# config sshd workdir
RUN mkdir /run/sshd

# USER ${USER_NAME}
# WORKDIR /home/${USER_NAME}

EXPOSE 22/tcp
CMD ["/usr/sbin/sshd", "-D"]

