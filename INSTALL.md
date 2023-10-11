## Requirements

To fully compile **Elvex**, make sure you have the following tools installed on your computer:

- g++
- flex
- bison
- libxml2-dev
- cmake

## Download

To download **Elvex**, follow this command: 

```shell
git clone https://github.com/lionelclement/Elvex.git
```

## Compilation

To compile **Elvex**, follow these commands from the Elvex directory:

1. Run: `cmake .`
2. Run: `make -j 7`
3. Run: `sudo make install`

## Testing

After you have successfully compiled **Elvex**, execute the following command:

```shell
make -s -f Makefile.test test
```
