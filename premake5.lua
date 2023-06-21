-- premake5.lua

workspace "Banana"
    configurations { "Debug", "Release" }
    staticruntime "off"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Banana/vendor/GLFW/include"

LibDir = {}
LibDir["GLFW"] = "%{wks.location}/Banana/vendor/GLFW/lib"
 
includedirs{
  "%{IncludeDir.GLFW}"
}

libdirs {
  "%{LibDir.GLFW}"
}

links {
  "glfw3",
  "dl",
  "m",
  "GL",
  "X11",
  "Xi"
}

group "engine"
include "Banana/"
group ""

group "game"
include "Sandbox/"
group ""
