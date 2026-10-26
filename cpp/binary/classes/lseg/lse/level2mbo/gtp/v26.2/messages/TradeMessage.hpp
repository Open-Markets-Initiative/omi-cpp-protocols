#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/TradeFlags.hpp"
#include "../common/Decimal.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/HiddenExecutionIndicator.hpp"
#include "../enums/SourceVenue.hpp"
#include "../enums/TradeQualifier.hpp"
#include "../enums/TradeType.hpp"
#include "../messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class Visitor;

// Sent to indicate trades executed on supported markets.
class TradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 63;

    TradeMessage() = default;
    TradeMessage(std::chrono::nanoseconds timestamp, std::chrono::nanoseconds transaction_time, SourceVenue source_venue, Decimal executed_size, std::uint64_t instrument, Decimal price, const std::array<std::byte, 8>& reserved_8, std::uint64_t trade_id, TradeType trade_type, AuctionType auction_type, const TradeFlags& trade_flags, HiddenExecutionIndicator hidden_execution_indicator, TradeQualifier trade_qualifier);

    // Timestamp: Time the message was generated.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Transaction Time: Execution timestamp as reported by the supported market. If a trade is
    // cancelled or amended, this field will contain the transaction time of the original
    // trade.
    std::chrono::nanoseconds transaction_time() const;
    void set_transaction_time(std::chrono::nanoseconds value);

    // Source Venue: Venue from which market data is received for the instrument.
    SourceVenue source_venue() const;
    void set_source_venue(SourceVenue value);

    // Executed Size: Total executed quantity.
    Decimal executed_size() const;
    void set_executed_size(Decimal value);

    // Instrument: GTP Instrument identifier.
    std::uint64_t instrument() const;
    void set_instrument(std::uint64_t value);

    // Price: Limit price of the order.
    Decimal price() const;
    void set_price(Decimal value);

    // Reserved 8: Reserved for future use.
    const std::array<std::byte, 8>& reserved_8() const;
    std::array<std::byte, 8>& reserved_8();
    void set_reserved_8(const std::array<std::byte, 8>& value);

    // Trade Id: Unique identifier of the trade.
    std::uint64_t trade_id() const;
    void set_trade_id(std::uint64_t value);

    // Trade Type: Type of the trade.
    TradeType trade_type() const;
    void set_trade_type(TradeType value);

    // Auction Type: The value in this field is only relevant when Trade Type is 1.
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Trade Flags: Trade Flags
    const TradeFlags& trade_flags() const;
    TradeFlags& trade_flags();
    void set_trade_flags(const TradeFlags& value);

    // Hidden Execution Indicator: For London Stock Exchange, during continuous trading and CPX
    // session, 1[2] will be sent for execution of visible[hidden] quantities. For London Stock
    // Exchange Auction Trades, 0 will be sent indicating 'Not Applicable' (N/A).
    HiddenExecutionIndicator hidden_execution_indicator() const;
    void set_hidden_execution_indicator(HiddenExecutionIndicator value);

    // Trade Qualifier: Qualifier of the trade.
    TradeQualifier trade_qualifier() const;
    void set_trade_qualifier(TradeQualifier value);

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

    bool operator==(const TradeMessage& other) const;
    bool operator!=(const TradeMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::chrono::nanoseconds transaction_time_{};
    SourceVenue source_venue_{};
    Decimal executed_size_{ 0, -8 };
    std::uint64_t instrument_{};
    Decimal price_{ 0, -8 };
    std::array<std::byte, 8> reserved_8_{};
    std::uint64_t trade_id_{};
    TradeType trade_type_{};
    AuctionType auction_type_{};
    TradeFlags trade_flags_{};
    HiddenExecutionIndicator hidden_execution_indicator_{};
    TradeQualifier trade_qualifier_{};
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
