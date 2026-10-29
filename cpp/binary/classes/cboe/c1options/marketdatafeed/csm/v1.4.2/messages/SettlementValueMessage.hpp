#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../groups/SettlementValueMdEntry.hpp"
#include "../messages/Message.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Visitor;

// Index value messages contain the values associated with a calculated index. They are
// transmitted when an index is calculated.
class SettlementValueMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SettlementValueMessage;

    SettlementValueMessage() = default;
    SettlementValueMessage(std::uint32_t class_key, std::uint32_t security_id, std::uint8_t price_type, std::uint8_t no_entries, const std::vector<SettlementValueMdEntry>& settlement_value_md_entry);

    // Class Key: Class key
    std::uint32_t class_key() const;
    void set_class_key(std::uint32_t value);

    // Security Id: Product key
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Price Type: Specifies how to interpret the value in the StrikePrice field.
    std::uint8_t price_type() const;
    void set_price_type(std::uint8_t value);

    // No Entries: Number of MDEntries in this message. Will not exceed 255
    std::uint8_t no_entries() const;
    void set_no_entries(std::uint8_t value);

    // Settlement Value Md Entry: The settlement price
    const std::vector<SettlementValueMdEntry>& settlement_value_md_entry() const;
    std::vector<SettlementValueMdEntry>& settlement_value_md_entry();
    void set_settlement_value_md_entry(const std::vector<SettlementValueMdEntry>& value);

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

    bool operator==(const SettlementValueMessage& other) const;
    bool operator!=(const SettlementValueMessage& other) const;

  private:
    std::uint32_t class_key_{};
    std::uint32_t security_id_{};
    std::uint8_t price_type_{};
    std::uint8_t no_entries_{};
    std::vector<SettlementValueMdEntry> settlement_value_md_entry_{};
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
