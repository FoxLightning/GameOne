#/bin/bash
mkdir -p lib/SDL ;
# TODO attach to commit or stable brunch
git clone --depth 1 https://github.com/libsdl-org/SDL ./lib/SDL  &&
git clone --depth 1 https://github.com/libsdl-org/SDL_Image ./lib/SDL_image &&
git clone --depth 1 https://github.com/libsdl-org/SDL_ttf ./lib/SDL_ttf

