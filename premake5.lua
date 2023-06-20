-- premake5.lua

workspace "MyGame"
    configurations { "Debug", "Release" }

project "game"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files {
      "banana/src/**.cpp",
      "sandbox/src/**.cpp",
      "banana/include/**.h",
      "sandbox/include/**.h"
    }

    includedirs {
        "banana/",
        "banana/include/",
        "sandbox/",
        "sandbox/include/"
    }

    links {
        "SDL2",
        "GL",
        "X11",
        "pthread",
        "Xrandr",
        "Xi",
        "dl",
        "m"
    }

    defines {
        "MACRO_SDL2",
        "MACRO_OPENGL"
    }

    filter "configurations:Debug"
        symbols "On"
        warnings "Extra"

    filter "configurations:Release"
        optimize "On"
        warnings "Extra"