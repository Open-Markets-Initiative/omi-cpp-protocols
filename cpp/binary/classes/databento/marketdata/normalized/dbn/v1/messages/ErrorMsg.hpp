// Databento.MarketData.Normalized.Dbn.v1: messages/ErrorMsg.hpp
#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class Visitor;

// An error message from the Databento Live Subscription Gateway (LSG)
class ErrorMsg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::Error;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    ErrorMsg() = default;
    ErrorMsg(const std::string& err);

    // Err: The error message
    const std::string& err() const;
    std::string& err();
    void set_err(const std::string& value);

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
};

} // namespace databento::marketdata::normalized::dbn::v1
