FROM ubuntu:18.04

ARG UBUNTU_MIRROR

# Basic packages and dependencies of docker-systemctl-replacement
RUN echo locales locales/default_environment_locale select en_US.UTF-8 | debconf-set-selections \
    && echo locales locales/locales_to_be_generated select "en_US.UTF-8 UTF-8" | debconf-set-selections \
    && { [ ! "$UBUNTU_MIRROR" ] || sed -i "s|http://\(\w*\.\)*archive\.ubuntu\.com/ubuntu/\? |$UBUNTU_MIRROR |" /etc/apt/sources.list; } \
    # This restores man pages and other documentation that have been
    # stripped from the default Ubuntu cloud image and installs
    # ubuntu-minimal and ubuntu-standard.
    #
    # This makes sense to do because we're using this image as a
    # development environment, not a minimal production system.
    && printf 'y\n\n' | unminimize \
    && apt-get install --no-install-recommends -y \
           ca-certificates \
           curl \
           locales \
           lsb-release \
           openssh-server \
           python3 \
           sudo \
           systemd \
    && rm -rf /var/lib/apt/lists/*

ARG VAGRANT_UID

ARG USER_NAME=alick
ARG USER_GROUP=alick
ARG USER_PASSWORD=1

# add build data.
ADD data/* /build_data/

RUN \
    # We use https://github.com/gdraheim/docker-systemctl-replacement
    # to make services we install like postgres, redis, etc. normally
    # managed by systemd start within Docker, which breaks normal
    # operation of systemd.
    dpkg-divert --add --rename /bin/systemctl \
    && cp /build_data/systemctl3.py /bin/systemctl \
    && chmod +x /bin/systemctl \
    && ln -nsf /bin/true /usr/sbin/policy-rc.d \
    && mkdir -p /run/sshd \
    # docker-systemctl-replacement doesn’t work with template units yet:
    # https://github.com/gdraheim/docker-systemctl-replacement/issues/62
    && ln -ns /lib/systemd/system/postgresql@.service /etc/systemd/system/multi-user.target.wants/postgresql@10-main.service \
    # redis fails to start with the default configuration if IPv6 is disabled:
    # https://github.com/antirez/redis/pull/5598
    && dpkg-divert --add --rename /etc/default/redis-server \
    && printf 'ULIMIT=65536\nDAEMON_ARGS="/etc/redis/redis.conf --bind 127.0.0.1"\n' > /etc/default/redis-server \
    && mkdir /etc/systemd/system/redis-server.service.d \
    && printf '[Service]\nExecStart=\nExecStart=/usr/bin/redis-server /etc/redis/redis.conf --bind 127.0.0.1\n' > /etc/systemd/system/redis-server.service.d/override.conf

# add default user.
RUN /bin/bash -c "groupadd -r -g 1000 $USER_NAME;\
    useradd -r -u 1000 -g $USER_NAME $USER_NAME -m -s /bin/bash;\
    echo \"${USER_NAME}:${USER_PASSWORD}\"|chpasswd;\
    usermod -aG sudo $USER_NAME"

CMD ["/bin/systemctl"]

EXPOSE 22
