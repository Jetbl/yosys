#include "cxxrtl_ccapi.h"
#include <cxxrtl/cxxrtl.h>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

void dump_all_items(cxxrtl::debug_items &items) {
  std::cout << "All items:" << std::endl;
  for (auto &it : items.table)
    for (auto &part : it.second)
      std::cout << std::setw(20) << it.first << ": type = " << part.type
                << ", width = " << std::setw(4) << part.width
                << ", depth = " << std::setw(6) << part.depth
                << ", lsb_at = " << part.lsb_at
                << ", zero_at = " << part.zero_at << std::endl;
  std::cout << std::endl;
}

CxxrtlHandle::CxxrtlHandle(CxxrtlToplevel *design, std::string path) {
  if (!path.empty()) {
    assert(path.back() != ' ');
    path += ' ';
  }

  this->module = std::move(design->module);
  this->module->debug_info(this->objects, path);
  // dump_all_items(this->objects);
}

CxxrtlHandle::CxxrtlHandle(std::unique_ptr<cxxrtl::module> module,
                           std::string path) {
  if (!path.empty()) {
    assert(path.back() != ' ');
    path += ' ';
  }

  this->module = std::move(module);
  this->module->debug_info(this->objects, path);
  dump_all_items(this->objects);
}

void CxxrtlHandle::step() const { this->module->step(); }

const struct cxxrtl_object *CxxrtlHandle::get_parts(std::string name,
                                                    size_t *parts) const {
  auto it = this->objects.table.find(name);
  if (it == this->objects.table.end())
    return nullptr;
  *parts = it->second.size();
  return static_cast<const cxxrtl_object *>(&it->second[0]);
}
