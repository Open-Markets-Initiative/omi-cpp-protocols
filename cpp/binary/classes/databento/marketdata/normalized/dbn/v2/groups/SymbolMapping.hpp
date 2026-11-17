// Databento.MarketData.Normalized.Dbn.v2: groups/SymbolMapping.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

#include "../groups/MappingInterval.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// The mappings of one raw symbol
class SymbolMapping {
  public:

    SymbolMapping() = default;
    SymbolMapping(const std::string& raw_symbol_in, std::uint32_t interval_count, const std::vector<MappingInterval>& mapping_interval);

    // Raw Symbol In: The symbol assigned by publisher
    const std::string& raw_symbol_in() const;
    std::string& raw_symbol_in();
    void set_raw_symbol_in(const std::string& value);

    // Interval Count: The number of mapping intervals of the symbol
    std::uint32_t interval_count() const;
    void set_interval_count(std::uint32_t value);

    // Mapping Interval: The resolution of a symbol for a date range
    const std::vector<MappingInterval>& mapping_interval() const;
    std::vector<MappingInterval>& mapping_interval();
    void set_mapping_interval(const std::vector<MappingInterval>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SymbolMapping& other) const;
    bool operator!=(const SymbolMapping& other) const;

  private:
    std::string raw_symbol_in_{};
    std::uint32_t interval_count_{};
    std::vector<MappingInterval> mapping_interval_{};
};

std::ostream& operator<<(std::ostream& out, const SymbolMapping& value);

} // namespace databento::marketdata::normalized::dbn::v2
