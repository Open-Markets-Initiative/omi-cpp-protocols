#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace siac::opra::output::obi::v6_2 {

// Administrative Message
class AdministrativeMessage {
  public:
    static constexpr const char* name = "AdministrativeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AdministrativeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AdministrativeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    std::size_t encoded_size() const { return message_data_end(); }

    char message_indicator() const { return wire::read_char(at(0)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(1)); }

    std::uint32_t participant_reference_number() const { return wire::read_u32_be(at(5)); }

    std::uint16_t message_data_length() const { return wire::read_u16_be(at(9)); }

    std::size_t message_data_size() const { return wire::count(message_data_length()); }
    std::string_view message_data() const {
        wire::require("AdministrativeMessage", 11 + message_data_size(), bytes_.size());
        return view::characters(at(11), message_data_size());
    }

    void print(std::ostream& out) const {
        out << "AdministrativeMessage{";
        out << "message_indicator=";
        print::character(out, message_indicator());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", message_data_length=";
        out << message_data_length();
        out << ", message_data=";
        print::text(out, message_data());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t message_data_end() const { return 11 + message_data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AdministrativeMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
