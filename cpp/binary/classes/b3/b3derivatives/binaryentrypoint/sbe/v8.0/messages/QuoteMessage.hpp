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
#include "../enums/SettlType.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/QuoteReqId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// QuoteMessage
class QuoteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::QuoteMessage;

    QuoteMessage() = default;
    QuoteMessage(const BidirectionalBusinessHeader& bidirectional_business_header, std::uint64_t security_id, std::uint64_t quote_id, std::chrono::nanoseconds transact_time, std::optional<Decimal> price_optional, std::uint64_t order_qty, Side side, SettlType settl_type, std::optional<std::uint32_t> account, const std::string& sender_location, const std::string& entering_trader, const std::string& executing_trader, Decimal fixed_rate, ExecuteUnderlyingTrade execute_underlying_trade, std::uint16_t days_to_settlement, const QuoteReqId& quote_req_id, const DeskId& desk_id, const Memo& memo);

    // Bidirectional Business Header: BidirectionalBusinessHeader
    const BidirectionalBusinessHeader& bidirectional_business_header() const;
    BidirectionalBusinessHeader& bidirectional_business_header();
    void set_bidirectional_business_header(const BidirectionalBusinessHeader& value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Quote Id: quoteID
    std::uint64_t quote_id() const;
    void set_quote_id(std::uint64_t value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Price Optional: price
    std::optional<Decimal> price_optional() const;
    void set_price_optional(std::optional<Decimal> value);

    // Order Qty: orderQty
    std::uint64_t order_qty() const;
    void set_order_qty(std::uint64_t value);

    // Side: side
    Side side() const;
    void set_side(Side value);

    // Settl Type: settlType
    SettlType settl_type() const;
    void set_settl_type(SettlType value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

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

    // Fixed Rate: fixedRate
    Decimal fixed_rate() const;
    void set_fixed_rate(Decimal value);

    // Execute Underlying Trade: executeUnderlyingTrade
    ExecuteUnderlyingTrade execute_underlying_trade() const;
    void set_execute_underlying_trade(ExecuteUnderlyingTrade value);

    // Days To Settlement: daysToSettlement
    std::uint16_t days_to_settlement() const;
    void set_days_to_settlement(std::uint16_t value);

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

    bool operator==(const QuoteMessage& other) const;
    bool operator!=(const QuoteMessage& other) const;

  private:
    BidirectionalBusinessHeader bidirectional_business_header_{};
    std::uint64_t security_id_{};
    std::uint64_t quote_id_{};
    std::chrono::nanoseconds transact_time_{};
    std::optional<Decimal> price_optional_{};
    std::uint64_t order_qty_{};
    Side side_{};
    SettlType settl_type_{};
    std::optional<std::uint32_t> account_{};
    std::string sender_location_{};
    std::string entering_trader_{};
    std::string executing_trader_{};
    Decimal fixed_rate_{ 0, -4 };
    ExecuteUnderlyingTrade execute_underlying_trade_{};
    std::uint16_t days_to_settlement_{};
    QuoteReqId quote_req_id_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
