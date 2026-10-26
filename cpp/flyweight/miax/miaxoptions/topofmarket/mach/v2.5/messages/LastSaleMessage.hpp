#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TradeCondition.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// This is the message format that will be used to disseminate Trades that are resulting from
// executions on MIAX during the current trading session.
class LastSaleMessage {
  public:
    static constexpr const char* name = "LastSaleMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LastSaleMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LastSaleMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 27;
    static constexpr std::size_t fixed_size = 27;
    std::size_t encoded_size() const { return 27; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t product_id() const { return wire::read_u32_le(at(4)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(8)); }

    std::uint8_t correction_number() const { return wire::read_u8(at(12)); }

    std::uint32_t reference_trade_id() const { return wire::read_u32_le(at(13)); }

    std::uint8_t reference_correction_number() const { return wire::read_u8(at(17)); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_le(at(18))), -4); }

    std::uint32_t trade_size() const { return wire::read_u32_le(at(22)); }

    TradeCondition trade_condition() const { return static_cast<TradeCondition>(wire::read_char(at(26))); }

    void print(std::ostream& out) const {
        out << "LastSaleMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", product_id=";
        out << product_id();
        out << ", trade_id=";
        out << trade_id();
        out << ", correction_number=";
        out << static_cast<int>(correction_number());
        out << ", reference_trade_id=";
        out << reference_trade_id();
        out << ", reference_correction_number=";
        out << static_cast<int>(reference_correction_number());
        out << ", trade_price=";
        out << trade_price();
        out << ", trade_size=";
        out << trade_size();
        out << ", trade_condition=";
        out << trade_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LastSaleMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
