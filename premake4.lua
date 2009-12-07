solution "gmath"
	configurations { "Debug", "Release" }
	includedirs {
		"include",
		"testing"
	}
	
	project "vec"
	kind "ConsoleApp"
	language "C"
	files {
		"include/gmath/*.h",
		"include/gmath/internal/*.h",
		"testing/*.h",
		"testing/vec.c",
	}
	
	project "sincos"
	kind "ConsoleApp"
	language "C"
	files {
		"include/gmath/*.h",
		"include/gmath/internal/*.h",
		"testing/*.h",
		"testing/sincos.c",
	}

	configuration "linux"
		buildoptions { "-std=c99" }
		links { "m" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
		targetdir "bin/debug"
	
	configuration "Release"
		defines { "NDEBUG" }
		flags { "OptimizeSpeed" }
		targetdir "bin/release"
