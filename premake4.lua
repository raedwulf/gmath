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
	
	project "cephes"
	kind "ConsoleApp"
	language "C"
	files {
		"include/gmath/*.h",
		"include/gmath/internal/*.h",
		"include/cephes/*.h",
		"testing/*.h",
		"testing/cephes.c",
	}

	configuration "linux"
		buildoptions { "-std=c99" }
		links { "m" }

	configuration "Debug"
		defines { "DEBUG", "USE_SSE2" }
		flags { "Symbols" }
		targetdir "bin/debug"
	
	configuration "Release"
		defines { "NDEBUG", "USE_SSE2" }
		flags { "OptimizeSpeed" }
		targetdir "bin/release"
