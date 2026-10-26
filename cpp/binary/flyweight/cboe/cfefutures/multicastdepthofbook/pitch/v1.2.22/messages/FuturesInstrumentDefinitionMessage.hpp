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
#include "../bitfields/FuturesFlags.hpp"
#include "../enums/ListingState.hpp"
#include "../common/Decimal.hpp"
#include "../groups/FutureLeg.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The Futures Instrument Definition message can be sent as a sequenced message or an
// un-sequenced message. It is sent as a sequenced message when the system starts up at the
// beginning of a trading session or an the instrument is created or modified during a trading
// day.
class FuturesInstrumentDefinitionMessage {
  public:
    static constexpr const char* name = "FuturesInstrumentDefinitionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FuturesInstrumentDefinitionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FuturesInstrumentDefinitionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 43;
    std::size_t encoded_size() const { return future_leg_end(); }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view symbol() const { return view::text(at(4), 6, ' '); }

    std::uint32_t unit_timestamp() const { return wire::read_u32_le(at(10)); }

    std::string_view report_symbol() const { return view::text(at(14), 6, ' '); }

    FuturesFlags futures_flags() const { return FuturesFlags{ bytes_.subspan(20) }; }

    std::uint32_t expiration_date() const { return wire::read_u32_le(at(21)); }

    std::uint16_t contract_size() const { return wire::read_u16_le(at(25)); }

    ListingState listing_state() const { return static_cast<ListingState>(wire::read_char(at(27))); }

    Decimal price_increment() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(28))), -4); }

    std::uint8_t leg_count() const { return wire::read_u8(at(36)); }

    std::uint8_t leg_offset() const { return wire::read_u8(at(37)); }

    std::uint8_t reserved_1() const { return wire::read_u8(at(38)); }

    std::uint32_t contract_date() const { return wire::read_u32_le(at(39)); }

    view::entries<FutureLeg> future_leg() const { return view::entries<FutureLeg>{ bytes_.subspan(43), wire::count(leg_count()) }; }

    void print(std::ostream& out) const {
        out << "FuturesInstrumentDefinitionMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", unit_timestamp=";
        out << unit_timestamp();
        out << ", report_symbol=";
        print::text(out, report_symbol());
        out << ", futures_flags=";
        futures_flags().print(out);
        out << ", expiration_date=";
        out << expiration_date();
        out << ", contract_size=";
        out << contract_size();
        out << ", listing_state=";
        out << listing_state();
        out << ", price_increment=";
        out << price_increment();
        out << ", leg_count=";
        out << static_cast<int>(leg_count());
        out << ", leg_offset=";
        out << static_cast<int>(leg_offset());
        out << ", reserved_1=";
        out << static_cast<int>(reserved_1());
        out << ", contract_date=";
        out << contract_date();
        out << ", future_leg=";
        print::sequence(out, future_leg());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t future_leg_end() const { return 43 + future_leg().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FuturesInstrumentDefinitionMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
