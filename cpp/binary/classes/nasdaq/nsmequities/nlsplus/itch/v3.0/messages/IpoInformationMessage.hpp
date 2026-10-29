#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ReferenceForNetChange.hpp"
#include "../enums/SecurityClass.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Denotes the reference price to be used for intraday net change calculations for an issue.
class IpoInformationMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::IpoInformationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 14;

    IpoInformationMessage() = default;
    IpoInformationMessage(const std::string& issue_symbol, SecurityClass security_class, ReferenceForNetChange reference_for_net_change, Decimal reference_price);

    // Issue Symbol: Denotes the Nasdaq-assigned issue symbol of the security for which the
    // trade report is being generated
    const std::string& issue_symbol() const;
    std::string& issue_symbol();
    void set_issue_symbol(const std::string& value);

    // Security Class: Indicates the primary listing market for the issue
    SecurityClass security_class() const;
    void set_security_class(SecurityClass value);

    // Reference For Net Change: Indicates the basis of the reference price for net change
    // calculations
    ReferenceForNetChange reference_for_net_change() const;
    void set_reference_for_net_change(ReferenceForNetChange value);

    // Reference Price: Denotes the reference price to be used for intraday net change
    // calculations
    Decimal reference_price() const;
    void set_reference_price(Decimal value);

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

    bool operator==(const IpoInformationMessage& other) const;
    bool operator!=(const IpoInformationMessage& other) const;

  private:
    std::string issue_symbol_{};
    SecurityClass security_class_{};
    ReferenceForNetChange reference_for_net_change_{};
    Decimal reference_price_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
