#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef CONSUMER
#define CONSUMER "esme-gpio-toggle"
#endif

int main(int argc, char **argv)
{
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int gpio_id = 26;  // GPIO par défaut
    int value = 0;
    int ret;

    // Analyse des arguments
    if (argc > 1) {
        if (strcmp(argv[1], "--gpio") == 0 && argc > 2) {
            gpio_id = atoi(argv[2]);
        } else {
            fprintf(stderr, "Usage: %s [--gpio <GPIO_ID>]\n", argv[0]);
            return 1;
        }
    }

    // Ouvrir le chip GPIO
    chip = gpiod_chip_open_by_name("gpiochip0");
    if (!chip) {
        perror("gpiod_chip_open_by_name");
        return 1;
    }

    // Récupérer la ligne GPIO
    line = gpiod_chip_get_line(chip, gpio_id);
    if (!line) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
        return 1;
    }

    // Configurer en sortie
    ret = gpiod_line_request_output(line, CONSUMER, 0);
    if (ret < 0) {
        perror("gpiod_line_request_output");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return 1;
    }

    printf("Toggling GPIO %d (chip0) every second...\n", gpio_id);

    // Boucle infinie : toggle toutes les secondes
    while (1) {
        value = !value;
        gpiod_line_set_value(line, value);
        sleep(1);
    }

    // Nettoyage (jamais atteint)
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}
