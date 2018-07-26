# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
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

