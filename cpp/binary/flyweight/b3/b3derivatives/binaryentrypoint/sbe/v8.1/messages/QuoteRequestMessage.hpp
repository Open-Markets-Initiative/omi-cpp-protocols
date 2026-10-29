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
#include "../enums/SettlType.hpp"
#include "../enums/ExecuteUnderlyingTrade.hpp"
#include "../structs/SidesGroups.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// QuoteRequestMessage
class QuoteRequestMessage {
  public:
    static constexpr const char* name = "QuoteRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 107;
    std::size_t encoded_size() const { return memo_end(); }

    BidirectionalBusinessHeader bidirectional_business_header() const { return BidirectionalBusinessHeader{ bytes_.subspan(0) }; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(19)); }

    std::uint64_t quote_req_id() const { return wire::read_u64_le(at(27)); }

    std::optional<std::uint64_t> quote_id_optional() const { return wire::nullable(wire::read_u64_le(at(35)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> trade_id_optional() const { return wire::nullable(wire::read_u32_le(at(43)), static_cast<std::uint32_t>(0ULL)); }

    std::uint32_t contra_broker() const { return wire::read_u32_le(at(47)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(51)))); }

    Decimal price_8() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(59))), -8); }

    SettlType settl_type() const { return static_cast<SettlType>(wire::read_char(at(67))); }

    ExecuteUnderlyingTrade execute_underlying_trade() const { return static_cast<ExecuteUnderlyingTrade>(wire::read_char(at(68))); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(69)); }

    std::string_view sender_location() const { return view::text(at(77), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(87), 5, '\0'); }

    std::string_view executing_trader() const { return view::text(at(92), 5, '\0'); }

    Decimal fixed_rate_percentage_8() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(97))), -8); }

    std::uint16_t days_to_settlement() const { return wire::read_u16_le(at(105)); }

    SidesGroups sides_groups() const { return SidesGroups{ bytes_.subspan(107) }; }

    DeskId desk_id() const {
        wire::require("QuoteRequestMessage", sides_groups_end() + DeskId::minimum_size, bytes_.size());
        return DeskId{ bytes_.subspan(sides_groups_end()) };
    }

    Memo memo() const {
        wire::require("QuoteRequestMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "QuoteRequestMessage{";
        out << "bidirectional_business_header=";
        bidirectional_business_header().print(out);
        out << ", security_id=";
        out << security_id();
        out << ", quote_req_id=";
        out << quote_req_id();
        out << ", quote_id_optional=";
        print::optional(out, quote_id_optional());
        out << ", trade_id_optional=";
        print::optional(out, trade_id_optional());
        out << ", contra_broker=";
        out << contra_broker();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", price_8=";
        out << price_8();
        out << ", settl_type=";
        out << settl_type();
        out << ", execute_underlying_trade=";
        out << execute_underlying_trade();
        out << ", order_qty=";
        out << order_qty();
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", executing_trader=";
        print::text(out, executing_trader());
        out << ", fixed_rate_percentage_8=";
        out << fixed_rate_percentage_8();
        out << ", days_to_settlement=";
        out << days_to_settlement();
        out << ", sides_groups=";
        sides_groups().print(out);
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t sides_groups_end() const { return 107 + sides_groups().encoded_size(); }
    std::size_t desk_id_end() const { return sides_groups_end() + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
