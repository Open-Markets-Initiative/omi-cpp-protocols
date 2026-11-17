// Databento.MarketData.Normalized.Dbn.v3: messages/SystemMsg.hpp
#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/SystemCode.hpp"
#include "../messages/Message.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

class Visitor;

// A non-error message from the Databento Live Subscription Gateway (LSG); also used for
// heartbeating
class SystemMsg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::System;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 304;

    SystemMsg() = default;
    SystemMsg(const std::string& msg, SystemCode system_code);

    // Msg: The message from the Databento Live Subscription Gateway (LSG)
    const std::string& msg() const;
    std::string& msg();
    void set_msg(const std::string& value);

    // System Code: Type of system message
    SystemCode system_code() const;
    void set_system_code(SystemCode value);

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

    bool operator==(const SystemMsg& other) const;
    bool operator!=(const SystemMsg& other) const;

  private:
    std::string msg_{};
    SystemCode system_code_{};
};

} // namespace databento::marketdata::normalized::dbn::v3
