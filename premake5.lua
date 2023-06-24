-- premake5.lua

workspace "Banana"
    configurations { "Debug", "Release" }
    staticruntime "off"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Banana/vendor/GLFW/include/GLFW"
IncludeDir["GLAD"] = "%{wks.location}/Banana/vendor/GLAD/include/glad"

group "dependencies"
include "Banana/vendor/GLFW"
include "Banana/vendor/GLAD"
group ""

group "engine"
include "Banana/"
group ""

group "game"
include "Sandbox/"
group ""
