#pragma once

#include <cstddef>
#include <memory>
#include <ostream>

#include "../enums/MessageType.hpp"
#include "../messages/Data.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class DataVisitor;

// Application Message
class RefreshResponseMessageApplicationMessage {
  public:

    RefreshResponseMessageApplicationMessage() = default;
    RefreshResponseMessageApplicationMessage(const RefreshResponseMessageApplicationMessage& other);
    RefreshResponseMessageApplicationMessage& operator=(const RefreshResponseMessageApplicationMessage& other);
    RefreshResponseMessageApplicationMessage(RefreshResponseMessageApplicationMessage&& other) noexcept = default;
    RefreshResponseMessageApplicationMessage& operator=(RefreshResponseMessageApplicationMessage&& other) noexcept = default;
    ~RefreshResponseMessageApplicationMessage() = default;

    // Message Type: Code identifying this message type
    MessageType message_type() const;
    void set_message_type(MessageType value);

    // Data: Branch
    const Data* data() const;
    Data* data();
    void set_data(std::unique_ptr<Data> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RefreshResponseMessageApplicationMessage& other) const;
    bool operator!=(const RefreshResponseMessageApplicationMessage& other) const;

  private:
    MessageType message_type_{};
    std::unique_ptr<Data> data_{};
};

std::ostream& operator<<(std::ostream& out, const RefreshResponseMessageApplicationMessage& value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
