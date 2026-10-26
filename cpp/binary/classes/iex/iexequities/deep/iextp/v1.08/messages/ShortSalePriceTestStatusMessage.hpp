#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Detail.hpp"
#include "../enums/ShortSalePriceTestStatus.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

class Visitor;

// The Short Sale Price Test Message is used to indicate when a short sale price test
// restriction is in effect for a security.
class ShortSalePriceTestStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ShortSalePriceTestStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 18;

    ShortSalePriceTestStatusMessage() = default;
    ShortSalePriceTestStatusMessage(ShortSalePriceTestStatus short_sale_price_test_status, std::chrono::nanoseconds timestamp, const std::string& symbol, Detail detail);

    // Short Sale Price Test Status: Reg. SHO short sale price test restriction status
    ShortSalePriceTestStatus short_sale_price_test_status() const;
    void set_short_sale_price_test_status(ShortSalePriceTestStatus value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Detail: Detail of the Reg. SHO short sale price test restriction status
    Detail detail() const;
    void set_detail(Detail value);

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

    bool operator==(const ShortSalePriceTestStatusMessage& other) const;
    bool operator!=(const ShortSalePriceTestStatusMessage& other) const;

  private:
    ShortSalePriceTestStatus short_sale_price_test_status_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
    Detail detail_{};
};

} // namespace iex::iexequities::deep::iextp::v1_08
