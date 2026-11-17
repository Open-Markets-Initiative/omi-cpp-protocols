// Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22: pcap/Result.hpp
#pragma once

namespace packet {

    enum class result {
        cboe_cfefutures_multicastdepthofbook_pitch_v1_2_22,
        error,
        end_of_file,
        unknown
    };

}