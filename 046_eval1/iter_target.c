#include "iter_target.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  planet_t * src_planet = find_planet(planets, this_launch->src);
  planet_t * dest_planet = find_planet(planets, this_launch->dest);

  point_t src_location, dest_location;
  launch_result_t best_result, current_result;
  double best_total_time = -1.0;
  double current_time = this_launch->time;

  for (uint64_t iteration = 0; iteration < this_launch->max_iterations; ++iteration) {
    src_location = get_location_at(src_planet, current_time);
    dest_location = get_location_at(dest_planet, current_time);

    double dx = dest_location.x - src_location.x;
    double dy = dest_location.y - src_location.y;
    double distance = sqrt(dx * dx + dy * dy);

    current_result.theta = atan2(dy, dx);
    if (current_result.theta < 0) {
      current_result.theta += 2 * M_PI;
    }

    current_result.duration = distance / this_launch->speed;

    if (distance <= this_launch->close_enough) {
      return current_result;
    }

    double arrival_time = current_time + current_result.duration;
    double waiting_time =
        when_does_planet_return_to(dest_planet, dest_location, arrival_time) -
        arrival_time;

    double total_time = current_result.duration + waiting_time;

    if (best_total_time == -1.0 || total_time < best_total_time) {
      best_result = current_result;
      best_total_time = total_time;
    }

    current_time = arrival_time;
  }

  return best_result;
}
