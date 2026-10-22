


target("vermilion")
    add_toolchains("w64devkit")
    set_targetdir("build-$(os)-$(arch)")
    add_includedirs("vendor/include", "include")
    add_linkdirs("vendor/lib")
    add_cflags("-Wall -Wextra -Werror");
    add_files("src/pl/win32/*.c", "src/mm/*.c", "src/rtl/*.c", "src/*.c")








toolchain("w64devkit")
    set_kind("standalone")
    set_toolset("cc", "gcc")
    set_toolset("ld", "gcc")
toolchain_end()
