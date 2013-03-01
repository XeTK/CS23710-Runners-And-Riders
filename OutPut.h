/* 
 * File:   OutPut.h
 * Author: THR2
 *
 * Created on 06 December 2012, 11:46
 */
#include "EventStructs.h"
#ifndef OUTPUT_H
#define	OUTPUT_H

#ifdef	__cplusplus
extern "C" {
#endif

    void print_menu();
    void print_event_name(struct Event_Name *e_name);
    void print_event_nodes(struct Event_Node *e_nodes);
    void print_event_tracks(struct Event_Track *e_tracks);
    void print_event_courses(struct Event_Course *e_courses);
    void print_event_entrants(struct Event_Entrant *e_entrants);
    void print_event_times(struct Event_Time *e_times);


#ifdef	__cplusplus
}
#endif

#endif	/* OUTPUT_H */

