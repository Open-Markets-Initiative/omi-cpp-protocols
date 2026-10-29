#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../groups/RecapUpdateMdEntry.hpp"
#include "../messages/Message.hpp"
#include "../structs/PrevClosePx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Visitor;

// The Recap Update message contains the latest Last Sale price, Last Sale size, Total Volume,
// Open price, High price, Low price, and Previous close price. It is sent as a result of a
// trade or cancel.
class RecapUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::RecapUpdateMessage;

    RecapUpdateMessage() = default;
    RecapUpdateMessage(std::uint32_t class_key, std::uint32_t security_id, std::uint8_t price_type, const PrevClosePx& prev_close_px, std::uint32_t trade_volume, std::uint8_t no_entries, const std::vector<RecapUpdateMdEntry>& recap_update_md_entry);

    // Class Key: Class key
    std::uint32_t class_key() const;
    void set_class_key(std::uint32_t value);

    // Security Id: Product key
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Price Type: Specifies how to interpret the value in the StrikePrice field.
    std::uint8_t price_type() const;
    void set_price_type(std::uint8_t value);

    // Prev Close Px:
    const PrevClosePx& prev_close_px() const;
    PrevClosePx& prev_close_px();
    void set_prev_close_px(const PrevClosePx& value);

    // Trade Volume: Total trade volume for security
    std::uint32_t trade_volume() const;
    void set_trade_volume(std::uint32_t value);

    // No Entries: Number of MDEntries in this message. Will not exceed 255
    std::uint8_t no_entries() const;
    void set_no_entries(std::uint8_t value);

    // Recap Update Md Entry: MDEntry indicating market data
    const std::vector<RecapUpdateMdEntry>& recap_update_md_entry() const;
    std::vector<RecapUpdateMdEntry>& recap_update_md_entry();
    void set_recap_update_md_entry(const std::vector<RecapUpdateMdEntry>& value);

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

    bool operator==(const RecapUpdateMessage& other) const;
    bool operator!=(const RecapUpdateMessage& other) const;

  private:
    std::uint32_t class_key_{};
    std::uint32_t security_id_{};
    std::uint8_t price_type_{};
    PrevClosePx prev_close_px_{};
    std::uint32_t trade_volume_{};
    std::uint8_t no_entries_{};
    std::vector<RecapUpdateMdEntry> recap_update_md_entry_{};
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
