#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/ImbalanceSide.hpp"
#include "../enums/AuctionStatus.hpp"
#include "../enums/FreezeStatus.hpp"
#include "../enums/UnpairedSide.hpp"

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

// Imbalance messages are published once a second during auctions to update price and volume
// information.
class ImbalanceMessage {
  public:
    static constexpr const char* name = "ImbalanceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ImbalanceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ImbalanceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 69;
    static constexpr std::size_t fixed_size = 69;
    std::size_t encoded_size() const { return 69; }

    std::chrono::seconds source_time() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::chrono::nanoseconds source_time_ns() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(4)))); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::int32_t reference_price() const { return wire::read_i32_le(at(16)); }

    std::uint32_t paired_qty() const { return wire::read_u32_le(at(20)); }

    std::uint32_t total_imbalance_qty() const { return wire::read_u32_le(at(24)); }

    std::uint32_t market_imbalance_qty() const { return wire::read_u32_le(at(28)); }

    std::uint16_t auction_time() const { return wire::read_u16_le(at(32)); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(34))); }

    ImbalanceSide imbalance_side() const { return static_cast<ImbalanceSide>(wire::read_char(at(35))); }

    std::int32_t continuous_book_clearing_price() const { return wire::read_i32_le(at(36)); }

    std::int32_t auction_interest_clearing_price() const { return wire::read_i32_le(at(40)); }

    std::int32_t ssr_filing_price() const { return wire::read_i32_le(at(44)); }

    std::int32_t indicative_match_price() const { return wire::read_i32_le(at(48)); }

    std::int32_t upper_collar() const { return wire::read_i32_le(at(52)); }

    std::int32_t lower_collar() const { return wire::read_i32_le(at(56)); }

    AuctionStatus auction_status() const { return static_cast<AuctionStatus>(wire::read_u8(at(60))); }

    FreezeStatus freeze_status() const { return static_cast<FreezeStatus>(wire::read_u8(at(61))); }

    std::uint8_t num_extensions() const { return wire::read_u8(at(62)); }

    std::uint32_t unpaired_qty() const { return wire::read_u32_le(at(63)); }

    UnpairedSide unpaired_side() const { return static_cast<UnpairedSide>(wire::read_char(at(67))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(68).template first<1>(); }

    void print(std::ostream& out) const {
        out << "ImbalanceMessage{";
        out << "source_time=";
        out << source_time().count();
        out << ", source_time_ns=";
        out << source_time_ns().count();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", reference_price=";
        out << reference_price();
        out << ", paired_qty=";
        out << paired_qty();
        out << ", total_imbalance_qty=";
        out << total_imbalance_qty();
        out << ", market_imbalance_qty=";
        out << market_imbalance_qty();
        out << ", auction_time=";
        out << auction_time();
        out << ", auction_type=";
        out << auction_type();
        out << ", imbalance_side=";
        out << imbalance_side();
        out << ", continuous_book_clearing_price=";
        out << continuous_book_clearing_price();
        out << ", auction_interest_clearing_price=";
        out << auction_interest_clearing_price();
        out << ", ssr_filing_price=";
        out << ssr_filing_price();
        out << ", indicative_match_price=";
        out << indicative_match_price();
        out << ", upper_collar=";
        out << upper_collar();
        out << ", lower_collar=";
        out << lower_collar();
        out << ", auction_status=";
        out << auction_status();
        out << ", freeze_status=";
        out << freeze_status();
        out << ", num_extensions=";
        out << static_cast<int>(num_extensions());
        out << ", unpaired_qty=";
        out << unpaired_qty();
        out << ", unpaired_side=";
        out << unpaired_side();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ImbalanceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g
