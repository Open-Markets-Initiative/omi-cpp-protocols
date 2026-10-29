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
#include "../enums/Side.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

// The Add Order Refresh message can be sent in either of two contexts: refresh response or
// symbol refresh.
class AddOrderRefreshMessage {
  public:
    static constexpr const char* name = "AddOrderRefreshMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderRefreshMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderRefreshMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::chrono::seconds source_time() const { return std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::chrono::nanoseconds source_time_ns() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(4)))); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(16)); }

    std::int32_t price() const { return wire::read_i32_le(at(24)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(28)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(32))); }

    std::string_view firm_id() const { return view::text(at(33), 5, ' '); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(38).template first<1>(); }

    void print(std::ostream& out) const {
        out << "AddOrderRefreshMessage{";
        out << "source_time=";
        out << source_time().count();
        out << ", source_time_ns=";
        out << source_time_ns().count();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", order_id=";
        out << order_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", side=";
        out << side();
        out << ", firm_id=";
        print::text(out, firm_id());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderRefreshMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
