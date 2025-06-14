# phil-common-remap

A plugin for Interception Tools with my common remaps.

## Features
 - Remap CAPSLOCK to ESC, similar to [caps2esc](https://gitlab.com/interception/linux/plugins/caps2esc) without the caps-esc swap or caps to esc/ctrl nonesense.
 - Swap left alt and meta, which is useful when the super and alt key caps are swapped on a keyboard to make the layout more ideal for macOS.

## Dependencies
 - [Interception Tools](https://gitlab.com/interception/linux/tools)

## Installing
```
$ git clone https://github.com/philanatidae/phil-common-remap.git
$ cd phil-common-remap
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
$ cmake --install
```

## License
The Unlicense. See `LICENSE`.
