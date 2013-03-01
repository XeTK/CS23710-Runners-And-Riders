/* 
 * File:   EventStructs.h
 * Author: THR2
 *
 * Created on November 30, 2012, 5:52 PM
 */

#ifndef EVENTSTRUCTS_H
#define	EVENTSTRUCTS_H

#ifdef	__cplusplus
extern "C" {
#endif

    struct Event_Name
    {
       char name[80];
       char date[80];
       char time[5];
    };
    struct Event_Node
    {
        int node;
        char node_type[2];
        struct Event_Node *next_node;
    };
    struct Event_Track
    {
        int number;
        int start_node;
        int end_node;
        int expected_time;
        struct Event_Track *next_track;
    };
    struct Event_Course
    {
        char ident;
        int node_num;
        struct Event_Course_Node *head_node;
        struct Event_Course *next_course;
    };
    struct Event_Course_Node
    {
        int node;
        struct Event_Course_Node *next_node;
    };
    struct Event_Entrant
    {
        int comp_num;
        char course;
        char name[51];
        struct Event_Entrant *next_entrant;
    };
    struct Event_Time
    {
        char status;
        int node;
        int entrant_num;
        char time[5];
        struct Event_Time *next_time;
    };


#ifdef	__cplusplus
}
#endif

#endif	/* EVENTSTRUCTS_H */

