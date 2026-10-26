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
#include "../enums/BuyerSide.hpp"
#include "../enums/SellerSide.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The Combination Trade Executed Message is designed to provide details for executions where
// one or both orders are resting from a different order book id from the order book id of the
// trade
class CombinationTradeExecutedMessage {
  public:
    static constexpr const char* name = "CombinationTradeExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CombinationTradeExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CombinationTradeExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 79;
    static constexpr std::size_t fixed_size = 79;
    std::size_t encoded_size() const { return 79; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    TradeType trade_type() const { return static_cast<TradeType>(wire::read_char(at(10))); }

    std::uint64_t trade_id() const { return wire::read_u64_be(at(11)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_be(at(19)); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(23))), -2); }

    std::uint32_t buyer_tradeable_instrument_id() const { return wire::read_u32_be(at(31)); }

    BuyerSide buyer_side() const { return static_cast<BuyerSide>(wire::read_char(at(35))); }

    std::uint64_t buyer_order_id() const { return wire::read_u64_be(at(36)); }

    std::uint64_t buyer_combination_trade_id() const { return wire::read_u64_be(at(44)); }

    std::string_view buyer_participant_id() const { return view::text(at(52), 3, ' '); }

    std::uint32_t seller_tradeable_instrument_id() const { return wire::read_u32_be(at(55)); }

    SellerSide seller_side() const { return static_cast<SellerSide>(wire::read_char(at(59))); }

    std::uint64_t seller_order_id() const { return wire::read_u64_be(at(60)); }

    std::uint64_t seller_combination_trade_id() const { return wire::read_u64_be(at(68)); }

    std::string_view seller_participant_id() const { return view::text(at(76), 3, ' '); }

    void print(std::ostream& out) const {
        out << "CombinationTradeExecutedMessage{";
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
        out << ", buyer_tradeable_instrument_id=";
        out << buyer_tradeable_instrument_id();
        out << ", buyer_side=";
        out << buyer_side();
        out << ", buyer_order_id=";
        out << buyer_order_id();
        out << ", buyer_combination_trade_id=";
        out << buyer_combination_trade_id();
        out << ", buyer_participant_id=";
        print::text(out, buyer_participant_id());
        out << ", seller_tradeable_instrument_id=";
        out << seller_tradeable_instrument_id();
        out << ", seller_side=";
        out << seller_side();
        out << ", seller_order_id=";
        out << seller_order_id();
        out << ", seller_combination_trade_id=";
        out << seller_combination_trade_id();
        out << ", seller_participant_id=";
        print::text(out, seller_participant_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CombinationTradeExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
