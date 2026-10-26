#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/WidthType.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// Options Only. The Width Update message is used to communicate opening quote width
// multiplier. This message will be sent in the event that the exchange decides to change the
// quote width multiplier on a per underlying basis. For complete details on the opening
// collars see the US Options Opening Process Specification.
class WidthUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::WidthUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    WidthUpdateMessage() = default;
    WidthUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& underlying, WidthType width_type, Decimal multiplier);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Underlying: Symbol of underlying equity right padded with spaces.
    const std::string& underlying() const;
    std::string& underlying();
    void set_underlying(const std::string& value);

    // Width Type: R = Regular, V = Volatility.
    WidthType width_type() const;
    void set_width_type(WidthType value);

    // Multiplier: Width multiplier.
    Decimal multiplier() const;
    void set_multiplier(Decimal value);

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

    bool operator==(const WidthUpdateMessage& other) const;
    bool operator!=(const WidthUpdateMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::string underlying_{};
    WidthType width_type_{};
    Decimal multiplier_{ 0, -1 };
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
