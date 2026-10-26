#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/RegShoAction.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class Visitor;

// Nasdaq introduced the Reg SHO Short Sale Price Test Restricted Indicator message format.
class RegShoRestrictionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RegShoRestrictionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    RegShoRestrictionMessage() = default;
    RegShoRestrictionMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, const std::string& stock, RegShoAction reg_sho_action);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Time Stamp: Timestamp
    std::chrono::nanoseconds time_stamp() const;
    void set_time_stamp(std::chrono::nanoseconds value);
    std::int64_t time_stamp_utc(const calendar::Day& day) const;

    // Stock: Denotes the security symbol for the issue in the execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Reg Sho Action: Denotes the Reg SHO Short Sale Price Test Restriction status for the
    // issue at the time of the message dissemination.
    RegShoAction reg_sho_action() const;
    void set_reg_sho_action(RegShoAction value);

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

    bool operator==(const RegShoRestrictionMessage& other) const;
    bool operator!=(const RegShoRestrictionMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds time_stamp_{};
    std::string stock_{};
    RegShoAction reg_sho_action_{};
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
