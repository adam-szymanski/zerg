cc_library(
    name = "tensor",
    srcs = [
        "Tensor.cc",
        "TensorSize.cc"
    ],
    hdrs = [
        "Tensor.h",
        "TensorSize.h"
    ],
    deps = ["//lib/assert:assert"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "tensor_test",
    srcs = ["TensorTest.cc"],
    deps = [
        "@gtest//:gtest_main",
        ":tensor"
    ],
    data = ["test.csv"],
)