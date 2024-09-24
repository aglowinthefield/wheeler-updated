set(headers ${headers}
	src/PCH.h 
    src/log.h
    src/util.h
    src/hook.h 
    src/settings.h

    src/bin/Animation/TimeInterpolator/TimeFloatInterpolator.h
    src/bin/Animation/TimeInterpolator/TimeInterpolatorManager.h

    src/bin/Animation/TimeBounceInterpolator.h
    src/bin/Animation/TimeColorInterpolator.h
    src/bin/Animation/TimeTrapezoidInterpolator.h

    src/bin/Rendering/Drawer.h
    src/bin/Rendering/RenderManager.h
    src/bin/Rendering/TextureManager.h

    src/bin/Serialization/SerializationEntry.h

    src/bin/UserInput/Controls.h
    src/bin/UserInput/Input.h

    src/bin/Utilities/UniqueIDHandler.h
    src/bin/Utilities/Utils.h

    src/bin/Wheeler/WheelItems/WheelItem.h
    src/bin/Wheeler/WheelItems/WheelItemAlchemy.h
    src/bin/Wheeler/WheelItems/WheelItemAmmo.h
    src/bin/Wheeler/WheelItems/WheelItemArmor.h
    src/bin/Wheeler/WheelItems/WheelItemFactory.h
    src/bin/Wheeler/WheelItems/WheelItemLight.h
    src/bin/Wheeler/WheelItems/WheelItemMisc.h
    src/bin/Wheeler/WheelItems/WheelItemMutable.h
    src/bin/Wheeler/WheelItems/WheelItemMutableManager.h
    src/bin/Wheeler/WheelItems/WheelItemScroll.h
    src/bin/Wheeler/WheelItems/WheelItemShout.h
    src/bin/Wheeler/WheelItems/WheelItemSpell.h
    src/bin/Wheeler/WheelItems/WheelItemWeapon.h

    src/bin/Wheeler/Wheel.h
    src/bin/Wheeler/WheelEntry.h
    src/bin/Wheeler/Wheeler.h

    src/bin/Config.h
    src/bin/Hooks.h
    src/bin/ModCallbackEventHandler.h
    src/bin/Texts.h

    src/include/lib/imgui_freetype.h
    src/include/lib/nanosvg.h
    src/include/lib/nanosvgrast.h
)