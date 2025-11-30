-- premake5.lua
workspace "Parcheesi"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Parcheesi"
   location "build"
   libdirs {"."}

project "ParcheesiJPlayer"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   files { "JPlayer.h", "JPlayer.cc"}

project "ParcheesiJBoard"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   files { "JParcheesi.cc", "JParcheesi.h" }

project "Parcheesi"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   --links {"ParcheesiJPlayer","ParcheesiJBoard", "PlayerJonathan.lib"}
   links {"ParcheesiJPlayer", "ParcheesiJBoard", "PlayerArnau"}
   files { "JParcheesi.cc", "PlayerArnau.h" }

   files
   {
      "game.h",
      "iparcheesi.h",
      "mock_parcheesi.h",
      "game.cc",
      "main.cc"
   }