#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ExecuteUnderlyingTrade.hpp"
#include "../enums/QuoteRejectReason.hpp"
#include "../enums/QuoteStatus.hpp"
#include "../enums/QuoteStatusResponseTo.hpp"
#include "../enums/SettlTypeOptional.hpp"
#include "../enums/SideOptional.hpp"
#include "../messages/Message.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/QuoteReqId.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// QuoteStatusReportMessage
class QuoteStatusReportMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::QuoteStatusReportMessage;

    QuoteStatusReportMessage() = default;
    QuoteStatusReportMessage(const BidirectionalBusinessHeader& bidirectional_business_header, std::optional<QuoteRejectReason> quote_reject_reason, std::uint64_t security_id, std::uint64_t quote_id, std::optional<std::uint32_t> trade_id_optional, std::uint32_t contra_broker, std::chrono::nanoseconds transact_time, QuoteStatus quote_status, QuoteStatusResponseTo quote_status_response_to, std::optional<std::uint32_t> account, SideOptional side_optional, SettlTypeOptional settl_type_optional, std::optional<Decimal> price_optional, std::uint64_t order_qty, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader, std::optional<Decimal> fixed_rate_optional, ExecuteUnderlyingTrade execute_underlying_trade, std::optional<std::uint16_t> days_to_settlement_optional, const QuoteReqId& quote_req_id, const DeskId& desk_id, const Memo& memo, const Text& text);

    // Bidirectional Business Header: BidirectionalBusinessHeader
    const BidirectionalBusinessHeader& bidirectional_business_header() const;
    BidirectionalBusinessHeader& bidirectional_business_header();
    void set_bidirectional_business_header(const BidirectionalBusinessHeader& value);

    // Quote Reject Reason: quoteRejectReason
    std::optional<QuoteRejectReason> quote_reject_reason() const;
    void set_quote_reject_reason(std::optional<QuoteRejectReason> value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Quote Id: quoteID
    std::uint64_t quote_id() const;
    void set_quote_id(std::uint64_t value);

    // Trade Id Optional: tradeID
    std::optional<std::uint32_t> trade_id_optional() const;
    void set_trade_id_optional(std::optional<std::uint32_t> value);

    // Contra Broker: contraBroker
    std::uint32_t contra_broker() const;
    void set_contra_broker(std::uint32_t value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Quote Status: quoteStatus
    QuoteStatus quote_status() const;
    void set_quote_status(QuoteStatus value);

    // Quote Status Response To: quoteStatusResponseTo
    QuoteStatusResponseTo quote_status_response_to() const;
    void set_quote_status_response_to(QuoteStatusResponseTo value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Side Optional: side
    SideOptional side_optional() const;
    void set_side_optional(SideOptional value);

    // Settl Type Optional: settlType
    SettlTypeOptional settl_type_optional() const;
    void set_settl_type_optional(SettlTypeOptional value);

    // Price Optional: price
    std::optional<Decimal> price_optional() const;
    void set_price_optional(std::optional<Decimal> value);

    // Order Qty: orderQty
    std::uint64_t order_qty() const;
    void set_order_qty(std::uint64_t value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

    // Executing Trader: executingTrader
    const std::string& executing_trader() const;
    std::string& executing_trader();
    void set_executing_trader(const std::string& value);

    // Fixed Rate Optional: fixedRate
    std::optional<Decimal> fixed_rate_optional() const;
    void set_fixed_rate_optional(std::optional<Decimal> value);

    // Execute Underlying Trade: executeUnderlyingTrade
    ExecuteUnderlyingTrade execute_underlying_trade() const;
    void set_execute_underlying_trade(ExecuteUnderlyingTrade value);

    // Days To Settlement Optional: daysToSettlement
    std::optional<std::uint16_t> days_to_settlement_optional() const;
    void set_days_to_settlement_optional(std::optional<std::uint16_t> value);

    // Quote Req Id: quoteReqID data struct
    const QuoteReqId& quote_req_id() const;
    QuoteReqId& quote_req_id();
    void set_quote_req_id(const QuoteReqId& value);

    // Desk Id: deskID data struct
    const DeskId& desk_id() const;
    DeskId& desk_id();
    void set_desk_id(const DeskId& value);

    // Memo: memo data struct
    const Memo& memo() const;
    Memo& memo();
    void set_memo(const Memo& value);

    // Text: text data struct
    const Text& text() const;
    Text& text();
    void set_text(const Text& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const QuoteStatusReportMessage& other) const;
    bool operator!=(const QuoteStatusReportMessage& other) const;

  private:
    BidirectionalBusinessHeader bidirectional_business_header_{};
    std::optional<QuoteRejectReason> quote_reject_reason_{};
    std::uint64_t security_id_{};
    std::uint64_t quote_id_{};
    std::optional<std::uint32_t> trade_id_optional_{};
    std::uint32_t contra_broker_{};
    std::chrono::nanoseconds transact_time_{};
    QuoteStatus quote_status_{};
    QuoteStatusResponseTo quote_status_response_to_{};
    std::optional<std::uint32_t> account_{};
    SideOptional side_optional_{};
    SettlTypeOptional settl_type_optional_{};
    std::optional<Decimal> price_optional_{};
    std::uint64_t order_qty_{};
    std::string sender_location_{};
    std::string entering_trader_{};
    std::string executing_trader_{};
    std::optional<Decimal> fixed_rate_optional_{};
    ExecuteUnderlyingTrade execute_underlying_trade_{};
    std::optional<std::uint16_t> days_to_settlement_optional_{};
    QuoteReqId quote_req_id_{};
    DeskId desk_id_{};
    Memo memo_{};
    Text text_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
