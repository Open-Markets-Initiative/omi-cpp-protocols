#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MarketSide.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class SequencedMessageVisitor;

// For bandwidth efficiency reasons, this message can be published in either short or long
// format.
class AddOrderMessageShortMessageForm : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::AddOrderMessageShortMessageForm;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    AddOrderMessageShortMessageForm() = default;
    AddOrderMessageShortMessageForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, MarketSide market_side, std::uint32_t option_id, Decimal price_short, std::uint16_t volume_short);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Order Reference Number: The unique reference number assigned to the new order. The order
    // reference number is Increasing, but not necessarily sequential.
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Market Side: The type of order being added.
    MarketSide market_side() const;
    void set_market_side(MarketSide value);

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Price Short: The display price of the new order being added to the book. NOTE: When
    // converted to a decimal format, this price is in fixed point format with 3 whole number
    // places followed by 2 decimal digits.
    Decimal price_short() const;
    void set_price_short(Decimal value);

    // Volume Short: The total number of contracts of the new order being added to the book.
    std::uint16_t volume_short() const;
    void set_volume_short(std::uint16_t value);

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

    bool operator==(const AddOrderMessageShortMessageForm& other) const;
    bool operator!=(const AddOrderMessageShortMessageForm& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_reference_number_{};
    MarketSide market_side_{};
    std::uint32_t option_id_{};
    Decimal price_short_{ 0, -4 };
    std::uint16_t volume_short_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
