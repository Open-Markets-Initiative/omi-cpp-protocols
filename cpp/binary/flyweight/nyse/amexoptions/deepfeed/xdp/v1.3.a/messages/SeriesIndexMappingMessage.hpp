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
#include "../enums/PutOrCall.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// On system startup, each multicast channel sends all the symbols on its channel. Underlying
// Index Mapping messages are published first, followed by all Series Index Mapping messages,
// and for the Complex feed, Complex Symbol Definitions last of all.
class SeriesIndexMappingMessage {
  public:
    static constexpr const char* name = "SeriesIndexMappingMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SeriesIndexMappingMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SeriesIndexMappingMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    std::uint32_t series_index() const { return wire::read_u32_le(at(0)); }

    std::uint8_t channel_id() const { return wire::read_u8(at(4)); }

    std::span<const std::byte, 1> reserved_a_1() const { return bytes_.subspan(5).template first<1>(); }

    MarketId market_id() const { return static_cast<MarketId>(wire::read_u16_le(at(6))); }

    std::uint8_t system_id() const { return wire::read_u8(at(8)); }

    std::span<const std::byte, 1> reserved_b_1() const { return bytes_.subspan(9).template first<1>(); }

    std::uint16_t stream_id() const { return wire::read_u16_le(at(10)); }

    std::uint32_t underlying_index() const { return wire::read_u32_le(at(12)); }

    std::uint16_t contract_multiplier() const { return wire::read_u16_le(at(16)); }

    std::string_view maturity_date() const { return view::text(at(18), 6, '\0'); }

    PutOrCall put_or_call() const { return static_cast<PutOrCall>(wire::read_u8(at(24))); }

    std::string_view strike_price() const { return view::text(at(25), 10, '\0'); }

    std::uint8_t price_scale_code() const { return wire::read_u8(at(35)); }

    std::string_view underlying_symbol() const { return view::text(at(36), 11, '\0'); }

    std::string_view option_symbol_root() const { return view::text(at(47), 5, '\0'); }

    std::uint32_t group_id() const { return wire::read_u32_le(at(52)); }

    void print(std::ostream& out) const {
        out << "SeriesIndexMappingMessage{";
        out << "series_index=";
        out << series_index();
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << ", reserved_a_1=";
        print::hex(out, reserved_a_1().data(), reserved_a_1().size());
        out << ", market_id=";
        out << market_id();
        out << ", system_id=";
        out << static_cast<int>(system_id());
        out << ", reserved_b_1=";
        print::hex(out, reserved_b_1().data(), reserved_b_1().size());
        out << ", stream_id=";
        out << stream_id();
        out << ", underlying_index=";
        out << underlying_index();
        out << ", contract_multiplier=";
        out << contract_multiplier();
        out << ", maturity_date=";
        print::text(out, maturity_date());
        out << ", put_or_call=";
        out << put_or_call();
        out << ", strike_price=";
        print::text(out, strike_price());
        out << ", price_scale_code=";
        out << static_cast<int>(price_scale_code());
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", option_symbol_root=";
        print::text(out, option_symbol_root());
        out << ", group_id=";
        out << group_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SeriesIndexMappingMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
