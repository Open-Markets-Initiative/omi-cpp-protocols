#pragma once

#include "../types/MemoLength.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

struct Memo {

    MemoLength memo_length;

    // parse method
    static Memo* parse(std::byte* buffer) {
        return reinterpret_cast<Memo*>(buffer);
    }

    // parse method const
    static const Memo* parse(const std::byte* buffer) {
        return reinterpret_cast<const Memo*>(buffer);
    }
};

#pragma pack(pop)
}
