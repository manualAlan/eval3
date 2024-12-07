#include "planet_util.h"

#include <stdio.h>
#include <string.h>

#include "provided.h"

point_t get_location_at(const planet_t * p, double time) {
  double angular_velocity = 2 * M_PI / p->year_len;
  double angle = p->init_pos + angular_velocity * time;
  angle = fmod(angle, 2 * M_PI);

  point_t location;
  location.x = p->orbital_radius * cos(angle);
  location.y = p->orbital_radius * sin(angle);
  return location;
}
planet_t * find_planet(const planet_list_t * lst, const char * name) {
  for (size_t i = 0; i < lst->num_planets; i++) {
    if (strncmp(lst->planets[i]->name, name, MAX_PLANET_NAME_LEN) == 0) {
      return lst->planets[i];
    }
  }
  fprintf(stderr, " Planet '%s' not found\n", name);
  exit(EXIT_FAILURE);
}
