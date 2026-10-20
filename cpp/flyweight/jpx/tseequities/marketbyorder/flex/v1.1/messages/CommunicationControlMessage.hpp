#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TestModeFlag.hpp"
#include "../enums/CommunicationStartEndFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Provides information about communication control. Delivered when communication starts and
// ends, and in between at minute intervals.
class CommunicationControlMessage {
  public:
    static constexpr const char* name = "CommunicationControlMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CommunicationControlMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CommunicationControlMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 2;
    static constexpr std::size_t fixed_size = 2;
    std::size_t encoded_size() const { return 2; }

    TestModeFlag test_mode_flag() const { return static_cast<TestModeFlag>(wire::read_u8(at(0))); }

    CommunicationStartEndFlag communication_start_end_flag() const { return static_cast<CommunicationStartEndFlag>(wire::read_u8(at(1))); }

    void print(std::ostream& out) const {
        out << "CommunicationControlMessage{";
        out << "test_mode_flag=";
        out << test_mode_flag();
        out << ", communication_start_end_flag=";
        out << communication_start_end_flag();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CommunicationControlMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
