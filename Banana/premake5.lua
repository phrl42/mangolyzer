project "Banana"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    targetdir "%{wks.location}/bin/target/%{cfg.buildcfg}/%{prj.name}"
    objdir "%{wks.location}/bin/obj/%{cfg.buildcfg}/%{prj.name}"

    pchheader "incs.h"
  
    files {
      "src/**.cpp",
      "src/**.h",
      "src/**.hpp"
    }

    links {
      "GLFW",
    }
    
    includedirs {
      "%{IncludeDir.GLFW}",
      "%{wks.location}/Banana",
      "%{wks.location}/Banana/src",
      "%{wks.location}/Banana/src/generic"
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
