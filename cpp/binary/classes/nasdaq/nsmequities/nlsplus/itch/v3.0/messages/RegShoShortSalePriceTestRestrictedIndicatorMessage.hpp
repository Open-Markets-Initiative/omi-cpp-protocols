#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/RegShoAction.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class Visitor;

// Indicates the Reg Sho short sale price test restriction status for an issue, under Rule 201
// of Regulation Sho.
class RegShoShortSalePriceTestRestrictedIndicatorMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    RegShoShortSalePriceTestRestrictedIndicatorMessage() = default;
    RegShoShortSalePriceTestRestrictedIndicatorMessage(const std::string& issue_symbol, RegShoAction reg_sho_action);

    // Issue Symbol: Denotes the Nasdaq-assigned issue symbol of the security for which the
    // trade report is being generated
    const std::string& issue_symbol() const;
    std::string& issue_symbol();
    void set_issue_symbol(const std::string& value);

    // Reg Sho Action: Denotes the Reg Sho short sale price test restriction status for the
    // issue
    RegShoAction reg_sho_action() const;
    void set_reg_sho_action(RegShoAction value);

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

    bool operator==(const RegShoShortSalePriceTestRestrictedIndicatorMessage& other) const;
    bool operator!=(const RegShoShortSalePriceTestRestrictedIndicatorMessage& other) const;

  private:
    std::string issue_symbol_{};
    RegShoAction reg_sho_action_{};
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
