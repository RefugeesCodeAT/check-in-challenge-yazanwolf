#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

typedef struct PARTICIPANT
{
    string name;
    bool checked_in;
    struct PARTICIPANT* next;
}
PARTICIPANT;

PARTICIPANT* participants = NULL;

#define CHECKED_IN true
#define CHECKED_OUT false

string get_user_input();
bool perform(string user_input);

// TODO: Functions to implement
void add_one(string participant_name);
void remove_one(string participant_name);
void check_one(string participant_name);
void display_participants();
void free_memory();

int main(void)
{
    bool working = true;

    while(working)
    {
        string user_input = get_user_input();
        working = perform(user_input);
    }

    free_memory();
}

string get_user_input()
{
    return get_string("Command: ");
}

// Performs the action from the "user_input"
bool perform(string user_input)
{
    // Read the string of user input into two variables
    string action_name = strtok(user_input, " ");
    string participant_name = strtok(NULL, " ");

    if(strcmp(action_name, "add") == 0)
    {
        add_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "remove") == 0)
    {
        remove_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "check") == 0)
    {
        check_one(participant_name);
        return true;
    }
    if(strcmp(action_name, "display") == 0)
    {
       display_participants();
       return true;
    }
    if(strcmp(action_name, "exit") == 0)
    {
        return false;
    }

    return true;
}

/*
    Adds a participant to the beginning of the list
*/
void add_one(string participant_name)
{
    // string name = get_string("write a name: ");
    // participant_name = name;
    // PARTICIPANT* current = participants;

    PARTICIPANT* new_participant = malloc(sizeof(PARTICIPANT));
    new_participant->name = participant_name;
    new_participant->checked_in = CHECKED_OUT;
    new_participant->next = NULL;

    if (participants == NULL)
    {
        participants = new_participant;
        // current = new_participant;
    }
    else
    {
       new_participant->next = participants;
       participants = new_participant;
    }

    // participants->next = current;


}

/*
    Search for a participant in the list and if it exists, remove it.
*/
void remove_one(string participant_name)
{
    PARTICIPANT* first = participants;
    PARTICIPANT* previous = first;
    PARTICIPANT* current = first;
    //participant_name = get_string("write the name of the participant you want to remove: ");

    if (strcmp(participant_name ,first->name) == 0)
        {

            current = first->next;
            participants = current;
            free(first);
        }
    else
    {

        while (true)
        {
            previous = current;
            current = current->next;
            if(strcmp(current->name, participant_name) == 0)
            {
                previous->next = current->next;
                free(current);
                break;
            }
        }
    }

    printf("remove %s\n", participant_name);
}

/*
    Check a participant from the list in or out
*/
void check_one(string participant_name)
{
    PARTICIPANT* current = participants;

    // string name = get_string("which participant: ");
    //participant_name = name;

   while (current != NULL)
   {
       if (strcmp(participant_name, current->name) == 0)
       {
           if(current->checked_in == CHECKED_IN)
           {
               current->checked_in = CHECKED_OUT;
               break;
           }
           else
           {
               current->checked_in = CHECKED_IN;
               break;
           }
       }
       else
       {
           current = current->next;
       }
   }
    printf("check %s\n", participant_name);
    return;

}

/*
    Display all participants and their status.
*/
void display_participants()
{

    printf("display:\n");

    if (participants != NULL)
    {
        PARTICIPANT* current = participants;
        while(current != NULL)
        {
            printf("%s\n%i\n", current->name,  current->checked_in);
            current = current->next;
        }
    }
    else
    {
        printf("empty\n");
        return;
    }



    // TODO
}

/*
    Free all memory used by participants in the list
*/
void free_memory()
{
    PARTICIPANT* first = participants;
    PARTICIPANT* previous = first;
    PARTICIPANT* current = first;

    printf("freeing stuff.\n");
    if (participants != NULL)
    {
        while (true)
        {
            previous = current;
            current = current->next;
            if(current->next == NULL)
            {
                free(current);
                current = NULL;
                current = first;
            }
            if (participants == NULL)
            {
                break;
            }
        }
    }

    return;
    // TODO
}