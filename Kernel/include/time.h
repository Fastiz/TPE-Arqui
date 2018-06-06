#ifndef TIME_H
#define TIME_H

void newTimer(int, void(*)());

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();

#endif
