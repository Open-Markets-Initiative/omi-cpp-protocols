// Databento.MarketData.Normalized.Dbn.v2: groups/SymbolMapping.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../groups/MappingInterval.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// The mappings of one raw symbol
class SymbolMapping {
  public:
    static constexpr const char* name = "SymbolMapping";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolMapping(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolMapping has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 75;
    std::size_t encoded_size() const { return mapping_interval_end(); }

    std::string_view raw_symbol_in() const { return view::text(at(0), 71, '\0'); }

    std::uint32_t interval_count() const { return wire::read_u32_le(at(71)); }

    view::entries<MappingInterval> mapping_interval() const { return view::entries<MappingInterval>{ bytes_.subspan(75), wire::count(interval_count()) }; }

    void print(std::ostream& out) const {
        out << "SymbolMapping{";
        out << "raw_symbol_in=";
        print::text(out, raw_symbol_in());
        out << ", interval_count=";
        out << interval_count();
        out << ", mapping_interval=";
        print::sequence(out, mapping_interval());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t mapping_interval_end() const { return 75 + mapping_interval().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolMapping& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
