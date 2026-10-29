#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SymbolCondition.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// A Symbol Mapping message is used to map the 6 character multicast feed symbol field to an
// OSI symbol and Underlying.
class SymbolMappingMessage {
  public:
    static constexpr const char* name = "SymbolMappingMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolMappingMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SymbolMappingMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::string_view feed_symbol() const { return view::text(at(0), 6, ' '); }

    std::string_view osi_symbol() const { return view::text(at(6), 21, ' '); }

    SymbolCondition symbol_condition() const { return static_cast<SymbolCondition>(wire::read_char(at(27))); }

    std::string_view underlying() const { return view::text(at(28), 8, ' '); }

    void print(std::ostream& out) const {
        out << "SymbolMappingMessage{";
        out << "feed_symbol=";
        print::text(out, feed_symbol());
        out << ", osi_symbol=";
        print::text(out, osi_symbol());
        out << ", symbol_condition=";
        out << symbol_condition();
        out << ", underlying=";
        print::text(out, underlying());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolMappingMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
