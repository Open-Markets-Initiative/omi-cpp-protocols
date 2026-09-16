#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/RegShoAction.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// Nasaq processes orders based on the most Reg SHO Restriction status value
class RegShoShortSalePriceTestRestrictedIndicatorMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 19;

    RegShoShortSalePriceTestRestrictedIndicatorMessage() = default;
    RegShoShortSalePriceTestRestrictedIndicatorMessage(std::uint16_t locate_code, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, RegShoAction reg_sho_action);

    // Locate Code: Locate code identifying the security
    std::uint16_t locate_code() const;
    void set_locate_code(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Stock: Denotes the security symbol for the issue in the NASDAQ execution system.
    const std::string& stock() const;
    std::string& stock();
    void set_stock(const std::string& value);

    // Reg Sho Action: Denotes the Reg SHO Short Sale Price Test Restriction status for the
    // issue at the time of the message dissemination
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

    bool operator==(const RegShoShortSalePriceTestRestrictedIndicatorMessage& other) const;
    bool operator!=(const RegShoShortSalePriceTestRestrictedIndicatorMessage& other) const;

  private:
    std::uint16_t locate_code_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::string stock_{};
    RegShoAction reg_sho_action_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
