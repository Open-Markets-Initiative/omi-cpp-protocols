#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Informs the market of the daily market wide circuit breaker decline levels, disseminated at
// the start of the trading day.
class MwcbDeclineLevelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::MwcbDeclineLevelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    MwcbDeclineLevelMessage() = default;
    MwcbDeclineLevelMessage(Decimal level_1, Decimal level_2, Decimal level_3);

    // Level 1: Denotes the Mwcb Level 1 value
    Decimal level_1() const;
    void set_level_1(Decimal value);

    // Level 2: Denotes the Mwcb Level 2 value
    Decimal level_2() const;
    void set_level_2(Decimal value);

    // Level 3: Denotes the Mwcb Level 3 value
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
    Decimal level_1_{ 0, -8 };
    Decimal level_2_{ 0, -8 };
    Decimal level_3_{ 0, -8 };
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
