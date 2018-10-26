![alt tag](https://hypelabs.io/static/img/NQMAnSZ.jpg)
![alt tag](https://hypelabs.io/static/img/logo200x.png)

[Hype](https://hypelabs.io/?r=10) is an SDK for cross-platform peer-to-peer communication with mesh networking. Hype works even without Internet access, connecting devices via other communication channels such as Bluetooth, Wi-Fi direct, and Infrastructural Wi-Fi.

The Hype SDK has been designed by [Hype Labs](http://hypelabs.io/?r=10). It is currently available for multiple platforms.

You can [start using Hype](http://hypelabs.io/?r=10) today.

## Project

This project is a decentralized peer-to-peer publisher-subscriber system powered by the HypeSDK, for the Linux platform. Due to its decentralized nature this system is more robust than traditional publisher-subscriber systems that usually requires a centralized broker to serve as intermediary between publishers and subscribers. You can find out a detailed description of the system in this [article](https://medium.com/@hypelabs.io). You can also see a demonstration video of the system [here](https://www.youtube.com/watch?v=2fMwe3q1NYc&t=2s).

## Compilation

The project can be compiled using the provided CMakeLists file. You can compile the project using the following commands:

```bash
mkdir -p build && cd build
cmake -G "Unix Makefiles" ../
make
```

If you also want to compile the unit tests you can use the following commands (This requires the CUnit test framework to be installed):

```bash
mkdir -p build && cd build
cmake -G "Unix Makefiles" -DHYPE_PUB_SUB_COMPILE_TESTS=ON ../
make
```

## Other platforms

Besides Linux, this project is available for the following platforms:

[Android](https://github.com/Hype-Labs/pubsub.android) <br>
[iOS](https://github.com/Hype-Labs/pubsub.ios)

## License

This project is MIT-licensed.

## Follow us

Follow us on [twitter](http://www.twitter.com/hypelabstech) and [facebook](http://www.facebook.com/hypelabs.io). We promise to keep you up to date!