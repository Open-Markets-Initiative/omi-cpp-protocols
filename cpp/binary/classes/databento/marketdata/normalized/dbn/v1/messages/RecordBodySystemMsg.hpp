// Databento.MarketData.Normalized.Dbn.v1: messages/RecordBodySystemMsg.hpp
#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/GatewayMessage.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class GatewayMessageVisitor;

// A non-error message from the Databento Live Subscription Gateway (LSG); also used for
// heartbeating
class RecordBodySystemMsg : public GatewayMessage {
  public:
    // The code that selects this message
    static constexpr GatewayMessageCode message_type = Rtype::System;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    RecordBodySystemMsg() = default;
    RecordBodySystemMsg(const std::string& msg);

    // Msg: The message from the Databento Live Subscription Gateway (LSG)
    const std::string& msg() const;
    std::string& msg();
    void set_msg(const std::string& value);

    // GatewayMessage
    GatewayMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(GatewayMessageVisitor& visitor) const override;
    std::unique_ptr<GatewayMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const GatewayMessage& other) const override;

    bool operator==(const RecordBodySystemMsg& other) const;
    bool operator!=(const RecordBodySystemMsg& other) const;

  private:
    std::string msg_{};
};

} // namespace databento::marketdata::normalized::dbn::v1
