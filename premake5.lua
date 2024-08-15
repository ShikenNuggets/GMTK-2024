-- //-----------------------------------------------------------//
-- //---------------- Functions --------------------------------//
-- //-----------------------------------------------------------//

gRootPath = "GadgetEngine/"
dofile("GadgetEngine/premake/common.lua")

-- //-----------------------------------------------------------//
-- //---------------------- Workspace --------------------------//
-- //-----------------------------------------------------------//

workspace "GMTK-GameJam-2024"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Develop",
		"Release"
	}
	
	startproject "Game"

-- //-----------------------------------------------------------//
-- //------------------ External Projects ----------------------//
-- //-----------------------------------------------------------//

externalproject "Glad"
	location "GadgetEngine/SDK/_prj"
	filename "Glad"
	kind "StaticLib"
	language "C"

externalproject "SDL2"
	location "GadgetEngine/SDK/_prj"
	filename "SDL2"
	kind "SharedLib"
	language "C++"
	
externalproject "SDL2main"
	location "GadgetEngine/SDK/_prj"
	filename "SDL2main"
	kind "StaticLib"
	language "C++"
	dependson
	{
		"SDL2",
	}
	
externalproject "BulletCollision"
	location "GadgetEngine/SDK/_prj"
	filename "BulletCollision"
	kind "StaticLib"
	language "C++"
	
externalproject "BulletDynamics"
	location "GadgetEngine/SDK/_prj"
	filename "BulletDynamics"
	kind "StaticLib"
	language "C++"
	
externalproject "BulletLinearMath"
	location "GadgetEngine/SDK/_prj"
	filename "LinearMath"
	kind "StaticLib"
	language "C++"

externalproject "GadgetEngine"
	location "GadgetEngine/GadgetEngine"
	filename "GadgetEngine"
	kind "StaticLib"
	language "C++"
	dependson
	{
		"Glad",
		"SDL2",
		"SDL2main",
		"BulletCollision",
		"BulletDynamics",
		"BulletLinearMath",
	}

externalproject "GadgetDLL"
	location "GadgetEngine/GadgetDLL"
	filename "GadgetDLL"
	kind "SharedLib"
	language "C++"
	dependson
	{
		"Glad",
		"SDL2",
		"SDL2main",
		"BulletCollision",
		"BulletDynamics",
		"BulletLinearMath",
		"GadgetEngine",
	}

externalproject "Workbench"
	location "GadgetEngine/Workbench"
	filename "Workbench"
	kind "WindowedApp"
	language "C#"
	dependson
	{
		"Glad",
		"SDL2",
		"SDL2main",
		"BulletCollision",
		"BulletDynamics",
		"BulletLinearMath",
		"GadgetEngine",
		"GadgetDLL",
	}

externalproject "DataBuilder"
	location "GadgetEngine/DataBuilder"
	filename "DataBuilder"
	kind "ConsoleApp"
	language "C++"
	dependson
	{
		"Glad",
		"SDL2",
		"SDL2main",
		"BulletCollision",
		"BulletDynamics",
		"BulletLinearMath",
		"GadgetEngine",
	}

externalproject "Tests"
	location "GadgetEngine/Tests"
	filename "Tests"
	kind "ConsoleApp"
	language "C++"
	dependson
	{
		"Glad",
		"SDL2",
		"SDL2main",
		"BulletCollision",
		"BulletDynamics",
		"BulletLinearMath",
		"GadgetEngine",
	}

-- //-----------------------------------------------------------//
-- //----------------------- Game ------------------------------//
-- //-----------------------------------------------------------//

project "Game"
	CppProjectDefaults()
	GadgetExternalIncludes()
	GadgetExternalLibDirs()
	GadgetExternalLibs { linkLibs="true" }
	DependsOnGadgetEngine()

	dpiawareness "HighPerMonitor"
	debugdir ("%{cfg.targetdir}")
	
	filter "system:windows"
		postbuildcommands
		{
			"echo D|xcopy \"$(SolutionDir)GadgetEngine\\SDK\\_Gadget\\lib\\$(Configuration)\\*.dll\" \"$(TargetDir)\" /y /E /d",
			"echo D|xcopy \"$(SolutionDir)GadgetEngine\\SDK\\_Gadget\\lib\\$(Configuration)\\*.pdb\" \"$(TargetDir)\" /y /E /d",
			"echo D|xcopy \"$(SolutionDir)GadgetEngine\\Resources\\\" \"$(TargetDir)Resources\\\" /y /E /d",
			"echo D|xcopy \"$(SolutionDir)Resources\\\" \"$(TargetDir)Resources\\\" /y /E /d",
		}
		
	filter "configurations:Debug or Develop"
		kind "ConsoleApp"
		IgnoreDefaultLibrariesForDebug()
		
	filter "configurations:Release"
		kind "WindowedApp"
		IgnoreDefaultLibrariesForRelease()