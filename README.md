![alt tag](https://hypelabs.io/static/img/NQMAnSZ.jpg)
![alt tag](https://hypelabs.io/static/img/logo200x.png)

[Hype](https://hypelabs.io/?r=10) is an SDK for cross-platform peer-to-peer communication with mesh networking. Hype works even without Internet access, connecting devices via other communication channels such as Bluetooth, Wi-Fi direct, and Infrastructural Wi-Fi.

The Hype SDK has been designed by [Hype Labs](http://hypelabs.io/?r=10). It is currently available for multiple platforms.

You can [start using Hype](http://hypelabs.io/?r=10) today.

## Project

This project is a decentralized peer-to-peer publisher-subscriber system powered by the HypeSDK, for the Linux platform. Due to its decentralized nature this system is more robust than traditional publisher-subscriber systems that usually requires a centralized broker to serve as intermediary between publishers and subscribers. You can find out a detailed description of the system in this [article](https://medium.com/@hypelabs.io). You can also see a demonstration video of the system [here](https://www.youtube.com/watch?v=2fMwe3q1NYc&t=2s).


## Setup

This demo does not work out of the box. The following are the necessary steps to configure it:

 1. [Download](https://hypelabs.io/downloads/?r=9) the SDK binaries for the Linux platform.
 2. Extract it, and drag the folder named *hype*, which is located inside the folder named *lib*, to the project root folder
 3. Access the [apps](https://hypelabs.io/apps/?r=9) page and create a new app
 4. Name the app and press "Create new app"
 5. Go to the app settings
 6. Copy the identifier under `App ID`
 7. In the file *include/hype_pub_sub/hpb_constants.h*, find the line that reads `#define HPB_HYPE_APP_IDENTIFIER "{{app_identifier}}"`
 8. Replace `{{app_identifier}}` by the App ID you just copied
 9. Go back to the app settings
 10. This time, copy the `Access Token`, under the Authorization group
 11. Open the same file, *include/hype_pub_sub/hpb_constants.h*, and find the line that reads `#define HPB_HYPE_ACCESS_TOKEN "{{access_token}}"`
 12. Replace `{{access_token}}` by the token you just copied

You should be ready to go! If you run into trouble, feel free to reach out to our [community](https://hypelabs.io/community/?r=9) or browse our other [support](https://hypelabs.io/support/?r=9) options. Also keep in mind our project templates on the [apps](https://hypelabs.io/apps/?r=9) page for demos working out of the box.


## Compilation

The project can be compiled using the provided CMakeLists file. You can compile the project using the following commands:

```bash
mkdir -p build && cd build
cmake -G "Unix Makefiles" -DABI={{ABI}} ../
make

NOTE: {{ABI}} must be replaced by a valid Hype SDK architecture: amd64, i686, armel or armhf.

```

If you also want to compile the unit tests you can use the following commands (This requires the CUnit test framework to be installed):

```bash
mkdir -p build && cd build
cmake -G "Unix Makefiles" -DHYPE_PUB_SUB_COMPILE_TESTS=ON -DABI={{ABI}} ../
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