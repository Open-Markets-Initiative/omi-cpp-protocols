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

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// C1 Only. The Constituent Symbol Mapping message is only available on the C1 Exchange. This
// message is used to communicate which options series (if any) are Constituent Series in a
// Volatility Settlement Special Opening Quote (SOQ). The message is identical to the Symbol
// Mapping message with the addition of the SOQ Identifier field, which is set to the CSMi
// symbol on which the final settlement SOQ value is disseminated. The Constituent Symbol
// Mapping message is sent as an unsequenced message with one message sent for each Constituent
// Series in a continuous loop as bandwidth allows.
class ConstituentSymbolMappingMessage {
  public:
    static constexpr const char* name = "ConstituentSymbolMappingMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ConstituentSymbolMappingMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ConstituentSymbolMappingMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    std::string_view feed_symbol() const { return view::text(at(0), 6, ' '); }

    std::string_view osi_symbol() const { return view::text(at(6), 21, ' '); }

    SymbolCondition symbol_condition() const { return static_cast<SymbolCondition>(wire::read_char(at(27))); }

    std::string_view underlying() const { return view::text(at(28), 8, ' '); }

    std::string_view soq_identifier() const { return view::text(at(36), 20, ' '); }

    void print(std::ostream& out) const {
        out << "ConstituentSymbolMappingMessage{";
        out << "feed_symbol=";
        print::text(out, feed_symbol());
        out << ", osi_symbol=";
        print::text(out, osi_symbol());
        out << ", symbol_condition=";
        out << symbol_condition();
        out << ", underlying=";
        print::text(out, underlying());
        out << ", soq_identifier=";
        print::text(out, soq_identifier());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ConstituentSymbolMappingMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
