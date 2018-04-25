DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
$DIR/common/build.sh
$DIR/deps/build.sh
docker build -t dhoodlum/powerhouse $DIR
