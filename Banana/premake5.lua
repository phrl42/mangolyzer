project "Banana"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    targetdir "%{wks.location}/bin/target/%{cfg.buildcfg}/%{prj.name}"
    objdir "%{wks.location}/bin/obj/%{cfg.buildcfg}/%{prj.name}"

    pchheader "include/incs.h"
  
    files {
      "%{wks.location}/Banana/src/**.cpp",
      "%{wks.location}/Banana/include/**.h"
    }

    links {
      "GLFW",
    }
    

    includedirs {
        "%{wks.location}/Banana/include/engine/",
        "%{wks.location}/Banana/include/"
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
