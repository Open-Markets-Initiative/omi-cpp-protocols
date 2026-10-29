#pragma once

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

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Options Imbalance messages are published once a second during opening and reopening auctions
// to update price and volume information
class OptionsImbalanceMessage {
  public:
    static constexpr const char* name = "OptionsImbalanceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsImbalanceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsImbalanceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 61;
    static constexpr std::size_t fixed_size = 61;
    std::size_t encoded_size() const { return 61; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(12)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(16).template first<4>(); }

    std::uint32_t paired_qty() const { return wire::read_u32_le(at(20)); }

    std::uint32_t total_imbalance_qty() const { return wire::read_u32_le(at(24)); }

    std::uint32_t market_imbalance_qty() const { return wire::read_u32_le(at(28)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(32).template first<2>(); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(34))); }

    ImbalanceSide imbalance_side() const { return static_cast<ImbalanceSide>(wire::read_char(at(35))); }

    std::int32_t continuous_book_clearing_price() const { return wire::read_i32_le(at(36)); }

    std::int32_t auction_interest_clearing_price() const { return wire::read_i32_le(at(40)); }

    std::span<const std::byte, 4> second_reserved_4() const { return bytes_.subspan(44).template first<4>(); }

    std::int32_t indicative_match_price() const { return wire::read_i32_le(at(48)); }

    std::int32_t upper_collar() const { return wire::read_i32_le(at(52)); }

    std::int32_t lower_collar() const { return wire::read_i32_le(at(56)); }

    AuctionStatus auction_status() const { return static_cast<AuctionStatus>(wire::read_u8(at(60))); }

    void print(std::ostream& out) const {
        out << "OptionsImbalanceMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", paired_qty=";
        out << paired_qty();
        out << ", total_imbalance_qty=";
        out << total_imbalance_qty();
        out << ", market_imbalance_qty=";
        out << market_imbalance_qty();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << ", auction_type=";
        out << auction_type();
        out << ", imbalance_side=";
        out << imbalance_side();
        out << ", continuous_book_clearing_price=";
        out << continuous_book_clearing_price();
        out << ", auction_interest_clearing_price=";
        out << auction_interest_clearing_price();
        out << ", second_reserved_4=";
        print::hex(out, second_reserved_4().data(), second_reserved_4().size());
        out << ", indicative_match_price=";
        out << indicative_match_price();
        out << ", upper_collar=";
        out << upper_collar();
        out << ", lower_collar=";
        out << lower_collar();
        out << ", auction_status=";
        out << auction_status();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsImbalanceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
