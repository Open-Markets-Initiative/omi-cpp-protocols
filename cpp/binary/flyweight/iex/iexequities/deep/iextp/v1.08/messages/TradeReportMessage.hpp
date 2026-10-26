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
#include "../bitfields/SaleConditionFlags.hpp"
#include "../common/Decimal.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

// Trade Report Messages are sent when an order on the IEX Order Book is executed in whole or
// in part
class TradeReportMessage {
  public:
    static constexpr const char* name = "TradeReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 37;
    static constexpr std::size_t fixed_size = 37;
    std::size_t encoded_size() const { return 37; }

    SaleConditionFlags sale_condition_flags() const { return SaleConditionFlags{ bytes_.subspan(0) }; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    std::uint32_t size() const { return wire::read_u32_le(at(17)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(21))), -4); }

    std::uint64_t trade_id() const { return wire::read_u64_le(at(29)); }

    void print(std::ostream& out) const {
        out << "TradeReportMessage{";
        out << "sale_condition_flags=";
        sale_condition_flags().print(out);
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", size=";
        out << size();
        out << ", price=";
        out << price();
        out << ", trade_id=";
        out << trade_id();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deep::iextp::v1_08
