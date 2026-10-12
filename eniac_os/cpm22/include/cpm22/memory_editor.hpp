#pragma once
#include "cpm22/bios.hpp"
#include "cpm22/bdos.hpp"
#include "cpm22/memory.hpp"
#include <filesystem>
#include <string>
namespace cpm22 {
struct MemoryViewOptions { std::size_t bytes_per_row{16}; bool show_ascii{true}; bool color{false}; bool show_header{true}; std::string color_name{"GREEN"}; };
class MemoryEditor {
public:
 MemoryEditor(Memory&,Bdos&,BiosConsole&,std::filesystem::path);
 void display(std::size_t address=0,std::size_t rows=16);
 void options();
 int edit(std::size_t address=0);
 bool export_csv(std::string filename,std::size_t address,std::size_t count,std::string& error);
 bool import_csv(std::string filename,std::string& error);
private:
 void load_options(); bool save_options(std::string& error) const;
 std::string prefix() const; std::string reset() const;
 Memory& memory_; Bdos& bdos_; BiosConsole& bios_; std::filesystem::path settings_path_; MemoryViewOptions options_;
};
}
