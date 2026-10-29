#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/QuoteCondition.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// The options system uses this administrative message to indicate when an strategy has
// completed the opening process and is now available for auto execution or when the option has
// closed and is no longer available for auto execution.
class StrategyBestBidAndAskUpdate {
  public:
    static constexpr const char* name = "StrategyBestBidAndAskUpdate";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StrategyBestBidAndAskUpdate(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StrategyBestBidAndAskUpdate has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 67;
    static constexpr std::size_t fixed_size = 67;
    std::size_t encoded_size() const { return 67; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t strategy_id() const { return wire::read_u32_be(at(6)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(10))); }

    Decimal bid_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(11))), -4); }

    std::uint32_t bid_size() const { return wire::read_u32_be(at(15)); }

    std::uint32_t bid_cust_size() const { return wire::read_u32_be(at(19)); }

    std::uint32_t bid_pro_cust_size() const { return wire::read_u32_be(at(23)); }

    std::uint32_t bid_ntt_size() const { return wire::read_u32_be(at(27)); }

    std::uint32_t bid_market_size() const { return wire::read_u32_be(at(31)); }

    std::uint32_t bid_ntt_market_size() const { return wire::read_u32_be(at(35)); }

    Decimal ask_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(39))), -4); }

    std::uint32_t ask_size() const { return wire::read_u32_be(at(43)); }

    std::uint32_t ask_cust_size() const { return wire::read_u32_be(at(47)); }

    std::uint32_t ask_pro_cust_size() const { return wire::read_u32_be(at(51)); }

    std::uint32_t ask_ntt_size() const { return wire::read_u32_be(at(55)); }

    std::uint32_t ask_market_size() const { return wire::read_u32_be(at(59)); }

    std::uint32_t ask_ntt_market_size() const { return wire::read_u32_be(at(63)); }

    void print(std::ostream& out) const {
        out << "StrategyBestBidAndAskUpdate{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", strategy_id=";
        out << strategy_id();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", bid_price=";
        out << bid_price();
        out << ", bid_size=";
        out << bid_size();
        out << ", bid_cust_size=";
        out << bid_cust_size();
        out << ", bid_pro_cust_size=";
        out << bid_pro_cust_size();
        out << ", bid_ntt_size=";
        out << bid_ntt_size();
        out << ", bid_market_size=";
        out << bid_market_size();
        out << ", bid_ntt_market_size=";
        out << bid_ntt_market_size();
        out << ", ask_price=";
        out << ask_price();
        out << ", ask_size=";
        out << ask_size();
        out << ", ask_cust_size=";
        out << ask_cust_size();
        out << ", ask_pro_cust_size=";
        out << ask_pro_cust_size();
        out << ", ask_ntt_size=";
        out << ask_ntt_size();
        out << ", ask_market_size=";
        out << ask_market_size();
        out << ", ask_ntt_market_size=";
        out << ask_ntt_market_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StrategyBestBidAndAskUpdate& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
