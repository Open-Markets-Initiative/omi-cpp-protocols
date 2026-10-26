#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Data.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class DataVisitor;

// This is the message format that will be used to disseminate the "seconds" part of the
// timestamp that is applicable to all messages that are sent in the current second.
class SystemTimeMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SystemTimeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    SystemTimeMessage() = default;
    SystemTimeMessage(std::chrono::seconds seconds);

    // Seconds: Seconds part of the time that applies to all messages that gets disseminated
    // until this message gets sent again.
    std::chrono::seconds seconds() const;
    void set_seconds(std::chrono::seconds value);

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

    bool operator==(const SystemTimeMessage& other) const;
    bool operator!=(const SystemTimeMessage& other) const;

  private:
    std::chrono::seconds seconds_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
