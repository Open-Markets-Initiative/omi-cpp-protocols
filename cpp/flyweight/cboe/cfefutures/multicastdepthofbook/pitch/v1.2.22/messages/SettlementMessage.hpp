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
#include "../common/Decimal.hpp"
#include "../enums/Issue.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Settlement messages are used to provide information concerning indicative, approved, or
// corrected daily and final settlement prices for CFE products.
class SettlementMessage {
  public:
    static constexpr const char* name = "SettlementMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SettlementMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SettlementMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 23;
    static constexpr std::size_t fixed_size = 23;
    std::size_t encoded_size() const { return 23; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view symbol() const { return view::text(at(4), 6, ' '); }

    std::uint32_t trade_date() const { return wire::read_u32_le(at(10)); }

    Decimal settlement_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(14))), -4); }

    Issue issue() const { return static_cast<Issue>(wire::read_char(at(22))); }

    void print(std::ostream& out) const {
        out << "SettlementMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", trade_date=";
        out << trade_date();
        out << ", settlement_price=";
        out << settlement_price();
        out << ", issue=";
        out << issue();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SettlementMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
