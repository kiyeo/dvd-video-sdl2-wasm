# dvd-video-sdl2-wasm

A [demo](https://kiyeo.github.io/dvd-video-sdl2-wasm/) utlizing c++, sdl2, sdl2-image and wasm generated from emscripten on a custom html document

```
emcc dvd.cpp -s USE_SDL=2 -s USE_SDL_IMAGE=2 -O3 -o index.js --preload-file ./ --use-preload-plugins
python3 -m http.server 8080
```

NOTE: The gh-pages branch contains the compiled code and can be run using the `python3 -m http.server 8080`
