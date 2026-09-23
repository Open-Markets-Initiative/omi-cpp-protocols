#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Value identifying sequenced message type
struct SequencedMessageType {

    static constexpr auto name = "Sequenced Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SequencedMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SequencedMessageType(const char &value)
     : value{ value } {}

    // get value of SequencedMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
