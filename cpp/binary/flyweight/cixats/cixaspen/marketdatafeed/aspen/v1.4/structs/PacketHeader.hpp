#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/FeedIdentifier.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class PacketHeader {
  public:
    static constexpr const char* name = "PacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::string_view market_day_identifier() const { return view::text(at(0), 9, '\0'); }

    FeedIdentifier feed_identifier() const { return static_cast<FeedIdentifier>(wire::read_char(at(9))); }

    std::uint64_t sequence() const { return wire::read_u64_le(at(10)); }

    std::uint16_t count() const { return wire::read_u16_le(at(18)); }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "market_day_identifier=";
        print::text(out, market_day_identifier());
        out << ", feed_identifier=";
        out << feed_identifier();
        out << ", sequence=";
        out << sequence();
        out << ", count=";
        out << count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
