/* 
 * File:   FileReader.h
 * Author: thr2
 *
 * Created on 01 December 2012, 19:22
 */
#include "EventStructs.h";

#ifndef FILEREADER_H
#define	FILEREADER_H

#ifdef	__cplusplus
extern "C" {
#endif
    /*Function Prototypes*/
    struct Event_Name *get_event_name(char txt_file[]);
    struct Event_Node *get_event_nodes(char txt_file[]);
    struct Event_Track *get_event_tracks(char txt_file[]);
    struct Event_Course *get_event_courses(char txt_file[]);
    struct Event_Entrant *get_event_entrants(char txt_file[]);
    struct Event_Time *get_event_times(char txt_file[]);

#ifdef	__cplusplus
}
#endif

#endif	/* FILEREADER_H */

