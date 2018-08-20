cc_binary(
    name = "classification_test",
    srcs = ["classification_test.cc"],
    deps = [
        "//lib/assert:assert",
        "//lib/genetic:genetic",
        "//lib/tensor:tensor",
    ],
    data = [
        "test.csv",
    ],
    copts = [
        "-std=c++1y",
    ],
)