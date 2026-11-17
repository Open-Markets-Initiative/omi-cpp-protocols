// Databento.MarketData.Normalized.Dbn.v3: groups/MappingInterval.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// The resolution of a symbol for a date range
class MappingInterval {
  public:
    static constexpr const char* name = "MappingInterval";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MappingInterval(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MappingInterval has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 79;
    static constexpr std::size_t fixed_size = 79;
    std::size_t encoded_size() const { return 79; }

    std::uint32_t start_date() const { return wire::read_u32_le(at(0)); }

    std::uint32_t end_date() const { return wire::read_u32_le(at(4)); }

    std::string_view mapped_symbol() const { return view::text(at(8), 71, '\0'); }

    void print(std::ostream& out) const {
        out << "MappingInterval{";
        out << "start_date=";
        out << start_date();
        out << ", end_date=";
        out << end_date();
        out << ", mapped_symbol=";
        print::text(out, mapped_symbol());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MappingInterval& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
