project "HotReloading"
    kind "SharedLib"
    language "C++"

    targetdir "%{wks.location}/bin/target/%{cfg.buildcfg}/%{prj.name}"
    objdir "%{wks.location}/bin/obj/%{cfg.buildcfg}/%{prj.name}"

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
      "%{IncludeDir.MINIAUDIO}",
      "%{wks.location}/Banana",
      "%{wks.location}/Banana/src",
      "%{wks.location}/Banana/src/generic",

      "%{wks.location}/Sandbox",
      "%{wks.location}/Sandbox/src" 
      }


filter "configurations:Debug"
defines "BUILD_DEBUG"
symbols "On"

filter "configurations:Release"
defines "BUILD_RELEASE"
optimize "On"
