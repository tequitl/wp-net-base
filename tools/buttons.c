/*
 * buttons.c — Demo de botones con ncurses para Termux
 *
 * Compilar:  clang -O2 -o buttons buttons.c -lncursesw
 * Usar:      flechas o Tab para navegar, Enter para activar,
 *            o tocar el boton directamente. q o ESC para salir.
 */

#include <ncurses.h>
#include <string.h>
#include <time.h>

#define NUM_BUTTONS 3

static const char *labels[NUM_BUTTONS] = {"Saludar", "Hora", "Salir"};
static char message[64] = "Usa flechas/Tab y Enter, o toca un boton.";

static int selected = 0;
static int btn_x[NUM_BUTTONS], btn_w[NUM_BUTTONS], btn_y;

/* Calcula posicion y ancho de cada boton, centrados en pantalla */
static void layout(void)
{
    int total = 0;

    for (int i = 0; i < NUM_BUTTONS; i++) {
        btn_w[i] = (int)strlen(labels[i]) + 4; /* padding de 2 a cada lado */
        total += btn_w[i];
    }
    total += (NUM_BUTTONS - 1) * 2; /* separacion entre botones */

    btn_x[0] = (getmaxx(stdscr) - total) / 2;
    for (int i = 1; i < NUM_BUTTONS; i++)
        btn_x[i] = btn_x[i - 1] + btn_w[i - 1] + 2;

    btn_y = getmaxy(stdscr) / 2;
}

static void draw_button(int i)
{
    if (i == selected)
        wattr_on(stdscr, A_REVERSE, NULL);
    mvprintw(btn_y, btn_x[i], " %-*s ", btn_w[i] - 4, labels[i]);
    if (i == selected)
        wattr_off(stdscr, A_REVERSE, NULL);
}

static void draw(void)
{
    const char *title = "Demo C + ncurses";

    werase(stdscr);

    mvprintw(btn_y - 3, (getmaxx(stdscr) - (int)strlen(title)) / 2, "%s", title);
    for (int i = 0; i < NUM_BUTTONS; i++)
        draw_button(i);
    mvprintw(btn_y + 2, (getmaxx(stdscr) - (int)strlen(message)) / 2, "%s", message);

    wrefresh(stdscr);
}

/* Ejecuta el boton; devuelve 1 si hay que salir del programa */
static int activate(int i)
{
    time_t now = time(NULL);
    struct tm t;

    localtime_r(&now, &t);

    switch (i) {
    case 0: /* Saludar */
        snprintf(message, sizeof(message), "Hola desde Termux!");
        return 0;
    case 1: /* Hora */
        strftime(message, sizeof(message), "Son las %H:%M:%S", &t);
        return 0;
    case 2: /* Salir */
        return 1;
    }
    return 0;
}

/* Mueve la seleccion de forma circular */
static void next_button(int dir)
{
    selected = (selected + dir + NUM_BUTTONS) % NUM_BUTTONS;
}

int main(void)
{
    int quit = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    while (!quit) {
        layout();
        draw();

        switch (wgetch(stdscr)) {
        case KEY_RESIZE:
            break; /* solo redibujar */

        case KEY_LEFT:
            next_button(-1);
            break;
        case KEY_RIGHT:
        case '\t':
            next_button(1);
            break;
        case KEY_BTAB:
            next_button(-1);
            break;

        case '\n': /* KEY_ENTER */
        case '\r':
            quit = activate(selected);
            break;

        case KEY_MOUSE: {
            MEVENT ev;
            if (getmouse(&ev) == OK &&
                (ev.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED))) {
                for (int i = 0; i < NUM_BUTTONS; i++) {
                    if (ev.y == btn_y &&
                        ev.x >= btn_x[i] && ev.x < btn_x[i] + btn_w[i]) {
                        selected = i;
                        quit = activate(i);
                        break;
                    }
                }
            }
            break;
        }

        case 'q':
        case 27: /* ESC */
            quit = 1;
            break;
        }
    }

    endwin();
    return 0;
}
