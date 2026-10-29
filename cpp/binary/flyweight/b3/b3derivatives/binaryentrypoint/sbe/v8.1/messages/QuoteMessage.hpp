#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../enums/SettlType.hpp"
#include "../enums/ExecuteUnderlyingTrade.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// QuoteMessage
class QuoteMessage {
  public:
    static constexpr const char* name = "QuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 104;
    std::size_t encoded_size() const { return memo_end(); }

    BidirectionalBusinessHeader bidirectional_business_header() const { return BidirectionalBusinessHeader{ bytes_.subspan(0) }; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(19)); }

    std::uint64_t quote_req_id() const { return wire::read_u64_le(at(27)); }

    std::uint64_t quote_id() const { return wire::read_u64_le(at(35)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(43)))); }

    std::optional<Decimal> price_8_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(51)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(59)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(67))); }

    SettlType settl_type() const { return static_cast<SettlType>(wire::read_char(at(68))); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(69)), static_cast<std::uint32_t>(0ULL)); }

    std::string_view sender_location() const { return view::text(at(73), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(83), 5, '\0'); }

    std::string_view executing_trader() const { return view::text(at(88), 5, '\0'); }

    Decimal fixed_rate_percentage_8() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(93))), -8); }

    ExecuteUnderlyingTrade execute_underlying_trade() const { return static_cast<ExecuteUnderlyingTrade>(wire::read_char(at(101))); }

    std::uint16_t days_to_settlement() const { return wire::read_u16_le(at(102)); }

    DeskId desk_id() const { return DeskId{ bytes_.subspan(104) }; }

    Memo memo() const {
        wire::require("QuoteMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "QuoteMessage{";
        out << "bidirectional_business_header=";
        bidirectional_business_header().print(out);
        out << ", security_id=";
        out << security_id();
        out << ", quote_req_id=";
        out << quote_req_id();
        out << ", quote_id=";
        out << quote_id();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", price_8_optional=";
        print::optional(out, price_8_optional());
        out << ", order_qty=";
        out << order_qty();
        out << ", side=";
        out << side();
        out << ", settl_type=";
        out << settl_type();
        out << ", account=";
        print::optional(out, account());
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", executing_trader=";
        print::text(out, executing_trader());
        out << ", fixed_rate_percentage_8=";
        out << fixed_rate_percentage_8();
        out << ", execute_underlying_trade=";
        out << execute_underlying_trade();
        out << ", days_to_settlement=";
        out << days_to_settlement();
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t desk_id_end() const { return 104 + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
