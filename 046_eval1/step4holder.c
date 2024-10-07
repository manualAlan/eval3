#include "iter_target.h"

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  planet_t * src_planet = find_planet(planets, this_launch->src);
  planet_t * dest_planet = find_planet(planets, this_launch->dest);

  point_t src_location, dest_location;
  launch_result_t best_result, current_result;
  double best_total_time = -1.0;
  const double current_time = this_launch->time;
  double dtime = 0.0;

  printf("Computing launch from %s to %s at time %.2f\n",
         this_launch->src,
         this_launch->dest,
         current_time);

  for (uint64_t i = 0; i < this_launch->max_iterations; i++) {
    printf("Iteration %lu:\n", i);
    src_location = get_location_at(src_planet, current_time);

    dest_location = get_location_at(dest_planet, current_time + dtime);

    double dx = dest_location.x - src_location.x;
    double dy = dest_location.y - src_location.y;
    double distance = sqrt(dx * dx + dy * dy);

    current_result.theta = atan2(dy, dx);
    if (current_result.theta < 0) {
      current_result.theta += 2 * M_PI;
    }

    current_result.duration = distance / this_launch->speed;

    double arrival_time = current_time + current_result.duration;
    double waiting_time =
        when_does_planet_return_to(dest_planet, dest_location, arrival_time) -
        arrival_time;

    double total_time = current_result.duration + waiting_time;

    printf("  Angle: %.2f degrees, Duration: %.2f hours\n",
           current_result.theta * 180 / M_PI,
           current_result.duration);
    printf("  Arrival time: %.2f, Waiting time: %.2f, Total time: %.2f\n",
           arrival_time,
           waiting_time,
           total_time);

    if (best_total_time == -1.0 || total_time < best_total_time) {
      dtime = current_result.duration;
      best_result = current_result;
      best_total_time = total_time;
      printf("  ** New best solution **\n");
    }

    if (total_time > best_total_time || waiting_time == 0.0 ||
        distance <= this_launch->close_enough) {
      break;  // Exit the loop early if there's no waiting or we are close enough
    }
  }

  return best_result;
}
