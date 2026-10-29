#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../groups/MdTradeEntryGrp.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Published when a trade is reversed.
class TradeReversalMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TradeReversalMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 416;

    TradeReversalMessage() = default;
    TradeReversalMessage(std::int64_t security_id, std::chrono::nanoseconds transact_time, std::uint32_t trd_match_id, const std::array<std::byte, 4>& pad_4, std::int64_t last_qty, Decimal last_px, std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time, std::uint8_t no_md_entries, const std::array<std::byte, 7>& pad_7, const std::array<MdTradeEntryGrp, 15>& md_trade_entry_grp);

    // Security Id: Unique instrument identifier.
    std::int64_t security_id() const;
    void set_security_id(std::int64_t value);

    // Transact Time: Transaction timestamp.
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Trd Match Id: Unique identifier for each price level of a match event.
    std::uint32_t trd_match_id() const;
    void set_trd_match_id(std::uint32_t value);

    // Pad 4: not used
    const std::array<std::byte, 4>& pad_4() const;
    std::array<std::byte, 4>& pad_4();
    void set_pad_4(const std::array<std::byte, 4>& value);

    // Last Qty: The potential matchable quantity for the auction.
    std::int64_t last_qty() const;
    void set_last_qty(std::int64_t value);

    // Last Px: Indicating the potential Auction price for a crossed order book.
    Decimal last_px() const;
    void set_last_px(Decimal value);

    // Trd Reg Ts Execution Time: Last matching execution timestamp.
    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time() const;
    void set_trd_reg_ts_execution_time(std::optional<std::chrono::nanoseconds> value);

    // No Md Entries: Number of entries in Market Data message for MDEntryGrp.
    std::uint8_t no_md_entries() const;
    void set_no_md_entries(std::uint8_t value);

    // Pad 7: not used
    const std::array<std::byte, 7>& pad_7() const;
    std::array<std::byte, 7>& pad_7();
    void set_pad_7(const std::array<std::byte, 7>& value);

    // Md Trade Entry Grp: Trade statistics repeated NoMDEntries times in the Trade Reversal
    // Message.
    const std::array<MdTradeEntryGrp, 15>& md_trade_entry_grp() const;
    std::array<MdTradeEntryGrp, 15>& md_trade_entry_grp();
    void set_md_trade_entry_grp(const std::array<MdTradeEntryGrp, 15>& value);

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

    bool operator==(const TradeReversalMessage& other) const;
    bool operator!=(const TradeReversalMessage& other) const;

  private:
    std::int64_t security_id_{};
    std::chrono::nanoseconds transact_time_{};
    std::uint32_t trd_match_id_{};
    std::array<std::byte, 4> pad_4_{};
    std::int64_t last_qty_{};
    Decimal last_px_{ 0, -6 };
    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time_{};
    std::uint8_t no_md_entries_{};
    std::array<std::byte, 7> pad_7_{};
    std::array<MdTradeEntryGrp, 15> md_trade_entry_grp_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
