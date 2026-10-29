#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/SystemStatus.hpp"
#include "../messages/Data.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class DataVisitor;

// System State Message
class SystemStateMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SystemStateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 18;

    SystemStateMessage() = default;
    SystemStateMessage(std::chrono::nanoseconds timestamp, const std::string& tom_version, std::uint8_t session_id, SystemStatus system_status);

    // Timestamp: Matching Engine time
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Tom Version: Protocol Version
    const std::string& tom_version() const;
    std::string& tom_version();
    void set_tom_version(const std::string& value);

    // Session Id: Current trading session identifier
    std::uint8_t session_id() const;
    void set_session_id(std::uint8_t value);

    // System Status: System Status
    SystemStatus system_status() const;
    void set_system_status(SystemStatus value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const SystemStateMessage& other) const;
    bool operator!=(const SystemStateMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::string tom_version_{};
    std::uint8_t session_id_{};
    SystemStatus system_status_{};
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
