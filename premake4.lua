solution "gmath"
	configurations { "Debug", "Release" }
	includedirs {
		"include/gmath",
		"testing"
	}
	
	project "vec"
	kind "ConsoleApp"
	language "C"
	files {
		"include/gmath/*.h",
		"testing/*.h",
		"testing/vec.c",
	}
	buildoptions { "-std=c99" }
	
	configuration "linux"
		links { "m" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
		targetdir "bin/debug"
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" }
		targetdir "bin/release"
