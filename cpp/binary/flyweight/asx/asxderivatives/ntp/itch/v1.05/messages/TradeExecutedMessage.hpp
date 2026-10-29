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
#include "../enums/TradeType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ParticipantIdBuyer.hpp"
#include "../enums/ParticipantIdSeller.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The Trade Message is designed to provide details for executions in combination order books.
// Trade Executed messages are reported in the same sequence as order execution messages are
// reported
class TradeExecutedMessage {
  public:
    static constexpr const char* name = "TradeExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 45;
    static constexpr std::size_t fixed_size = 45;
    std::size_t encoded_size() const { return 45; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    TradeType trade_type() const { return static_cast<TradeType>(wire::read_char(at(10))); }

    std::uint64_t trade_id() const { return wire::read_u64_be(at(11)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_be(at(19)); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(23))), -2); }

    std::uint64_t combination_trade_id() const { return wire::read_u64_be(at(31)); }

    std::string_view participant_id_buyer() const { return view::text(at(39), 3, ' '); }

    std::string_view participant_id_seller() const { return view::text(at(42), 3, ' '); }

    void print(std::ostream& out) const {
        out << "TradeExecutedMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", trade_type=";
        out << trade_type();
        out << ", trade_id=";
        out << trade_id();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", trade_price=";
        out << trade_price();
        out << ", combination_trade_id=";
        out << combination_trade_id();
        out << ", participant_id_buyer=";
        print::text(out, participant_id_buyer());
        out << ", participant_id_seller=";
        print::text(out, participant_id_seller());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
