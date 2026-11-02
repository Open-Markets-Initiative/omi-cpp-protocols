#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/StypeIn.hpp"
#include "../enums/StypeOut.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// A symbol mapping message, which maps a symbol of one SType to another
class RecordBodySymbolMappingMsg {
  public:
    static constexpr const char* name = "RecordBodySymbolMappingMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodySymbolMappingMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodySymbolMappingMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 160;
    static constexpr std::size_t fixed_size = 160;
    std::size_t encoded_size() const { return 160; }

    std::optional<StypeIn> stype_in() const { return wire::nullable_enum<StypeIn>(wire::read_u8(at(0)), static_cast<std::uint8_t>(255ULL)); }

    std::string_view stype_in_symbol() const { return view::text(at(1), 71, '\0'); }

    StypeOut stype_out() const { return static_cast<StypeOut>(wire::read_u8(at(72))); }

    std::string_view stype_out_symbol() const { return view::text(at(73), 71, '\0'); }

    std::optional<std::chrono::nanoseconds> start_ts() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(144)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::chrono::nanoseconds> end_ts() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(152)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    void print(std::ostream& out) const {
        out << "RecordBodySymbolMappingMsg{";
        out << "stype_in=";
        print::optional(out, stype_in());
        out << ", stype_in_symbol=";
        print::text(out, stype_in_symbol());
        out << ", stype_out=";
        out << stype_out();
        out << ", stype_out_symbol=";
        print::text(out, stype_out_symbol());
        out << ", start_ts=";
        print::optional_duration(out, start_ts());
        out << ", end_ts=";
        print::optional_duration(out, end_ts());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordBodySymbolMappingMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
