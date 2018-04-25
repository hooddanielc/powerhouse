FROM dhoodlum/powerhouse-common
RUN sudo mkdir /opt/libuWS && sudo chown developer /opt/libuWS
RUN git clone https://github.com/uNetworking/uWebSockets.git /opt/libuWS
WORKDIR /opt/libuWS
RUN make -j$(grep -c ^processor /proc/cpuinfo) Linux
RUN sudo make PREFIX=/dhoodlum/libuws/usr install

VOLUME /dhoodlum/libuws

CMD bash
