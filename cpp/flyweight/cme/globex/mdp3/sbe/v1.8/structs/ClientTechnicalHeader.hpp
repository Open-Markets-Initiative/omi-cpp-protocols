#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Cme Technical Header sent by the firm to Cme
class ClientTechnicalHeader {
  public:
    static constexpr const char* name = "ClientTechnicalHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ClientTechnicalHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ClientTechnicalHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 14;
    static constexpr std::size_t fixed_size = 14;
    std::size_t encoded_size() const { return 14; }

    std::uint16_t encoding_type() const { return wire::read_u16_le(at(0)); }

    std::uint32_t message_sequence_number() const { return wire::read_u32_le(at(2)); }

    std::chrono::nanoseconds tcp_sending_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(6)))); }

    void print(std::ostream& out) const {
        out << "ClientTechnicalHeader{";
        out << "encoding_type=";
        out << encoding_type();
        out << ", message_sequence_number=";
        out << message_sequence_number();
        out << ", tcp_sending_time=";
        out << tcp_sending_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ClientTechnicalHeader& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
