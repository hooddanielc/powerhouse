FROM dhoodlum/powerhouse-common

# set default make flags
RUN echo MAKEFLAGS=\"-j$(grep -c ^processor /proc/cpuinfo)\" >> /etc/makepkg.conf

# install local packages
ADD deps/aws-sdk-cpp/pkg/aws-sdk-cpp /
ADD deps/libvmime/pkg/libvmime /
ADD deps/nginx-loadable-cpp-module/pkg/nginx-loadable-cpp-module /
ADD deps/nlohmann-json/pkg/nlohmann-json /
ADD deps/libpqxx/pkg/libpqxx /
ADD deps/libuws/pkg/libuws/usr/include /usr/include
ADD deps/libuws/pkg/libuws/usr/lib64/libuWS.so /usr/lib/libuWS.so

# use developer user
USER developer

# add command for updating timezone automatically
RUN git clone https://aur.archlinux.org/tzupdate.git /home/developer/tzupdate
RUN cd /home/developer/tzupdate && makepkg -s --noconfirm
RUN sudo pacman --noconfirm -U /home/developer/tzupdate/*.pkg.tar.xz
RUN sudo tzupdate

# install ohmyzsh
RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true

# install ib
RUN sudo rm -rf /opt/ib
RUN sudo mkdir /opt/ib && sudo chown -R developer /opt/ib
RUN git clone --branch fix-symlink https://github.com/hooddanielc/ib.git /opt/ib
RUN chmod +x /opt/ib/ib

# install python packages
RUN sudo pip install pyinotify
RUN sudo pip install alembic
RUN sudo pip install psycopg2

ADD ./config/.zshrc /home/developer/.zshrc
RUN sudo chown developer /home/developer/.zshrc

CMD /bin/zsh
