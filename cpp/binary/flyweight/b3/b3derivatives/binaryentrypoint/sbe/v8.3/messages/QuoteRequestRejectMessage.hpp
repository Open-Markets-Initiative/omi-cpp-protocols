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
#include "../enums/SettlTypeOptional.hpp"
#include "../common/Decimal.hpp"
#include "../structs/SidesGroups.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// QuoteRequestRejectMessage
class QuoteRequestRejectMessage {
  public:
    static constexpr const char* name = "QuoteRequestRejectMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteRequestRejectMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteRequestRejectMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 110;
    std::size_t encoded_size() const { return text_end(); }

    BidirectionalBusinessHeader bidirectional_business_header() const { return BidirectionalBusinessHeader{ bytes_.subspan(0) }; }

    std::optional<std::uint32_t> quote_request_reject_reason() const { return wire::nullable(wire::read_u32_le(at(19)), static_cast<std::uint32_t>(0ULL)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(23)); }

    std::uint64_t quote_req_id() const { return wire::read_u64_le(at(31)); }

    std::optional<std::uint64_t> quote_id_optional() const { return wire::nullable(wire::read_u64_le(at(39)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> trade_id_optional() const { return wire::nullable(wire::read_u32_le(at(47)), static_cast<std::uint32_t>(0ULL)); }

    std::uint32_t contra_broker() const { return wire::read_u32_le(at(51)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(55)))); }

    std::string_view entering_trader() const { return view::text(at(63), 5, '\0'); }

    SettlTypeOptional settl_type_optional() const { return static_cast<SettlTypeOptional>(wire::read_char(at(68))); }

    std::optional<Decimal> price_8_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(69)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::optional<std::uint64_t> order_qty_optional() const { return wire::nullable(wire::read_u64_le(at(77)), static_cast<std::uint64_t>(0ULL)); }

    std::string_view sender_location() const { return view::text(at(85), 10, '\0'); }

    std::string_view executing_trader() const { return view::text(at(95), 5, '\0'); }

    std::optional<Decimal> fixed_rate_percentage_8_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(100)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8); }

    std::optional<std::uint16_t> days_to_settlement_optional() const { return wire::nullable(wire::read_u16_le(at(108)), static_cast<std::uint16_t>(65535ULL)); }

    SidesGroups sides_groups() const { return SidesGroups{ bytes_.subspan(110) }; }

    DeskId desk_id() const {
        wire::require("QuoteRequestRejectMessage", sides_groups_end() + DeskId::minimum_size, bytes_.size());
        return DeskId{ bytes_.subspan(sides_groups_end()) };
    }

    Memo memo() const {
        wire::require("QuoteRequestRejectMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    Text text() const {
        wire::require("QuoteRequestRejectMessage", memo_end() + Text::minimum_size, bytes_.size());
        return Text{ bytes_.subspan(memo_end()) };
    }

    void print(std::ostream& out) const {
        out << "QuoteRequestRejectMessage{";
        out << "bidirectional_business_header=";
        bidirectional_business_header().print(out);
        out << ", quote_request_reject_reason=";
        print::optional(out, quote_request_reject_reason());
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
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", settl_type_optional=";
        out << settl_type_optional();
        out << ", price_8_optional=";
        print::optional(out, price_8_optional());
        out << ", order_qty_optional=";
        print::optional(out, order_qty_optional());
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", executing_trader=";
        print::text(out, executing_trader());
        out << ", fixed_rate_percentage_8_optional=";
        print::optional(out, fixed_rate_percentage_8_optional());
        out << ", days_to_settlement_optional=";
        print::optional(out, days_to_settlement_optional());
        out << ", sides_groups=";
        sides_groups().print(out);
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << ", text=";
        text().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t sides_groups_end() const { return 110 + sides_groups().encoded_size(); }
    std::size_t desk_id_end() const { return sides_groups_end() + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }
    std::size_t text_end() const { return memo_end() + text().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteRequestRejectMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
