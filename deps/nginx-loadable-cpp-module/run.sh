DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
sudo docker run --rm \
  -v $DIR/test-config:/home/developer/test-config \
  -v $DIR/ngx_loadable_cpp_module.c:/opt/ngx-loadable-cpp-module/ngx_loadable_cpp_module.c \
  -ti dhoodlum/nginx-loadable-cpp-module zsh