workspace "Hazel"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" --Debug-Windows-x64

-- include directory relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"
IncludeDir["ImGui"] = "Hazel/vendor/imgui"

include "Hazel/vendor/GLFW"   --include Hazel/vendor/GLFW/premake5.lua
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"
project "Hazel"
	location "Hazel"
	kind "SharedLib" --dll
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off" --linking the runtime library
		systemversion "latest"

		defines
		{
			"HZ_BUILD_DLL",
			"HZ_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
		}

		--create a postbuild step to put the .dll where we want to be
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")
		}

		filter "configurations:Debug" --only apply to Debug configurations
			defines "HZ_DEGUG"
			--buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release" --only apply to Debug configurations
			defines "HZ_RELEASE"
			--buildoptions "/MD"
			optimize "On"
		
		filter "configurations:Dist" --only apply to Debug configurations
			defines "HZ_DIST"
			--buildoptions "/MD"
			optimize "On"
			
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" --.exe
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")



	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"

	}

	links{
		"Hazel"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off" --linking the runtime library
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
		}

		filter "configurations:Debug" --only apply to Debug configurations
			defines "HZ_DEGUG"
			--buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release" --only apply to Debug configurations
			defines "HZ_RELEASE"
			--buildoptions "/MD"
			optimize "On"
		
		filter "configurations:Dist" --only apply to Debug configurations
			defines "HZ_DIST"
			--buildoptions "/MD"
			optimize "On"