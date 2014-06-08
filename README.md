Evening Prayer
==============

## Bulding/Running

 * When running the app, be sure to use `sudo make run` because the wiringPi lib seems to require sudo access to work

## Environments

The goal is to allow development on osx with the Raspberry Pi as the production target. There are some gotchas with switching between them, which are documented here. The goal is to maintain tagged versions in a state that will build & run on Raspberry Pi.

### OSX

#### config.make

Uncomment the following line (should be noted in the comments)

	PROJECT_LDFLAGS=-Wl, -L$(WIRING_PI_LIB_DIR) $(WIRING_PI_LIB)

### Raspberry Pi


#### config.make

Uncomment the following line (should be noted in the comments)

	PROJECT_LDFLAGS=-Wl,-rpath=./libs -L$(WIRING_PI_LIB_DIR) $(WIRING_PI_LIB)
