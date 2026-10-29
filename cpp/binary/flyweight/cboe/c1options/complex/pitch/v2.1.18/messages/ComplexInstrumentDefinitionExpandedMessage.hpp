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
#include "../groups/ComplexInstrumentLeg.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

// A Complex Instrument Definition Expanded message represents a complex instrument that is
// available to place orders.
class ComplexInstrumentDefinitionExpandedMessage {
  public:
    static constexpr const char* name = "ComplexInstrumentDefinitionExpandedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexInstrumentDefinitionExpandedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexInstrumentDefinitionExpandedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 23;
    std::size_t encoded_size() const { return complex_instrument_leg_end(); }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view complex_instrument_id() const { return view::text(at(4), 6, ' '); }

    std::string_view complex_instrument_underlying() const { return view::text(at(10), 8, ' '); }

    std::string_view complex_instrument_type() const { return view::text(at(18), 4, ' '); }

    std::uint8_t leg_count() const { return wire::read_u8(at(22)); }

    view::entries<ComplexInstrumentLeg> complex_instrument_leg() const { return view::entries<ComplexInstrumentLeg>{ bytes_.subspan(23), wire::count(leg_count()) }; }

    void print(std::ostream& out) const {
        out << "ComplexInstrumentDefinitionExpandedMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", complex_instrument_id=";
        print::text(out, complex_instrument_id());
        out << ", complex_instrument_underlying=";
        print::text(out, complex_instrument_underlying());
        out << ", complex_instrument_type=";
        print::text(out, complex_instrument_type());
        out << ", leg_count=";
        out << static_cast<int>(leg_count());
        out << ", complex_instrument_leg=";
        print::sequence(out, complex_instrument_leg());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t complex_instrument_leg_end() const { return 23 + complex_instrument_leg().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexInstrumentDefinitionExpandedMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
