FROM dhoodlum/powerhouse-common
RUN sudo mkdir -p /opt/libvmime && sudo chown -R developer /opt/libvmime
RUN sudo mkdir -p /dhoodlum/libvmime
RUN git clone https://github.com/kisli/vmime.git /opt/libvmime
RUN cd /opt/libvmime && git checkout a9b822140bf8926620fd21b880893d4c214dd8c0
RUN mkdir /opt/libvmime/build

WORKDIR /opt/libvmime/build

RUN cmake .. \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DLIB_INSTALL_DIR=/usr/lib/ \
    -DCMAKE_BUILD_TYPE=Release

RUN make -j$(grep -c ^processor /proc/cpuinfo)
RUN sudo make DESTDIR=/dhoodlum/libvmime install

VOLUME /dhoodlum/libvmime

CMD bash
