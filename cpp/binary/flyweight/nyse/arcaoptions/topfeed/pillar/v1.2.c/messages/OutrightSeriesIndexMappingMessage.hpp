#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SeriesType.hpp"
#include "../enums/MarketId.hpp"
#include "../enums/PriceScaleCode.hpp"
#include "../enums/PutOrCall.hpp"
#include "../enums/ClosingOnlyIndicator.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// This message is published over the real-time data channels at system startup or in the
// context of a refresh sequence after a Matching Engine or PILLAR Publisher failover.
class OutrightSeriesIndexMappingMessage {
  public:
    static constexpr const char* name = "OutrightSeriesIndexMappingMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OutrightSeriesIndexMappingMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OutrightSeriesIndexMappingMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 51;
    static constexpr std::size_t fixed_size = 51;
    std::size_t encoded_size() const { return 51; }

    std::uint32_t series_index() const { return wire::read_u32_le(at(0)); }

    SeriesType series_type() const { return static_cast<SeriesType>(wire::read_u8(at(4))); }

    MarketId market_id() const { return static_cast<MarketId>(wire::read_u16_le(at(5))); }

    std::uint8_t system_id() const { return wire::read_u8(at(7)); }

    std::string_view option_symbol_root() const { return view::text(at(8), 6, '\0'); }

    std::string_view underlying_symbol() const { return view::text(at(14), 11, '\0'); }

    std::uint32_t underlying_index() const { return wire::read_u32_le(at(25)); }

    PriceScaleCode price_scale_code() const { return static_cast<PriceScaleCode>(wire::read_u8(at(29))); }

    std::uint16_t contract_multiplier() const { return wire::read_u16_le(at(30)); }

    std::string_view maturity_date() const { return view::text(at(32), 6, '\0'); }

    PutOrCall put_or_call() const { return static_cast<PutOrCall>(wire::read_u8(at(38))); }

    std::string_view strike_price() const { return view::text(at(39), 10, '\0'); }

    ClosingOnlyIndicator closing_only_indicator() const { return static_cast<ClosingOnlyIndicator>(wire::read_char(at(49))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(50).template first<1>(); }

    void print(std::ostream& out) const {
        out << "OutrightSeriesIndexMappingMessage{";
        out << "series_index=";
        out << series_index();
        out << ", series_type=";
        out << series_type();
        out << ", market_id=";
        out << market_id();
        out << ", system_id=";
        out << static_cast<int>(system_id());
        out << ", option_symbol_root=";
        print::text(out, option_symbol_root());
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", underlying_index=";
        out << underlying_index();
        out << ", price_scale_code=";
        out << price_scale_code();
        out << ", contract_multiplier=";
        out << contract_multiplier();
        out << ", maturity_date=";
        print::text(out, maturity_date());
        out << ", put_or_call=";
        out << put_or_call();
        out << ", strike_price=";
        print::text(out, strike_price());
        out << ", closing_only_indicator=";
        out << closing_only_indicator();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OutrightSeriesIndexMappingMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
