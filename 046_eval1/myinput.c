#include "myinput.h"

#include <stdio.h>
void parse_planet_info(planet_t * planet, char * line) {
  char * temp;
  char * line_copy = strdup(line);
  char * field_count_check = line_copy;
  int field_count = 0;

  while (strsep(&field_count_check, ":") != NULL) {
    field_count++;
  }

  if (field_count != 4) {
    free(line_copy);
    printf("Wrong number of fields\n");
    exit(EXIT_FAILURE);
  }
  //planet name
  temp = strsep(&line, ":");

  if (strlen(temp) >= MAX_PLANET_NAME_LEN) {
    free(line_copy);
    printf(" Planet name longer than maximum (31) length\n");
    exit(EXIT_FAILURE);
  }
  strncpy(planet->name, temp, MAX_PLANET_NAME_LEN - 1);
  planet->name[MAX_PLANET_NAME_LEN - 1] = '\0';
  //radius
  temp = strsep(&line, ":");
  char * endptr;
  planet->orbital_radius = strtod(temp, &endptr);
  if (*endptr != '\0') {
    free(line_copy);
    printf(" Invalid format for orbital radius.\n");
    exit(EXIT_FAILURE);
  }
  if (planet->orbital_radius <= 0.0) {
    free(line_copy);
    printf("orbital_radius can't be non-positive \n");
    exit(EXIT_FAILURE);
  }
  //period
  temp = strsep(&line, ":");
  planet->year_len = strtod(temp, &endptr);
  if (*endptr != '\0') {
    free(line_copy);
    printf(" Invalid format for period.\n");
    exit(EXIT_FAILURE);
  }
  if (planet->year_len <= 0.0) {
    free(line_copy);
    printf("year_len can't be non-positive \n");
    exit(EXIT_FAILURE);
  }
  //initial position
  temp = strsep(&line, ":");
  if (*endptr != '\0') {
    free(line_copy);
    printf("Invalid format for initial position.\n");
    exit(EXIT_FAILURE);
  }
  planet->init_pos = strtod(temp, NULL) * M_PI / 180.0;
  if (planet->init_pos < 0.0) {
    free(line_copy);
    printf("init_pos can't be non-positive \n");
    exit(EXIT_FAILURE);
  }
  free(line_copy);
}
