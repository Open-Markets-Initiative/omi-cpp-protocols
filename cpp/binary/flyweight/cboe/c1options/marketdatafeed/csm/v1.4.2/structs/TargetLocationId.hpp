#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class TargetLocationId {
  public:
    static constexpr const char* name = "TargetLocationId";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TargetLocationId(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TargetLocationId has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return target_location_id_text_end(); }

    std::uint8_t target_location_id_length() const { return wire::read_u8(at(0)); }

    std::size_t target_location_id_text_size() const { return wire::count(target_location_id_length()); }
    std::string_view target_location_id_text() const {
        wire::require("TargetLocationId", 1 + target_location_id_text_size(), bytes_.size());
        return view::characters(at(1), target_location_id_text_size());
    }

    void print(std::ostream& out) const {
        out << "TargetLocationId{";
        out << "target_location_id_length=";
        out << static_cast<int>(target_location_id_length());
        out << ", target_location_id_text=";
        print::text(out, target_location_id_text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t target_location_id_text_end() const { return 1 + target_location_id_text_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TargetLocationId& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
