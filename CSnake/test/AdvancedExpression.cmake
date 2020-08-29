message(STATUS "Hello world")

set(X 2)

py_expr(
    EXPRESSION
        "math.sqrt(float(X))"
    MODULES
        math
    INPUTS
        X
    OUTPUT
        Y
)

message(STATUS "sqrt(${X}) = ${Y}")