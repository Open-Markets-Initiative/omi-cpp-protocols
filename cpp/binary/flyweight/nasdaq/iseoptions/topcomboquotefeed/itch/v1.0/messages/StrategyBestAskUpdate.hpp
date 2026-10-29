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

// The options system will continuously calculate its best offer position for active strategies
// on the options market during the trading day. Whenever the best ask position changes on one
// side but not the other side, the options system will send its best ask update via this feed
// for the affected security
class StrategyBestAskUpdate {
  public:
    static constexpr const char* name = "StrategyBestAskUpdate";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StrategyBestAskUpdate(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StrategyBestAskUpdate has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t strategy_id() const { return wire::read_u32_be(at(6)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(10))); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(11))), -4); }

    std::uint32_t size() const { return wire::read_u32_be(at(15)); }

    std::uint32_t cust_size() const { return wire::read_u32_be(at(19)); }

    std::uint32_t pro_cust_size() const { return wire::read_u32_be(at(23)); }

    std::uint32_t ntt_size() const { return wire::read_u32_be(at(27)); }

    std::uint32_t market_size() const { return wire::read_u32_be(at(31)); }

    std::uint32_t ntt_market_size() const { return wire::read_u32_be(at(35)); }

    void print(std::ostream& out) const {
        out << "StrategyBestAskUpdate{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", strategy_id=";
        out << strategy_id();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", price=";
        out << price();
        out << ", size=";
        out << size();
        out << ", cust_size=";
        out << cust_size();
        out << ", pro_cust_size=";
        out << pro_cust_size();
        out << ", ntt_size=";
        out << ntt_size();
        out << ", market_size=";
        out << market_size();
        out << ", ntt_market_size=";
        out << ntt_market_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StrategyBestAskUpdate& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
