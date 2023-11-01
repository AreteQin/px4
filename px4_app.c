#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/tasks.h>
#include <px4_platform_common/posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <math.h>

#include <uORB/uORB.h>
#include <uORB/topics/vehicle_acceleration.h>
#include <uORB/topics/vehicle_attitude.h>

__EXPORT int px4_app_main(int argc, char *argv[]);

int px4_app_main(int argc, char *argv[]) {
    PX4_INFO("Hello Sky!");

    int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));

/* one could wait for multiple topics with this technique, just using one here */
    px4_pollfd_struct_t fds[] = {
            {.fd = sensor_sub_fd, .events = POLLIN},
    };

    while (true) {
        /* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
        int poll_ret = px4_poll(fds, 1, 1000);
        ..
        if (fds[0].revents & POLLIN) {
            /* obtained data for the first file descriptor */
            struct sensor_combined_s raw;
            /* copy sensors raw data into local buffer */
            orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &raw);
            PX4_INFO("Accelerometer:\t%8.4f\t%8.4f\t%8.4f",
                     (double) raw.accelerometer_m_s2[0],
                     (double) raw.accelerometer_m_s2[1],
                     (double) raw.accelerometer_m_s2[2]);
        }
    }

    return 0;
}
