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

    }
    
    includedirs {
      "%{IncludeDir.GLFW}",
      "%{IncludeDir.GLAD}",
      "%{IncludeDir.IMGUI}",
      "%{IncludeDir.GLM}",
      "%{IncludeDir.STB}",
      "%{IncludeDir.MSDFATLASGEN}",
      "%{IncludeDir.MSDF}",
      "%{IncludeDir.MSDFINC}",
      "%{wks.location}/Banana",
      "%{wks.location}/Banana/src",
      "%{wks.location}/Banana/src/generic"
    }


  filter "configurations:Debug"
    defines "BUILD_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "BUILD_RELEASE"
    optimize "On"
