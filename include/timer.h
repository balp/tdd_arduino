/**
 *  Support functions for a timer.
 */

#include "Arduino.h"
#ifndef __AVR__
#include <iostream>
#endif
static int timer_debug=0;
/**
 * Yet one more timer class for Arduino.
 *
 * My version is made to work something like this.
 *
 *   #include "Arduino.h"
 *   #include "Timer.h"
 *
 *   class Periodical : public Timer::CallbackInterface {
 *        virtual ~Periodical() {}
 *        virtual void onTimeout() {
 *            // DoStuff...
 *        }
 *   } periodical;
 *
 *   Timer timerHandler;
 *
 *   void setup()
 *   {
 *       timerHandler.addTimer(periodical, 100, true);
 *   }
 *
 *   void loop()
 *   {
 *       unsigned long timeout = timerHandler.handleTimeouts();
 *       delay(timeout);
 *   }
 *
 *
 */
class Timer {
    public:
        class CallbackInterface {
            public:
                virtual ~CallbackInterface() {}
                virtual void onTimeout() = 0;
        };
    private:
        struct TimerInfo {
            TimerInfo(CallbackInterface& cb, unsigned long timeout, bool repeating)
                : callback(cb),
                when(millis() + timeout),
                is_repeating(repeating),
                repeat_timeout(timeout),
                next(NULL)
            {}
            unsigned long when;
            CallbackInterface& callback;
            bool is_repeating;
            unsigned long repeat_timeout;
            struct TimerInfo* next;
        } *head;
    public:
        /**
         * Default constructor.
         */
        Timer() : head(NULL) {}

        /**
         * Add a new timer.
         *
         * @param callback the function onTimeout() in this class will be called
         * @param timeout the number of milliseconds to the timeout
         * @param repeating if true the callback will be called every timeout milliseconds.
         */
        void addTimer(CallbackInterface& callback, int timeout, bool repeating) {
#ifdef __AVR__
            if(timer_debug) Serial.print("addTimer(");
            if(timer_debug) Serial.print((unsigned long)&callback);
            if(timer_debug) Serial.print(", ");
            if(timer_debug) Serial.print(timeout);
            if(timer_debug) Serial.print(", ");
            if(timer_debug) Serial.print(repeating);
            if(timer_debug) Serial.println(")");
#else
            if(timer_debug) std::cerr << "addTimer(" << &callback << "," << timeout << "," << repeating << ")" << std::endl;
#endif
            TimerInfo* info = new TimerInfo(callback, timeout, repeating);
            insertTimer(info);
        }

        /**
         * Called to handle the timeouts.
         *
         * The functions is designed to be part of a main loop, like this.
         *   
         *   void loop(void) {
         *      unsigned long timeout = timerHandler->handleTimeouts();
         *      delay(timeout);
         *   }
         *
         *
         * @return the number of milliseconds to next timer or -1 if no active timers.
         */
        int handleTimeouts() {
            int returntime = -1;
#ifdef __AVR__
            if(timer_debug) Serial.print("handleTimeouts(");
            if(timer_debug) Serial.print((unsigned long)head);
            if(timer_debug) Serial.println(")");
#else
            if(timer_debug) std::cerr << "handleTimeouts(): head " << head <<  std::endl;
#endif
            if(! head) {
                return -1;
            }
            unsigned long now = millis();
#ifdef __AVR__
            if(timer_debug) Serial.print("handleTimeouts(): now ");
            if(timer_debug) Serial.print(now);
            if(timer_debug) Serial.print(" ");
            if(timer_debug) Serial.print(head->when);
            if(timer_debug) Serial.print(" ");
            if(timer_debug) Serial.println((unsigned long)head->next);
#else
            if(timer_debug) std::cerr << "handleTimeouts(): now " << now << " " << head->when << std::endl;
#endif
            TimerInfo* callback = NULL;
            if(now >= head->when) {
                callback = head;
                TimerInfo* tmp = head;
                head = head->next;
                if(tmp->is_repeating) {
                    tmp->when += tmp->repeat_timeout;
                    if(tmp->when < now) { // We missed a timeout
                        tmp->when = now + tmp->repeat_timeout;
                    } 
                    tmp->next = NULL;
                    insertTimer(tmp);
                } else {
#ifdef __AVR__
                    if(timer_debug) Serial.print("handleTimeouts(): delete ");
                    if(timer_debug) Serial.println((unsigned long)tmp);
#else
                    if(timer_debug) std::cerr << "handleTimeouts(): delete " << tmp << std::endl;
#endif
                    delete tmp;
                }
            }
            if(head) {
#ifdef __AVR__
                if(timer_debug) Serial.print("handleTimeouts(): timeout ");
                if(timer_debug) Serial.print(head->when - now);
                if(timer_debug) Serial.print(" = ");
                if(timer_debug) Serial.print(head->when);
                if(timer_debug) Serial.print(" - ");
                if(timer_debug) Serial.println(now);
#endif
                if (now < head->when) {
                    returntime =  head->when - now;
                } else {
                    returntime =  0;
                }
            } else {
#ifdef __AVR__
                if(timer_debug) Serial.println("handleTimeouts(): no head -1 ");
#endif

            }
            if(callback) {
                callback->callback.onTimeout();
            }
            return returntime;
        }

        /**
         * Remove a timer for the handler
         *
         * @param callback the callback to be removed.
         */
        void removeTimer(CallbackInterface& callback) {
#ifdef __AVR__
            if(timer_debug) Serial.print("removeTimer(");
            if(timer_debug) Serial.print((unsigned long)&callback);
            if(timer_debug) Serial.println(")");
#else
            if(timer_debug) std::cerr << "removeTimer(" << &callback << ")" << std::endl;
#endif
            TimerInfo* tmp = head;
            TimerInfo* prev = NULL;
            while(tmp) {
                if(&(tmp->callback) == &(callback)) {
                    if(prev) {
                        prev->next = tmp->next;
                    } else {
                        head = tmp->next;
                    }
#ifndef __AVR__
                    if(timer_debug) std::cerr << "removeTimer(): delete " << tmp << std::endl;
#endif
                    delete tmp;
                    break;
                }
                prev = tmp;
                tmp = tmp->next;
            }
        }

    private:
        void insertTimer(TimerInfo* info) {
#ifdef __AVR__
            if(timer_debug) Serial.print("insertTimer( when ");
            if(timer_debug) Serial.print(info->when);
            if(timer_debug) Serial.print(", next ");
            if(timer_debug) Serial.print((unsigned long)info->next);
            if(timer_debug) Serial.print(", is_repeating ");
            if(timer_debug) Serial.print(info->is_repeating);
            if(timer_debug) Serial.println(")");
#else
            if(timer_debug) std::cerr << "insertTimer(" << info << ") [" << info->when << "," << info->next << "]" << std::endl;
#endif
            if(! head) { // No events queued
                head = info;
            } else {
                TimerInfo* tmp = head;
                TimerInfo* prev = NULL;
                while(tmp) {
                    if(tmp->when > info->when) {
                        info->next = tmp;
                        if(prev) {
                            prev->next = info;
                        } else {
                            head = info;
                        }
                        tmp = NULL;
                    } else {
                        if(tmp->next) {
                            prev = tmp;
                            tmp = tmp->next;
                        } else {
                            tmp->next = info;
                            tmp = NULL;
                        }
                    }
                }
            }
#ifndef __AVR__
            if(timer_debug) std::cerr << "insertTimer(" << info << "): exit" << std::endl;
#endif
        }

};
