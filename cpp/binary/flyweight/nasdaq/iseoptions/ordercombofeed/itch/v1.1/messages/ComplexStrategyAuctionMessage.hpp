#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/OrderType.hpp"
#include "../enums/Side.hpp"
#include "../common/Decimal.hpp"
#include "../enums/ExecFlag.hpp"
#include "../enums/OrderCapacity.hpp"
#include "../enums/Scope.hpp"
#include "../enums/AuctionEvent.hpp"
#include "../enums/AuctionType.hpp"
#include "../groups/AuctionResponse.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// This message is used to announce strategy auctions. The start of auction is announced,
// followed by possible updates on the auction, and announcing the end of the auction.
class ComplexStrategyAuctionMessage {
  public:
    static constexpr const char* name = "ComplexStrategyAuctionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexStrategyAuctionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexStrategyAuctionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    std::size_t encoded_size() const { return auction_response_end(); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t strategy_id() const { return wire::read_u32_be(at(6)); }

    std::uint32_t auction_id() const { return wire::read_u32_be(at(10)); }

    OrderType order_type() const { return static_cast<OrderType>(wire::read_char(at(14))); }

    Side side() const { return static_cast<Side>(wire::read_char(at(15))); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(16))), -4); }

    std::uint32_t size() const { return wire::read_u32_be(at(20)); }

    ExecFlag exec_flag() const { return static_cast<ExecFlag>(wire::read_char(at(24))); }

    OrderCapacity order_capacity() const { return static_cast<OrderCapacity>(wire::read_char(at(25))); }

    Scope scope() const { return static_cast<Scope>(wire::read_char(at(26))); }

    std::string_view owner_id() const { return view::text(at(27), 6, ' '); }

    std::string_view giveup() const { return view::text(at(33), 6, ' '); }

    std::string_view cmta() const { return view::text(at(39), 6, ' '); }

    AuctionEvent auction_event() const { return static_cast<AuctionEvent>(wire::read_char(at(45))); }

    AuctionType auction_type() const { return static_cast<AuctionType>(wire::read_char(at(46))); }

    std::uint8_t number_of_responses() const { return wire::read_u8(at(47)); }

    view::entries<AuctionResponse> auction_response() const { return view::entries<AuctionResponse>{ bytes_.subspan(48), wire::count(number_of_responses()) }; }

    void print(std::ostream& out) const {
        out << "ComplexStrategyAuctionMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", strategy_id=";
        out << strategy_id();
        out << ", auction_id=";
        out << auction_id();
        out << ", order_type=";
        out << order_type();
        out << ", side=";
        out << side();
        out << ", price=";
        out << price();
        out << ", size=";
        out << size();
        out << ", exec_flag=";
        out << exec_flag();
        out << ", order_capacity=";
        out << order_capacity();
        out << ", scope=";
        out << scope();
        out << ", owner_id=";
        print::text(out, owner_id());
        out << ", giveup=";
        print::text(out, giveup());
        out << ", cmta=";
        print::text(out, cmta());
        out << ", auction_event=";
        out << auction_event();
        out << ", auction_type=";
        out << auction_type();
        out << ", number_of_responses=";
        out << static_cast<int>(number_of_responses());
        out << ", auction_response=";
        print::sequence(out, auction_response());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t auction_response_end() const { return 48 + auction_response().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexStrategyAuctionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
