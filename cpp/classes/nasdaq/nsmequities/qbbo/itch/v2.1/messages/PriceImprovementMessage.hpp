#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/InterestFlag.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class Visitor;

// Indicates a retail interest indication of the Bid, Ask or both the Bid and Ask for
// Nasdaq-listed securities.
class PriceImprovementMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::PriceImprovementMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    PriceImprovementMessage() = default;
    PriceImprovementMessage(std::uint16_t tracking, std::chrono::nanoseconds time_stamp, const std::string& stock, InterestFlag interest_flag);

    // Tracking: Nasdaq internal tracking number
    std::uint16_t tracking() const;
    void set_tracking(std::uint16_t value);

    // Time Stamp: Timestamp
    std::chrono::nanoseconds time_stamp() const;
    void set_time_stamp(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in the execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Interest Flag: Indicates the type of price improvement available
    InterestFlag interest_flag() const;
    void set_interest_flag(InterestFlag value);

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

    bool operator==(const PriceImprovementMessage& other) const;
    bool operator!=(const PriceImprovementMessage& other) const;

  private:
    std::uint16_t tracking_{};
    std::chrono::nanoseconds time_stamp_{};
    std::string stock_{};
    InterestFlag interest_flag_{};
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
