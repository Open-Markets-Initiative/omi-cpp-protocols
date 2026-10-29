#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketId.hpp"
#include "../groups/LegDefinition.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// The Complex Symbol Definition message provides a description of the legs in a Complex
// symbol, and specifies its Complex symbol ID, which is unique for its stream. If the same
// symbol ID appears in a different stream, it represents a different Complex symbol.
class ComplexSymbolDefinitionMessage {
  public:
    static constexpr const char* name = "ComplexSymbolDefinitionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexSymbolDefinitionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexSymbolDefinitionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    std::size_t encoded_size() const { return leg_definition_end(); }

    std::uint32_t complex_index() const { return wire::read_u32_le(at(0)); }

    std::string_view complex_symbol() const { return view::text(at(4), 21, '\0'); }

    std::uint8_t channel_id() const { return wire::read_u8(at(25)); }

    MarketId market_id() const { return static_cast<MarketId>(wire::read_u16_le(at(26))); }

    std::uint8_t system_id() const { return wire::read_u8(at(28)); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(29).template first<1>(); }

    std::uint16_t stream_id() const { return wire::read_u16_le(at(30)); }

    std::uint16_t no_of_legs() const { return wire::read_u16_le(at(32)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(34).template first<2>(); }

    view::entries<LegDefinition> leg_definition() const { return view::entries<LegDefinition>{ bytes_.subspan(36), wire::count(no_of_legs()) }; }

    void print(std::ostream& out) const {
        out << "ComplexSymbolDefinitionMessage{";
        out << "complex_index=";
        out << complex_index();
        out << ", complex_symbol=";
        print::text(out, complex_symbol());
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << ", market_id=";
        out << market_id();
        out << ", system_id=";
        out << static_cast<int>(system_id());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", stream_id=";
        out << stream_id();
        out << ", no_of_legs=";
        out << no_of_legs();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << ", leg_definition=";
        print::sequence(out, leg_definition());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t leg_definition_end() const { return 36 + leg_definition().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexSymbolDefinitionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
