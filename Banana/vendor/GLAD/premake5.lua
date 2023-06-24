project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "off"

  targetdir "%{wks.location}/bin/target/%{cfg.buildcfg}/%{prj.name}"
  objdir "%{wks.location}/bin/obj/%{cfg.buildcfg}/%{prj.name}"


	files{
		"src/glad.c",
	}

  includedirs{
    "include/"
  }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
