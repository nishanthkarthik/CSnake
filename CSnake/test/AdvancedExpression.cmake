message(STATUS "Hello world")

set(X 2)

py_expr(
    EXPRESSION  "math.sqrt(float(X))"
    MODULES     math
    INPUTS      X
    OUTPUT      Y
)

py_expr(
    EXPRESSION "math.pi"
    MODULES math
    OUTPUT PI_VALUE
)

message(STATUS "sqrt(${X}) = ${Y}")
message(STATUS "PI = ${PI_VALUE}")