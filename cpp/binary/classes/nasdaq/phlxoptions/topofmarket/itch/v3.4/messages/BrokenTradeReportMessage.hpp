#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

class SequencedMessageVisitor;

// The following message is used in the event that an options trade transaction is broken on
// the same business day that it is reported.
class BrokenTradeReportMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::BrokenTradeReportMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 20;

    BrokenTradeReportMessage() = default;
    BrokenTradeReportMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, std::uint32_t original_cross_id, Decimal original_price, std::uint32_t original_volume);

    // Nanoseconds: The sub-second portion of the time, in nanoseconds (0-999999999). The
    // second portion of the time is obtained from the most recent timestamp message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Option Id: Option ID for this option, assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Original Cross Id: Indicates the internal control number (cross id) associated with the
    // given trade transaction in the options market system.
    std::uint32_t original_cross_id() const;
    void set_original_cross_id(std::uint32_t value);

    // Original Price: Reported Premium Price of an option contract in the original trade
    // report message on this feed.
    Decimal original_price() const;
    void set_original_price(Decimal value);

    // Original Volume: Reported number of contracts in the original trade report message on
    // this feed.
    std::uint32_t original_volume() const;
    void set_original_volume(std::uint32_t value);

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

    bool operator==(const BrokenTradeReportMessage& other) const;
    bool operator!=(const BrokenTradeReportMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t option_id_{};
    std::uint32_t original_cross_id_{};
    Decimal original_price_{ 0, -4 };
    std::uint32_t original_volume_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
