#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../bitfields/AddOrderFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Sent to indicate that an anonymous limit or market order is added to the order book.
class AddOrderMessage {
  public:
    static constexpr const char* name = "AddOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 42;
    static constexpr std::size_t fixed_size = 42;
    std::size_t encoded_size() const { return 42; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(12))); }

    std::uint32_t quantity() const { return wire::read_u32_le(at(13)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(17)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(21).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(22).template first<1>(); }

    std::int64_t price() const { return wire::read_i64_le(at(23)); }

    AddOrderFlags add_order_flags() const { return AddOrderFlags{ bytes_.subspan(31) }; }

    std::span<const std::byte, 10> reserved_10() const { return bytes_.subspan(32).template first<10>(); }

    void print(std::ostream& out) const {
        out << "AddOrderMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", quantity=";
        out << quantity();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", reserved_a=";
        print::hex(out, reserved_a().data(), reserved_a().size());
        out << ", reserved_b=";
        print::hex(out, reserved_b().data(), reserved_b().size());
        out << ", price=";
        out << price();
        out << ", add_order_flags=";
        add_order_flags().print(out);
        out << ", reserved_10=";
        print::hex(out, reserved_10().data(), reserved_10().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
