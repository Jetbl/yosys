#pragma once
#include <cxxrtl/cxxrtl.h>
#include <cxxrtl/cxxrtl_vcd.h>
#include <cxxrtl/capi/cxxrtl_capi.h>
#include <memory>

using CxxrtlToplevel = _cxxrtl_toplevel;
using CxxrtlObject = cxxrtl_object;
using CxxrtlOutline = _cxxrtl_outline;

class CxxrtlHandle {

public:
  const struct cxxrtl_object *get_parts(std::string name, size_t *parts) const;
  std::unique_ptr<cxxrtl::module> module;
  cxxrtl::debug_items objects;
  CxxrtlHandle(CxxrtlToplevel *top_level, std::string root);
  CxxrtlHandle(std::unique_ptr<cxxrtl::module> module, std::string root);
  void step() const;
  bool eval() const;
  bool commit() const;
};

class CxxrtlOutlineHandle {
  cxxrtl_outline outline;
public:
  CxxrtlOutlineHandle(CxxrtlOutline* outline);
  void eval() const;
};
