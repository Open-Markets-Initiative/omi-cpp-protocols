// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/HeartbeatBody.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/BodyHeader.hpp"
#include "../groups/AdminBody.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class HeartbeatBody {
  public:
    static constexpr const char* name = "HeartbeatBody";

    // the bytes it reads, which it does not own: they must outlive it
    // and the fields of the packet around it that count its entries
    HeartbeatBody(std::span<const std::byte> bytes, std::uint8_t num_body) noexcept
      : bytes_{ bytes }, num_body_{ num_body } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every HeartbeatBody has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 6;
    std::size_t encoded_size() const { return admin_body_end(); }

    BodyHeader body_header() const { return BodyHeader{ bytes_.subspan(0) }; }

    std::uint8_t admin_id() const { return wire::read_u8(at(3)); }

    std::uint16_t hb_interval() const { return wire::read_u16_le(at(4)); }

    view::entries<AdminBody> admin_body() const { return view::entries<AdminBody>{ bytes_.subspan(6), wire::count(num_body_) }; }

    void print(std::ostream& out) const {
        out << "HeartbeatBody{";
        out << "body_header=";
        body_header().print(out);
        out << ", admin_id=";
        out << static_cast<int>(admin_id());
        out << ", hb_interval=";
        out << hb_interval();
        out << ", admin_body=";
        print::sequence(out, admin_body());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t admin_body_end() const { return 6 + admin_body().encoded_size(); }

    std::span<const std::byte> bytes_;
    // the Num Body the packet around it handed it, which counts its entries
    std::uint8_t num_body_;
};

inline std::ostream& operator<<(std::ostream& out, const HeartbeatBody& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
