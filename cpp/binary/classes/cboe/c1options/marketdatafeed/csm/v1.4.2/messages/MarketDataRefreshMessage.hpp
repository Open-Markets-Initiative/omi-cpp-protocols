#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../enums/SecurityTradingStatus.hpp"
#include "../groups/MdEntry.hpp"
#include "../messages/Message.hpp"
#include "../structs/PrevClosePx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Visitor;

// The Market Data Refresh message contains a snapshot / refresh of the Current Market and
// Recap information (Last Sale, Last Sale Size, Open, High, Low, Previous Close Price) for one
// product.
class MarketDataRefreshMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::MarketDataRefreshMessage;

    MarketDataRefreshMessage() = default;
    MarketDataRefreshMessage(std::uint32_t class_key, std::uint32_t security_id, SecurityTradingStatus security_trading_status, std::uint8_t price_type, std::uint32_t appl_seq_num, const PrevClosePx& prev_close_px, std::uint32_t trade_volume, std::uint8_t no_entries, const std::vector<MdEntry>& md_entry);

    // Class Key: Class key
    std::uint32_t class_key() const;
    void set_class_key(std::uint32_t value);

    // Security Id: Product key
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Security Trading Status:
    SecurityTradingStatus security_trading_status() const;
    void set_security_trading_status(SecurityTradingStatus value);

    // Price Type: Specifies how to interpret the value in the StrikePrice field.
    std::uint8_t price_type() const;
    void set_price_type(std::uint8_t value);

    // Appl Seq Num: Sequence number for Refresh message, will be set per line and reset to 1
    // (one) when refresh is completed
    std::uint32_t appl_seq_num() const;
    void set_appl_seq_num(std::uint32_t value);

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

    // Md Entry: MDEntry
    const std::vector<MdEntry>& md_entry() const;
    std::vector<MdEntry>& md_entry();
    void set_md_entry(const std::vector<MdEntry>& value);

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

    bool operator==(const MarketDataRefreshMessage& other) const;
    bool operator!=(const MarketDataRefreshMessage& other) const;

  private:
    std::uint32_t class_key_{};
    std::uint32_t security_id_{};
    SecurityTradingStatus security_trading_status_{};
    std::uint8_t price_type_{};
    std::uint32_t appl_seq_num_{};
    PrevClosePx prev_close_px_{};
    std::uint32_t trade_volume_{};
    std::uint8_t no_entries_{};
    std::vector<MdEntry> md_entry_{};
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
