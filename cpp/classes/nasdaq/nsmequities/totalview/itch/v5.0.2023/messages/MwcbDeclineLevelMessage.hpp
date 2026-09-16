#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// Informs data recipients what the daily MWCB breach points are set to for the current trading
// day.
class MwcbDeclineLevelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MwcbDeclineLevelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    MwcbDeclineLevelMessage() = default;
    MwcbDeclineLevelMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, Decimal level_1, Decimal level_2, Decimal level_3);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Level 1: Denotes the MWCB Level 1 Value.
    Decimal level_1() const;
    void set_level_1(Decimal value);

    // Level 2: Denotes the MWCB Level 2 Value.
    Decimal level_2() const;
    void set_level_2(Decimal value);

    // Level 3: Denotes the MWCB Level 3 Value.
    Decimal level_3() const;
    void set_level_3(Decimal value);

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

    bool operator==(const MwcbDeclineLevelMessage& other) const;
    bool operator!=(const MwcbDeclineLevelMessage& other) const;

  private:
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    Decimal level_1_{ 0, -8 };
    Decimal level_2_{ 0, -8 };
    Decimal level_3_{ 0, -8 };
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
