-- premake5.lua

workspace "Banana"
    configurations { "Debug", "Release" }
    staticruntime "off"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Banana/vendor/GLFW/include/GLFW"

group "dependencies"
include "Banana/vendor/GLFW"
group ""

group "engine"
include "Banana/"
group ""

group "game"
include "Sandbox/"
group ""
