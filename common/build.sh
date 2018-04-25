DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
docker build -t dhoodlum/powerhouse-common $DIR
