#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/BuySellIndicator.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class SequencedMessageVisitor;

// This Options Trade Message is designed to provide execution details for normal match events
// involving non-displayable order types. (Note: There is a separate message for NASDAQ Option
// auction events.)
class OptionsTradeMessagesNonAuction : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::OptionsTradeMessagesNonAuction;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 29;

    OptionsTradeMessagesNonAuction() = default;
    OptionsTradeMessagesNonAuction(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, BuySellIndicator buy_sell_indicator, std::uint32_t option_id, std::uint32_t cross_number, std::uint32_t match_number, Decimal price_long, std::uint32_t volume_long);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Buy Sell Indicator: The type of non-display order on the book being matched.
    BuySellIndicator buy_sell_indicator() const;
    void set_buy_sell_indicator(BuySellIndicator value);

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Cross Number: Trade Group Id. Ties together all trades of a given atomic transaction in
    // the matching engine.
    std::uint32_t cross_number() const;
    void set_cross_number(std::uint32_t value);

    // Match Number: Execution Id. Identifies the component of an execution. Unique for a given
    // day. The match number is also referenced in the Trade Break Message.
    std::uint32_t match_number() const;
    void set_match_number(std::uint32_t value);

    // Price Long: The display price of the new order being added to the book.
    Decimal price_long() const;
    void set_price_long(Decimal value);

    // Volume Long: The total number of contracts of the new order being added to the book.
    std::uint32_t volume_long() const;
    void set_volume_long(std::uint32_t value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const OptionsTradeMessagesNonAuction& other) const;
    bool operator!=(const OptionsTradeMessagesNonAuction& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    BuySellIndicator buy_sell_indicator_{};
    std::uint32_t option_id_{};
    std::uint32_t cross_number_{};
    std::uint32_t match_number_{};
    Decimal price_long_{ 0, -4 };
    std::uint32_t volume_long_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
