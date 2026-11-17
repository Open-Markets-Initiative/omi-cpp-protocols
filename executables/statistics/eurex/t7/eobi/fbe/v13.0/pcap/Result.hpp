// Eurex.T7.Eobi.Fbe.v13.0: pcap/Result.hpp
#pragma once

namespace packet {

    enum class result {
        eurex_t7_eobi_fbe_v13_0,
        error,
        end_of_file,
        unknown
    };

}