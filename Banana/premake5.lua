project "Banana"
    kind "StaticLib"
    language "C++"

    targetdir "%{wks.location}/bin/target/%{cfg.buildcfg}/%{prj.name}"
    objdir "%{wks.location}/bin/obj/%{cfg.buildcfg}/%{prj.name}"
  
    files {
      "%{wks.location}/Banana/src/**.cpp",
      "%{wks.location}/Banana/include/**.h"
    }

    includedirs {
        "%{wks.location}/Banana/include/engine/",
        "%{wks.location}/Banana/include/"
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
    defines "BUILD_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "BUILD_RELEASE"
    optimize "On"
