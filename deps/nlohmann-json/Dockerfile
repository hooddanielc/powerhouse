FROM dhoodlum/powerhouse-common

RUN sudo mkdir /opt/json && sudo chown developer /opt/json
RUN git clone https://github.com/nlohmann/json.git /opt/json
WORKDIR /opt/json
RUN sudo mkdir -p /dhoodlum/nlohmann-json/usr/include/nlohmann
RUN sudo cp single_include/nlohmann/json.hpp /dhoodlum/nlohmann-json/usr/include/nlohmann
VOLUME /dhoodlum/nlohmann-json
