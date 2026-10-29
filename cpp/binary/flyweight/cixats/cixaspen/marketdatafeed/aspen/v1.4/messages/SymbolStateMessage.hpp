#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/State.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Individual symbol trading state (halts)
class SymbolStateMessage {
  public:
    static constexpr const char* name = "SymbolStateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolStateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolStateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 27;
    static constexpr std::size_t fixed_size = 27;
    std::size_t encoded_size() const { return 27; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint16_t symbol_id() const { return wire::read_u16_le(at(8)); }

    std::string_view symbol() const { return view::text(at(10), 11, ' '); }

    State state() const { return static_cast<State>(wire::read_char(at(21))); }

    char reserved_1() const { return wire::read_char(at(22)); }

    std::string_view info() const { return view::text(at(23), 4, ' '); }

    void print(std::ostream& out) const {
        out << "SymbolStateMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", state=";
        out << state();
        out << ", reserved_1=";
        print::character(out, reserved_1());
        out << ", info=";
        print::text(out, info());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolStateMessage& value) {
    value.print(out);
    return out;
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
