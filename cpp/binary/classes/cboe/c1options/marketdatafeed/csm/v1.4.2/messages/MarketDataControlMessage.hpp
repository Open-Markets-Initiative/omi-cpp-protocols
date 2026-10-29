#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/MdControlType.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Visitor;

// Market Data Control messages mark the start and end of the end of session Summary and the
// end of session Settlement data transmissions.
class MarketDataControlMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::MarketDataControlMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 1;

    MarketDataControlMessage() = default;
    MarketDataControlMessage(MdControlType md_control_type);

    // Md Control Type:
    MdControlType md_control_type() const;
    void set_md_control_type(MdControlType value);

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

    bool operator==(const MarketDataControlMessage& other) const;
    bool operator!=(const MarketDataControlMessage& other) const;

  private:
    MdControlType md_control_type_{};
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
