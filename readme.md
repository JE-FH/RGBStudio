# Universal RGB Device Controller
Corsiar, ASUS, logitech, etc. each have different software for controlling RGB for all their devices. This application will be able to control all devices through their SDK. This enables you to have one place for all functionality and gives every compatible device the same feature set.
## Features
* Layered color effects
* Lua scripting to create custom effects
* Trigger effects on many different input source eg. controllers, mice, special buttons available through SDK.

## Version 1.0 release goals
* Lua scripting
* Supporting only keyboards
* Supporting ASUS aura devices

## Unplanned features
* Effects linking across devices

## TODO
[ ] EffectFactory and Effect should have a device attached instead of the effect manager
[ ] LuaStatePtr should track threads and somehow destroy itself when there are no threads or state references left, this would enable reloading script without having to delete all ongoing effects
[ ] Trigger functionality from EventTriggerController should be seperated more in a new class
