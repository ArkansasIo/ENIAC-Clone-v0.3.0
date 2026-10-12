#include "cpm22/bdos.hpp"
#include "cpm22/disk.hpp"
#include "cpm22/memory.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
int main(){const auto root=std::filesystem::temp_directory_path()/"eniac_cpm22_test_disk";std::error_code ec;std::filesystem::remove_all(root,ec);cpm22::Disk disk(root);cpm22::Bdos bdos(disk);std::string error;int failures=0;auto check=[&](bool ok,const char*m){if(!ok){std::cerr<<"FAIL: "<<m<<'\n';++failures;}};
check(cpm22::Disk::normalize_name("hello.txt").value_or("")=="HELLO.TXT","8.3 normalization");check(!cpm22::Disk::normalize_name("../escape.txt"),"traversal rejected");check(!cpm22::Disk::normalize_name("TOO-LONG-NAME.TXT"),"long name rejected");
check(bdos.write_file("HELLO.TXT","hello world\n",error),"disk write");auto read=bdos.read_file("hello.txt",error);check(read&&*read=="hello world\n","disk read");check(bdos.copy_file("HELLO.TXT","COPY.TXT",error),"copy");check(bdos.rename_file("COPY.TXT","RENAMED.TXT",error),"rename");check(bdos.set_user(3,error),"select user");check(!bdos.read_file("HELLO.TXT",error),"user areas isolated");check(bdos.set_user(0,error),"return user zero");check(bdos.delete_file("HELLO.TXT",error),"delete");check(bdos.set_drive('B',error)&&disk.drive()=='B',"drive switch");
cpm22::Memory m;check(m.write(0x200,0x41),"memory write");check(m.read(0x200).value_or(0)==0x41,"memory read");check(m.fill(0x210,4,0xFF),"memory fill");auto snap=m.snapshot(0x210,4);check(snap&&snap->size()==4&&(*snap)[3]==0xFF,"snapshot");check(m.restore(0x300,std::vector<std::uint8_t>{0x10,0x20,0x30}),"restore");check(m.read(0x302).value_or(0)==0x30,"restored value");check(!m.write(65536,0),"reject out-of-range address");check(!m.fill(65535,2,0),"reject overflowing fill");check(!m.snapshot(65535,2),"reject overflowing snapshot");check(bdos.write_file("MEM.BIN",std::string("\x41\x00\xFF",3),error),"binary file write");auto bin=bdos.read_file("MEM.BIN",error);check(bin&&bin->size()==3&&static_cast<unsigned char>((*bin)[2])==0xFF,"binary roundtrip");
std::filesystem::remove_all(root,ec);if(failures)return 1;std::cout<<"All CP/M-style disk and memory tests passed.\n";return 0;}
