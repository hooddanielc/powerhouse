FROM dhoodlum/arch-base-devel

RUN echo "en_US.UTF-8 UTF-8" >> /etc/locale.gen
RUN locale-gen
RUN echo "LANG=en_US.UTF-8" > /etc/locale.conf
RUN pacman --noconfirm -S \
  zsh \
  git \
  wget \
  sudo \
  clang \
  openssl \
  zlib \
  nano \
  inotify-tools \
  ntp \
  cmake \
  python-pip \
  postgresql \
  curl \
  libutil-linux \
  gsasl \
  gnutls \
  gtk3 \
  python \
  cmake \
  iputils \
  nano \
  vi \
  vim \
  iproute2 \
  libuv \
  exim

# enable ntp
ADD ntp.conf /etc/ntp.conf
RUN systemctl enable ntpd.service
RUN systemctl enable ntpdate.service

# add and use developer user
RUN useradd -m -G wheel -s /bin/zsh developer
RUN echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
