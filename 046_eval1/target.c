#include "target.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets) {
  double a = 1e25;
  if (this_launch->time > a || isnan(this_launch->time)) {
    fprintf(stderr, "Error: Time value out of bounds.\n");
    return (launch_result_t){.theta = NAN, .duration = NAN};
  }
  //STEP 3: Write this
  planet_t * src_planet = find_planet(planets, this_launch->src);
  planet_t * dest_planet = find_planet(planets, this_launch->dest);

  point_t src_location = get_location_at(src_planet, this_launch->time);
  point_t dest_location = get_location_at(dest_planet, this_launch->time);

  double dx = dest_location.x - src_location.x;
  double dy = dest_location.y - src_location.y;
  double distance = sqrt(dx * dx + dy * dy);

  double angle = atan2(dy, dx);
  if (angle < 0) {
    angle += 2 * M_PI;
  }
  launch_result_t result;
  result.theta = angle;
  double duration = distance / this_launch->speed;
  if (this_launch->speed == 0) {
    return (launch_result_t){.theta = angle, .duration = INFINITY};
  }
  else if (isnan(duration) || duration > DBL_MAX) {
    duration = INFINITY;
  }
  else if (isinf(duration)) {
    duration = INFINITY;
  }
  if (this_launch->time + duration > DBL_MAX) {
    result.duration = -NAN;  // Return NaN for arrival time if out of bounds
  }
  result.duration = duration;
  return result;
}

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time) {
  double target_angle = atan2(pos.y, pos.x);
  if (target_angle < 0) {
    target_angle += 2 * M_PI;
  }
  double a = 1e25;
  point_t current_position = get_location_at(planet, start_time);
  double current_angle = atan2(current_position.y, current_position.x);
  if (current_angle < 0) {
    current_angle += 2 * M_PI;
  }

  double angular_velocity = 2 * M_PI / planet->year_len;

  double angle_to_travel = target_angle - current_angle;
  if (angle_to_travel < 0) {
    angle_to_travel += 2 * M_PI;
  }
  double time_to_return = angle_to_travel / angular_velocity;
  //printf("%f", time_to_return);
  if (isnan(time_to_return)) {
    return INFINITY;
  }

  else if (isinf(time_to_return) || time_to_return > DBL_MAX) {
    return INFINITY;
  }
  if (start_time + time_to_return > a) {
    return -NAN;
  }
  return start_time + time_to_return;
}
