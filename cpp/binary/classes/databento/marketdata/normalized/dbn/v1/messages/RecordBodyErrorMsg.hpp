// Databento.MarketData.Normalized.Dbn.v1: messages/RecordBodyErrorMsg.hpp
#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/GatewayMessage.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class GatewayMessageVisitor;

// An error message from the Databento Live Subscription Gateway (LSG)
class RecordBodyErrorMsg : public GatewayMessage {
  public:
    // The code that selects this message
    static constexpr GatewayMessageCode message_type = Rtype::Error;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    RecordBodyErrorMsg() = default;
    RecordBodyErrorMsg(const std::string& err);

    // Err: The error message
    const std::string& err() const;
    std::string& err();
    void set_err(const std::string& value);

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

    bool operator==(const RecordBodyErrorMsg& other) const;
    bool operator!=(const RecordBodyErrorMsg& other) const;

  private:
    std::string err_{};
};

} // namespace databento::marketdata::normalized::dbn::v1
