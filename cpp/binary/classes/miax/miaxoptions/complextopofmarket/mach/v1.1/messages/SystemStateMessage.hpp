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

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class DataVisitor;

// This message format is used to notify the firms of the state changes of the system. This is
// a notification that applies to each Underlying group. Firms can use notifications as
// triggers in their system to ensure electronic synchronization of systems.
class SystemStateMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SystemStateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    SystemStateMessage() = default;
    SystemStateMessage(std::chrono::nanoseconds nanoseconds, const std::string& c_to_m_version, std::uint32_t session_id, SystemStatus system_status);

    // Nanoseconds: Time at which this product is added/updated on MIAX system today.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // C To M Version: Eg: CTOM01.01
    const std::string& c_to_m_version() const;
    std::string& c_to_m_version();
    void set_c_to_m_version(const std::string& value);

    // Session Id: MIAX assigned ID for the current trading session
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // System Status: Current system status: “S” = Start of System hours “C” = End of System
    // hours, “1” = Start of Test Session (sent before tests). “2” = End of Test Session.
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
    std::chrono::nanoseconds nanoseconds_{};
    std::string c_to_m_version_{};
    std::uint32_t session_id_{};
    SystemStatus system_status_{};
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
