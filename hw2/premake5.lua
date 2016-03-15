-- premake5.lua
workspace "hw2"
  filename "hw2"
  configurations { "Debug", "Release" }

  project "main"
    kind "ConsoleApp"
    language "C++"

    files { "src/**.h", "src/**.cpp" }

    configuration { "windows" }
      links { "freeglut", "glu32", "opengl32" }
      libdirs { "lib" }
      includedirs { "include" }
      targetname "main.exe"
      targetdir "."

    configuration { "macosx" }
      linkoptions { "-framework OpenGL", "-framework GLUT" }
      targetname "main"
      targetdir "."

    configuration { "linux" }
      links { "X11", "GL", "GLU", "GLUT" }
      targetname "main"
      targetdir "."
