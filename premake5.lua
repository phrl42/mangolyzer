-- premake5.lua

workspace "Banana"
    configurations { "Debug", "Release" }
    staticruntime "off"

IncludeDir = {}


group "engine"
include "Banana/"
group ""

group "game"
include "Sandbox/"
group ""
