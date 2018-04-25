set -e
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DEPS=(
  aws-sdk-cpp
  libvmime
  nlohmann-json
  nginx-loadable-cpp-module
  libpqxx
  libuws
)

for dep in ${DEPS[@]}; do
  if [ ! -d $DIR/$dep/pkg ]; then
    mkdir -p $DIR/$dep/pkg
    sudo docker build -t dhoodlum/${dep} -f $DIR/${dep}/Dockerfile $DIR/$dep
    sudo docker run dhoodlum/${dep}
    sudo docker cp $(sudo docker ps -q -l):/dhoodlum/$dep $DIR/$dep/pkg
    sudo docker rm $(sudo docker ps -q -l)
  fi
done
