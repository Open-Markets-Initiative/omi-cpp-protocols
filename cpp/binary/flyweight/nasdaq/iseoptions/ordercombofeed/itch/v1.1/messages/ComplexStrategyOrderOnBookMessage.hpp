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

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// An Order on Book message is generated for all the following situations whenever an order
// free from any display restrictions is reported by the matching engine. In all such cases the
// order size to be displayed is as reported by the matching engine
class ComplexStrategyOrderOnBookMessage {
  public:
    static constexpr const char* name = "ComplexStrategyOrderOnBookMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexStrategyOrderOnBookMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexStrategyOrderOnBookMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    static constexpr std::size_t fixed_size = 41;
    std::size_t encoded_size() const { return 41; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t strategy_id() const { return wire::read_u32_be(at(6)); }

    OrderType order_type() const { return static_cast<OrderType>(wire::read_char(at(10))); }

    Side side() const { return static_cast<Side>(wire::read_char(at(11))); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(12))), -4); }

    std::uint32_t size() const { return wire::read_u32_be(at(16)); }

    ExecFlag exec_flag() const { return static_cast<ExecFlag>(wire::read_char(at(20))); }

    OrderCapacity order_capacity() const { return static_cast<OrderCapacity>(wire::read_char(at(21))); }

    Scope scope() const { return static_cast<Scope>(wire::read_char(at(22))); }

    std::string_view owner_id() const { return view::text(at(23), 6, ' '); }

    std::string_view giveup() const { return view::text(at(29), 6, ' '); }

    std::string_view cmta() const { return view::text(at(35), 6, ' '); }

    void print(std::ostream& out) const {
        out << "ComplexStrategyOrderOnBookMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", strategy_id=";
        out << strategy_id();
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
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexStrategyOrderOnBookMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
