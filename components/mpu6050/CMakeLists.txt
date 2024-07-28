idf_component_register(
    SRCS "src/mpu6050.c"
         "src/roll_pitch.c"
         "src/quaternions.c"
    INCLUDE_DIRS "include"
    REQUIRES driver
)
