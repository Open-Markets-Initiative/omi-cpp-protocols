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
#include "../enums/ExchangeCode.hpp"
#include "../enums/SecurityType.hpp"
#include "../enums/PriceResolution.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// On system startup, each multicast channel sends all the symbols on its channel. Underlying
// Index Mapping messages are published first, followed by all Series Index Mapping messages,
// and for the Complex feed, Complex Symbol Definitions last of all.
class UnderlyingIndexMappingMessage {
  public:
    static constexpr const char* name = "UnderlyingIndexMappingMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnderlyingIndexMappingMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnderlyingIndexMappingMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::uint32_t underlying_index() const { return wire::read_u32_le(at(0)); }

    std::string_view underlying_symbol() const { return view::text(at(4), 11, '\0'); }

    std::uint8_t channel_id() const { return wire::read_u8(at(15)); }

    MarketId market_id() const { return static_cast<MarketId>(wire::read_u16_le(at(16))); }

    std::uint8_t system_id() const { return wire::read_u8(at(18)); }

    ExchangeCode exchange_code() const { return static_cast<ExchangeCode>(wire::read_char(at(19))); }

    std::uint8_t price_scale_code() const { return wire::read_u8(at(20)); }

    SecurityType security_type() const { return static_cast<SecurityType>(wire::read_char(at(21))); }

    PriceResolution price_resolution() const { return static_cast<PriceResolution>(wire::read_u8(at(22))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(23).template first<1>(); }

    void print(std::ostream& out) const {
        out << "UnderlyingIndexMappingMessage{";
        out << "underlying_index=";
        out << underlying_index();
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", channel_id=";
        out << static_cast<int>(channel_id());
        out << ", market_id=";
        out << market_id();
        out << ", system_id=";
        out << static_cast<int>(system_id());
        out << ", exchange_code=";
        out << exchange_code();
        out << ", price_scale_code=";
        out << static_cast<int>(price_scale_code());
        out << ", security_type=";
        out << security_type();
        out << ", price_resolution=";
        out << price_resolution();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnderlyingIndexMappingMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
