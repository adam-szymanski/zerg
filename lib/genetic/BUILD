cc_library(
    name = "genetic",
    srcs = [
        "Genetic.h",
        "NopCrosser.h",
        "Population.h",
    ],
    hdrs = [
    ],
    deps = [
        "//lib/assert:assert",
        "//lib/genetic/classification:classification",
        "//lib/genetic/selectors:selectors",
        "//lib/tensor:tensor",
        "//lib/util:utils"
    ],
    copts = [
        "-std=c++1y",
    ],
    visibility = ["//visibility:public"],
)