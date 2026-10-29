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
#include "../enums/QuoteRejectReason.hpp"
#include "../enums/QuoteStatus.hpp"
#include "../enums/QuoteStatusResponseTo.hpp"
#include "../enums/SideOptional.hpp"
#include "../enums/SettlTypeOptional.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ExecuteUnderlyingTrade.hpp"
#include "../structs/QuoteReqId.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// QuoteStatusReportMessage
class QuoteStatusReportMessage {
  public:
    static constexpr const char* name = "QuoteStatusReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteStatusReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteStatusReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 110;
    std::size_t encoded_size() const { return text_end(); }

    BidirectionalBusinessHeader bidirectional_business_header() const { return BidirectionalBusinessHeader{ bytes_.subspan(0) }; }

    std::optional<QuoteRejectReason> quote_reject_reason() const { return wire::nullable_enum<QuoteRejectReason>(wire::read_u32_le(at(19)), static_cast<std::uint32_t>(0ULL)); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(23)); }

    std::uint64_t quote_id() const { return wire::read_u64_le(at(31)); }

    std::optional<std::uint32_t> trade_id_optional() const { return wire::nullable(wire::read_u32_le(at(39)), static_cast<std::uint32_t>(0ULL)); }

    std::uint32_t contra_broker() const { return wire::read_u32_le(at(43)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(47)))); }

    QuoteStatus quote_status() const { return static_cast<QuoteStatus>(wire::read_u8(at(55))); }

    QuoteStatusResponseTo quote_status_response_to() const { return static_cast<QuoteStatusResponseTo>(wire::read_char(at(56))); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(57)), static_cast<std::uint32_t>(0ULL)); }

    SideOptional side_optional() const { return static_cast<SideOptional>(wire::read_char(at(61))); }

    SettlTypeOptional settl_type_optional() const { return static_cast<SettlTypeOptional>(wire::read_char(at(62))); }

    std::optional<Decimal> price_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(63)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    std::uint64_t order_qty() const { return wire::read_u64_le(at(71)); }

    std::string_view sender_location() const { return view::text(at(79), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(89), 5, '\0'); }

    std::string_view executing_trader() const { return view::text(at(94), 5, '\0'); }

    std::optional<Decimal> fixed_rate_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(99)), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4); }

    ExecuteUnderlyingTrade execute_underlying_trade() const { return static_cast<ExecuteUnderlyingTrade>(wire::read_char(at(107))); }

    std::optional<std::uint16_t> days_to_settlement_optional() const { return wire::nullable(wire::read_u16_le(at(108)), static_cast<std::uint16_t>(65535ULL)); }

    QuoteReqId quote_req_id() const { return QuoteReqId{ bytes_.subspan(110) }; }

    DeskId desk_id() const {
        wire::require("QuoteStatusReportMessage", quote_req_id_end() + DeskId::minimum_size, bytes_.size());
        return DeskId{ bytes_.subspan(quote_req_id_end()) };
    }

    Memo memo() const {
        wire::require("QuoteStatusReportMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    Text text() const {
        wire::require("QuoteStatusReportMessage", memo_end() + Text::minimum_size, bytes_.size());
        return Text{ bytes_.subspan(memo_end()) };
    }

    void print(std::ostream& out) const {
        out << "QuoteStatusReportMessage{";
        out << "bidirectional_business_header=";
        bidirectional_business_header().print(out);
        out << ", quote_reject_reason=";
        print::optional(out, quote_reject_reason());
        out << ", security_id=";
        out << security_id();
        out << ", quote_id=";
        out << quote_id();
        out << ", trade_id_optional=";
        print::optional(out, trade_id_optional());
        out << ", contra_broker=";
        out << contra_broker();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", quote_status=";
        out << quote_status();
        out << ", quote_status_response_to=";
        out << quote_status_response_to();
        out << ", account=";
        print::optional(out, account());
        out << ", side_optional=";
        out << side_optional();
        out << ", settl_type_optional=";
        out << settl_type_optional();
        out << ", price_optional=";
        print::optional(out, price_optional());
        out << ", order_qty=";
        out << order_qty();
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", executing_trader=";
        print::text(out, executing_trader());
        out << ", fixed_rate_optional=";
        print::optional(out, fixed_rate_optional());
        out << ", execute_underlying_trade=";
        out << execute_underlying_trade();
        out << ", days_to_settlement_optional=";
        print::optional(out, days_to_settlement_optional());
        out << ", quote_req_id=";
        quote_req_id().print(out);
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
    std::size_t quote_req_id_end() const { return 110 + quote_req_id().encoded_size(); }
    std::size_t desk_id_end() const { return quote_req_id_end() + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }
    std::size_t text_end() const { return memo_end() + text().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteStatusReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
