#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/OperationalHaltStatus.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::deepplus::iextp::v1_05 {

class Visitor;

// The Exchange may suspend trading of one or more securities on IEX for operational reasons
// and indicates such operational halt using the Operational Halt Status Message.
class OperationalHaltStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OperationalHaltStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    OperationalHaltStatusMessage() = default;
    OperationalHaltStatusMessage(OperationalHaltStatus operational_halt_status, std::chrono::nanoseconds timestamp, const std::string& symbol);

    // Operational Halt Status: Operational halt status identifier
    OperationalHaltStatus operational_halt_status() const;
    void set_operational_halt_status(OperationalHaltStatus value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

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

    bool operator==(const OperationalHaltStatusMessage& other) const;
    bool operator!=(const OperationalHaltStatusMessage& other) const;

  private:
    OperationalHaltStatus operational_halt_status_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
};

} // namespace iex::iexequities::deepplus::iextp::v1_05
