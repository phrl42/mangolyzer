project "Sandbox"
  kind  "ConsoleApp"
  language "C++"

  targetdir "%{wks.location}/bin/target/%{cfg.buildcfg}/%{prj.name}"
  objdir "%{wks.location}/bin/obj/%{cfg.buildcfg}/%{prj.name}"
  
  rules { "run" }
  
  files {
    "src/**.cpp",
    "include/**.h"
  }

  includedirs {
      "%{wks.location}/Banana/include/engine/",
      "%{wks.location}/Banana/include/",
      "%{wks.location}/Sandbox/",
      "%{wks.location}/Sandbox/include"
  }

  links {
    "Banana"
  }

  filter "configurations:Debug"
    defines "BUILD_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "BUILD_RELEASE"
    optimize "On"