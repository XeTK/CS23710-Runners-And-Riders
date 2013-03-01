#include <stdio.h>
#include <stdlib.h>
#include "EventStructs.h"
#include "FileReader.h"
#include "OutPut.h"
#include "Query.h"

/*Function prototypes didnt feel the need for a header for this class as there was so little*/
void menu();
void read_files();
void print_linkedlists();
void add_time();

/*Static valriables for all the most used objects*/
static struct Event_Name *e_name;
static struct Event_Node *e_nodes;
static struct Event_Track *e_tracks;
static struct Event_Course *e_courses;
static struct Event_Entrant *e_entrants;
static struct Event_Time *e_times;
static struct Current_Compet *c_competitors;

/*Standard main method, just used to load up the menu*/
int main(int argc, char** argv) 
{
    menu();
    return (EXIT_SUCCESS);    
}
/*Menu is the method for showing some interface for the end user to interact with*/
void menu()
{
    int option = 0;
    /*We Print the Menu navigation chart*/
    print_menu();
    scanf("%i",&option);
    /*If for selecting where we go in the program*/
    if (option ==1)
    {
        /*Call are function for reading in the files*/
        read_files();
    }
    else if (option == 2)
    {
        /*Debug method for printing out the text files left it in as it can be useful later*/
        print_linkedlists();
    }
    else if (option == 3)
    {
        /*This method is used to print out the finished, unfinished and not started competitors*/
        entrants_pos(e_times,e_entrants,e_courses,e_nodes);
    }
    else if (option == 4)
    {
        /*The function below is for getting the progress of 1 specific competitor*/
        printf("Please enter the competitor number of the competitor you would like to query\n\n");
        int i = 0;
        scanf("%i",&i);
        queary_entrant(i,e_courses,c_competitors);
    }
    else if (option == 5)
    {
        /*Sort method for the list of competitors*/
        queary_entrant(-1,e_courses,c_competitors);
        comp_sort(c_competitors);
    }
    else if (option == 6)
    {
        /*Add another time for the components to be taken into account*/
        add_time();
    }
    menu();
}
/*Read in the data files ready for use*/
void read_files()
{
    e_name = get_event_name("//Users//XeTK//Desktop//CassignmentTXT//name.txt");
    e_nodes = get_event_nodes("//Users//XeTK//Desktop//CassignmentTXT//nodes.txt");
    e_tracks = get_event_tracks("//Users//XeTK//Desktop//CassignmentTXT//tracks.txt");
    e_courses = get_event_courses("//Users//XeTK//Desktop//CassignmentTXT//courses.txt");
    e_entrants = get_event_entrants("//Users//XeTK//Desktop//CassignmentTXT//entrants.txt");
    e_times = get_event_times("//Users//XeTK//Desktop//CassignmentTXT//cp_times_2.txt");
    /*Index are competitors to make it easier to carry out operations on them later*/
    c_competitors = noderized(e_times,e_entrants,e_courses,e_nodes);
}
/*Print out the linked lists that hold the data to double check the data, Technicaly Debug but I left it in*/
void print_linkedlists()
{
    print_event_name(e_name);
    print_event_nodes(e_nodes);
    print_event_tracks(e_tracks);
    print_event_courses(e_courses);
    print_event_entrants(e_entrants);
    print_event_times(e_times);
}
/*Method below is to add a new time to the link listed contained above*/
void add_time()
{
    /*Define the start point*/
    const struct Event_Time *e_t;
    /*and a temp place to assign it to while we loop through*/
    struct Event_Time *temp;
    /*set the pointers to where its relivent*/
    e_t = e_times;
    temp = e_t;
    /*Keep looping till we hit the end*/
    while(1)
    {
        /*Set Node to next node for next operation*/
        temp = temp->next_time;
        /*if the node is == to null then we are at the end of the list so we have to break*/
        if (temp == NULL)
            break;
        /*if the next node == to null then we are near the end of the list so we add a new record*/
        if (temp->next_time == NULL)
        {
            /*define a temp struct pointer to hold it while we imput the data*/
            struct Event_Time *e_temp;
            /*allocate some memory to it*/
            e_temp = malloc(sizeof(struct Event_Time));
            /*get the data into the struct*/
            printf("\nStatus : ");
            scanf(" %c",&e_temp->status);
            printf("\nNode : ");
            scanf(" %i",&e_temp->node);
            printf("\nCompetitor : ");
            scanf(" %i",&e_temp->entrant_num);
            printf("\nTime Entered 00:00 : ");
            scanf(" %6s",&e_temp->time);
            /*set the next node to the new struct*/
            temp->next_time = e_temp;
            /*break to exit the adding process*/
            break;
        }
    }
}