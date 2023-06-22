project "Sandbox"
  kind  "ConsoleApp"
  language "C++"
  staticruntime "off"

  targetdir "%{wks.location}/bin/target/%{cfg.buildcfg}/%{prj.name}"
  objdir "%{wks.location}/bin/obj/%{cfg.buildcfg}/%{prj.name}"
    
  files {
    "src/**.cpp",
    "src/**.h",
    "src/**.hpp"
  }

  includedirs {
      "%{IncludeDir.GLFW}",
      "%{wks.location}/Banana",
      "%{wks.location}/Banana/src",
      "%{wks.location}/Banana/src/banana",

      "%{wks.location}/Sandbox",
      "%{wks.location}/Sandbox/src"
  }

  links {
    "Banana",
    "GLFW"
  }

  filter "configurations:Debug"
    defines "BUILD_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "BUILD_RELEASE"
    optimize "On"