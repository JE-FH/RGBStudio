# RGBStudio
Corsair, ASUS, Logitech, etc. each have different software for controlling RGB for all their devices. This application will be able to control all devices through their SDK. This enables you to have one place for all functionality and gives every compatible device the same feature set.
## Features
* Layered color effects
* Lua scripting to create custom effects
* Trigger effects on many different input source eg. controllers, mice, special buttons available through SDK.

## Version 1.0 release goals
* Lua scripting
* Supporting only keyboards
* Supporting ASUS aura devices

## Building
vcpkg makes everything easier, but the only requirement is lua 5.4, [rpclib](https://github.com/rpclib/rpclib.git) and nlohmann-json

If you use MSVC to build, it currently has a bug with #import statements where it does not look for the generated tlh and tli where it has generated them,
instead it looks in the root folder. Other than this there is another bug where it generates the correct x64 tlh and tli files but intellisense will look for the x86 versions
for no good reason. Therefore, build the project for x86, then copy the generated AuraSDK_x86.{tlh|tli} from `build/src/asus_aura_adapter/asus_aura_adapter.dir/Debug/` to the
root folder. This will make everything work as intended.

For debugging you should use `bin/` as cwd since this is where needed dll's are copied to

Ninja generator does not work when including .targets files, therefore set generator to "Visual Studio 17 2022". We need to support .targets files since this how we import webview2

## Running
Current build requires you to create the config folder yourself. You have to create a folder called `RGBLightRunner` in documents and create two sub folders `effects` and `device adapters`. 
Put the built device adapter you need into the `device adapters` folder, when prompted for the file name of the adapter, it will concat the path to the `device adapters` folder with the name.
Put any lua effect you want to be loaded into the `effects` folder, RGBLightRunner will load all effects in the folder that has the `.lua` extension.
