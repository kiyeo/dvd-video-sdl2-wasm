# dvd-video-sdl2-wasm

A [demo](https://kiyeo.github.io/dvd-video-sdl2-wasm/) utlizing c++, sdl2, sdl2-image and wasm generated from emscripten on a custom html document

Instructions:
-------------

1. Install Emscripten:

    http://emscripten.org

2. Clone this repo:

    ```
    git clone https://github.com/Kiyeo/dvd-video-sdl2-wasm
    cd dvd-video-sdl2-wasm
    ```
    
3. Build index.js and index.wasm:

    ```
    emcc dvd.cpp -s USE_SDL=2 -s USE_SDL_IMAGE=2 -O3 -o index.js --preload-file ./ --use-preload-plugins
    ```

4. Run a webserver and open localhost:

    with Python 2: 

    ```
    python -m SimpleHTTPServer 8080
    ```
    
    with Python 3:

    ```
    python -m http.server 8080
    ```

    and then open the following URL:

    http://localhost:8080/
    
5. You should see the classic dvd video logo:

    ![image](https://user-images.githubusercontent.com/52591219/138643352-632e3c0c-8aa2-4a69-a337-7e9cb930adce.gif)

NOTE: The gh-pages branch contains the compiled code

Compile locally
```
g++ dvd.cpp -lSDL2 -lSDL2_image -O3
```
