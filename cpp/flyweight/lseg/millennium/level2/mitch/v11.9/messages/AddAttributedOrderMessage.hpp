#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../bitfields/AddAttributedOrderFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Indicates that a named order is added to the order book.
class AddAttributedOrderMessage {
  public:
    static constexpr const char* name = "AddAttributedOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AddAttributedOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AddAttributedOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 43;
    static constexpr std::size_t fixed_size = 43;
    std::size_t encoded_size() const { return 43; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(12))); }

    std::uint32_t quantity() const { return wire::read_u32_le(at(13)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(17)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(21).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(22).template first<1>(); }

    std::int64_t price() const { return wire::read_i64_le(at(23)); }

    std::string_view attribution() const { return view::text(at(31), 11, ' '); }

    AddAttributedOrderFlags add_attributed_order_flags() const { return AddAttributedOrderFlags{ bytes_.subspan(42) }; }

    void print(std::ostream& out) const {
        out << "AddAttributedOrderMessage{";
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
        out << ", attribution=";
        print::text(out, attribution());
        out << ", add_attributed_order_flags=";
        add_attributed_order_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AddAttributedOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
