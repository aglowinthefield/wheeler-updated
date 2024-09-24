set(sources ${sources}
    src/plugin.cpp
    src/hook.cpp

    src/bin/Animation/TimeInterpolator/TimeFloatInterpolator.cpp
    src/bin/Animation/TimeInterpolator/TimeInterpolatorManager.cpp

    src/bin/Animation/TimeBounceInterpolator.cpp
    src/bin/Animation/TimeColorInterpolator.cpp
    src/bin/Animation/TimeTrapezoidInterpolator.cpp

    src/bin/Rendering/Drawer.cpp
    src/bin/Rendering/RenderManager.cpp
    src/bin/Rendering/TextureManager.cpp

    src/bin/Serialization/SerializationEntry.cpp

    src/bin/UserInput/Controls.cpp
    src/bin/UserInput/Input.cpp

    src/bin/Utilities/UniqueIDHandler.cpp
    src/bin/Utilities/Utils.cpp

    src/bin/Wheeler/WheelItems/WheelItem.cpp
    src/bin/Wheeler/WheelItems/WheelItemAlchemy.cpp
    src/bin/Wheeler/WheelItems/WheelItemAmmo.cpp
    src/bin/Wheeler/WheelItems/WheelItemArmor.cpp
    src/bin/Wheeler/WheelItems/WheelItemFactory.cpp
    src/bin/Wheeler/WheelItems/WheelItemLight.cpp
    src/bin/Wheeler/WheelItems/WheelItemMisc.cpp
    src/bin/Wheeler/WheelItems/WheelItemMutable.cpp
    src/bin/Wheeler/WheelItems/WheelItemMutableManager.cpp
    src/bin/Wheeler/WheelItems/WheelItemScroll.cpp
    src/bin/Wheeler/WheelItems/WheelItemShout.cpp
    src/bin/Wheeler/WheelItems/WheelItemSpell.cpp
    src/bin/Wheeler/WheelItems/WheelItemWeapon.cpp

    src/bin/Wheeler/Wheel.cpp
    src/bin/Wheeler/WheelEntry.cpp
    src/bin/Wheeler/Wheeler.cpp

    src/bin/Config.cpp
    src/bin/Hooks.cpp
    src/bin/main.cpp
    src/bin/ModCallbackEventHandler.cpp
    src/bin/Texts.cpp

    src/include/lib/imgui_freetype.cpp
)