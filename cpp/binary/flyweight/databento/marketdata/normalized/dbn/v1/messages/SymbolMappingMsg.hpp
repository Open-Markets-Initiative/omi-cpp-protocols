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

namespace databento::marketdata::normalized::dbn::v1 {

// A symbol mapping message, which maps a symbol of one SType to another
class SymbolMappingMsg {
  public:
    static constexpr const char* name = "SymbolMappingMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolMappingMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolMappingMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::string_view stype_in_symbol() const { return view::text(at(0), 22, '\0'); }

    std::string_view stype_out_symbol() const { return view::text(at(22), 22, '\0'); }

    std::span<const std::byte, 4> dummy_4() const { return bytes_.subspan(44).template first<4>(); }

    std::optional<std::chrono::nanoseconds> start_ts() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(48)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::chrono::nanoseconds> end_ts() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(56)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    void print(std::ostream& out) const {
        out << "SymbolMappingMsg{";
        out << "stype_in_symbol=";
        print::text(out, stype_in_symbol());
        out << ", stype_out_symbol=";
        print::text(out, stype_out_symbol());
        out << ", dummy_4=";
        print::hex(out, dummy_4().data(), dummy_4().size());
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

inline std::ostream& operator<<(std::ostream& out, const SymbolMappingMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
