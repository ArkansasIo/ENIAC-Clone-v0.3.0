#include "cpm22/bdos.hpp"
#include "cpm22/bios.hpp"
#include "cpm22/ccp.hpp"
#include "cpm22/memory.hpp"
#include "cpm22/memory_editor.hpp"
#include "eniac_os/machine.hpp"
#include <filesystem>
#include <iostream>
int main(int argc,char**argv){std::filesystem::path root="disk";if(argc>1)root=argv[1];cpm22::Disk disk(root);cpm22::Bdos bdos(disk);cpm22::BiosConsole bios(std::cin,std::cout);cpm22::Memory memory;cpm22::MemoryEditor editor(memory,bdos,bios,disk.root()/"settings"/"memory.ini");eniac_os::Machine machine([&bios](const std::string&m){bios.write(m+"\n");});cpm22::Ccp shell(bdos,bios,machine,memory,editor);return shell.loop();}
