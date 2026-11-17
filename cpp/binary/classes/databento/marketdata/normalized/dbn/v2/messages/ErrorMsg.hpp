// Databento.MarketData.Normalized.Dbn.v2: messages/ErrorMsg.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/ErrorCode.hpp"
#include "../messages/Message.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

class Visitor;

// An error message from the Databento Live Subscription Gateway (LSG)
class ErrorMsg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::Error;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 304;

    ErrorMsg() = default;
    ErrorMsg(const std::string& err, ErrorCode error_code, std::uint8_t is_last);

    // Err: The error message
    const std::string& err() const;
    std::string& err();
    void set_err(const std::string& value);

    // Error Code: The error code
    ErrorCode error_code() const;
    void set_error_code(ErrorCode value);

    // Is Last: Sometimes multiple errors are sent together; 1 when this is the last in the
    // series
    std::uint8_t is_last() const;
    void set_is_last(std::uint8_t value);

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

    bool operator==(const ErrorMsg& other) const;
    bool operator!=(const ErrorMsg& other) const;

  private:
    std::string err_{};
    ErrorCode error_code_{};
    std::uint8_t is_last_{};
};

} // namespace databento::marketdata::normalized::dbn::v2
